#BCC excecutables
CC 			= sparc-gaisler-elf-gcc
OBJDUMP	= sparc-gaisler-elf-objdump
SIZE 		= sparc-gaisler-elf-size
LD			= sparc-gaisler-elf-gcc

#BCC includes and libraries
#The BCC_PREFIX and BCC_VERSION environment variables should be set in the environment.
CCROOT 	:= /opt/${BCC_PREFIX}bcc-${BCC_VERSION}-gcc
BCC_SRC := $(CCROOT)/src/libdrv/src
BCC_INC := $(BCC_SRC)/include

BSP ?= gr740


#Paths to local includes, sources and binaries
ROOTDIR 	:= $(realpath $(dir $(abspath $(lastword $(MAKEFILE_LIST)))))
TARGET		:= hw

SOURCE_DIR		:= $(ROOTDIR)/src/ASW
INCLUDE_DIR		:= $(SOURCE_DIR)
BUILD_DIR 		:= build/$(TARGET)

# GLUE layer includes and sources path
GLUE_DIR							:= $(ROOTDIR)/src/glue
GLUE_INC							:= $(GLUE_DIR)
DBG_INC_DIR						:= $(GLUE_DIR)/debug-terminal-source
DBG_CIRC_INC_DIR			:= $(DBG_INC_DIR)/circular_hist
TARGET_PLATFORM_DIR 	:= $(GLUE_DIR)/$(TARGET)
DBG_CFG_DIR						:= $(TARGET_PLATFORM_DIR)/dbg_cfg
GR740_DIR							:= $(TARGET_PLATFORM_DIR)/gr740
LIBGLUE_DIR						:= ${BUILD_DIR}/glue
LIBGLUE								:= glue
LIBGLUE_GDB						:= glue_gdb

# FwProfile include and library path
FWP_DIR			:= src/include/FwProfile
FWP_INC			:= $(FWP_DIR)/src
FWP_LIB_DIR	:= build/$(TARGET)/FwProfile
FWP_LIB			:= fwprofile
FWP_LIB_GDB	:= fwprofile_gdb


# Includes for the compiler
_INCLUDES	+= -I$(BCC_INC)
_INCLUDES	+= -I$(INCLUDE_DIR)
_INCLUDES	+= -I$(FWP_INC)
_INCLUDES	+= -I$(GLUE_INC)
_INCLUDES	+= -I$(DBG_INC_DIR)
_INCLUDES	+= -I$(DBG_CIRC_INC_DIR)
_INCLUDES	+= -I$(TARGET_PLATFORM_DIR)
_INCLUDES	+= -I$(DBG_CFG_DIR)
_INCLUDES	+= -I$(GR740_DIR)

override INCLUDES := $(_INCLUDES) $(INCLUDES)

# Compiler flags
_CFLAGS  += -qbsp=$(strip $(BSP))
_CFLAGS  += -Og
_CFLAGS  += -mcpu=leon3
_CFLAGS  += -qnano
_CFLAGS  += -qsvt
_CFLAGS  += -std=c99
_CFLAGS  += -Wall -Wextra -pedantic
override CFLAGS := $(_CFLAGS) $(CFLAGS)

# Compiler flags for debug
_CFLAGS_GDB  += -qbsp=$(strip $(BSP))
_CFLAGS_GDB  += -Og
_CFLAGS_GDB  += -mcpu=leon3
_CFLAGS_GDB  += -qnano
_CFLAGS_GDB  += -qsvt
_CFLAGS_GDB  += -std=c99
_CFLAGS_GDB  += -Wall -Wextra -pedantic
_CFLAGS_GDB  += -ggdb3
override CFLAGS_GDB := $(_CFLAGS_GDB) $(CFLAGS_GDB)

# Linker flags
_LDFLAGS ?= -L$(LIBGLUE_DIR) -L$(FWP_LIB_DIR) -u _printf_float
override LDFLAGS := $(_LDFLAGS) $(LDFLAGS)

# Linker Libraries
_LDLIBS  ?= -l$(LIBGLUE) -l$(FWP_LIB)
override LDLIBS := $(_LDLIBS) $(LDLIBS)

# For debug build, link against libfwprofile_gdb.a
_LDLIBS_GDB ?= -l$(LIBGLUE_GDB) -l$(FWP_LIB_GDB)
override LDLIBS_GDB := $(_LDLIBS_GDB) $(LDLIBS_GDB)

# Source files
# Drivers
_COMMON_C       += $(wildcard $(BCC_SRC)/spi/*.c)
_COMMON_C       += $(wildcard $(BCC_SRC)/gpio/*.c)
_COMMON_C       += $(wildcard $(BCC_SRC)/timer/*.c)
_COMMON_C       += $(wildcard $(BCC_SRC)/grspw/*.c)
_COMMON_C       += $(wildcard $(BCC_SRC)/misc/*.c)
_COMMON_C       += $(wildcard $(BCC_SRC)/apbuart/*.c)
_COMMON_C       += $(wildcard $(BCC_SRC)/clkgate/*.c)
_COMMON_C       += $(wildcard $(BCC_SRC)/osal/bcc2/*.c)

# Our files
_COMMON_C       += $(SOURCE_DIR)/operational_sm.c
_COMMON_C	    	+= $(wildcard $(DBG_INC_DIR)/*.c)
_COMMON_C	    	+= $(wildcard $(DBG_CIRC_INC_DIR)/*.c)
_COMMON_C       += $(wildcard $(TARGET_PLATFORM_DIR)/*.c)
_COMMON_C       += $(wildcard $(DBG_CFG_DIR)/*.c)
_COMMON_C       += $(wildcard $(GR740_DIR)/*.c)


#Build instructions
#We build two .elf images because it is recommended to only provide the image with debug symbols (ASW_main_gdb.elf) to the debugger, and load the image without them (ASW_main.elf) to the HW target.
.PHONY: all
all: $(BUILD_DIR) XGIS_iDHU_ASW dis size size_gdb
	@echo "Finished building" $(TARGET) "target."

.phony: $(BUILD_DIR)
$(BUILD_DIR):
	@mkdir -p $(BUILD_DIR)

.phony: size
size: $(BUILD_DIR)/XGIS_iDHU_ASW.elf
	$(SIZE) $<

.phony: size_gdb
size_gdb: $(BUILD_DIR)/XGIS_iDHU_ASW_gdb.elf
	$(SIZE) $<

.phony: XGIS_iDHU_ASW
XGIS_iDHU_ASW: $(BUILD_DIR)/XGIS_iDHU_ASW.elf $(BUILD_DIR)/XGIS_iDHU_ASW_gdb.elf

$(BUILD_DIR)/XGIS_iDHU_ASW.elf: $(SOURCE_DIR)/ASW_main.c $(_COMMON_C)
	$(CC) $(CFLAGS) $(INCLUDES) $^ $(LDFLAGS) $(LDLIBS) -o $@ -Wl,-Map=$@.map

$(BUILD_DIR)/XGIS_iDHU_ASW_gdb.elf: $(SOURCE_DIR)/ASW_main.c $(_COMMON_C)
	$(CC) $(CFLAGS_GDB) $(INCLUDES) $^ $(LDFLAGS) $(LDLIBS_GDB) -o $@ -Wl,-Map=$@.map

.phony: dis
dis: $(BUILD_DIR)/XGIS_iDHU_ASW.dis $(BUILD_DIR)/XGIS_iDHU_ASW_gdb.dis

$(BUILD_DIR)/XGIS_iDHU_ASW.dis : $(BUILD_DIR)/XGIS_iDHU_ASW.elf
	$(OBJDUMP) -S -d -r $< > $@

$(BUILD_DIR)/XGIS_iDHU_ASW_gdb.dis : $(BUILD_DIR)/XGIS_iDHU_ASW_gdb.elf
	$(OBJDUMP) -S -d -r $< > $@

.PHONY: clean
clean:
	rm -f $(BUILD_DIR)/*.map $(BUILD_DIR)/*.dis $(BUILD_DIR)/*.o $(BUILD_DIR)/*.elf