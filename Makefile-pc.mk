#compiler
CC		:= gcc
CFLAGS	:= -O0 -W -Wall -Wextra -Wno-variadic-macros -Wno-address-of-packed-member -std=gnu99 -pedantic -ggdb 
CFLAGS	+= -Wno-type-limits -Wno-unused -Wno-format
CFLAGS	+= -DWITH_FORK

#linker
LD		:= gcc
LDFLAGS	:= -lm -pthread -lgcov --coverage

#Paths to local includes, sources and binaries
ROOTDIR 	:= $(realpath $(dir $(abspath $(lastword $(MAKEFILE_LIST)))))
TARGET		:= pc


SOURCE_DIR		:= $(ROOTDIR)/src/ASW
INCLUDE_DIR		:= $(SOURCE_DIR)
BUILD_DIR 		:= build/$(TARGET)

# GLUE layer includes and sources path
GLUE_DIR						:= $(ROOTDIR)/src/glue
GLUE_INC						:= $(GLUE_DIR)
DBG_INC_DIR					:= $(GLUE_DIR)/debug-terminal-source
DBG_CIRC_INC_DIR		:= $(DBG_INC_DIR)/circular_hist
TARGET_PLATFORM_DIR := $(GLUE_DIR)/$(TARGET)
DBG_CFG_DIR					:= $(TARGET_PLATFORM_DIR)/dbg_cfg
LIBGLUE_DIR					:= ${BUILD_DIR}/glue
LIBGLUE							:= ${LIBGLUE_DIR}/libglue.a

# FwProfile include and library path
FWP_DIR	= $(ROOTDIR)/src/include/FwProfile
FWP_INC	= $(FWP_DIR)/src
FWP_LIB	= build/$(TARGET)/FwProfile/libfwprofile.a

# Includes for the compiler
_INCLUDES	+= -I$(INCLUDE_DIR)
_INCLUDES	+= -I$(FWP_INC)
_INCLUDES	+= -I$(GLUE_INC)
_INCLUDES	+= -I$(DBG_INC_DIR)
_INCLUDES	+= -I$(DBG_CIRC_INC_DIR)
_INCLUDES	+= -I$(TARGET_PLATFORM_DIR)
_INCLUDES	+= -I$(DBG_CFG_DIR)

override INCLUDES := $(_INCLUDES) $(INCLUDES)

LOPTIONS	:= -lpthread

# Source files
SOURCES	:= $(shell find $(SOURCE_DIR)/ -type f -name "*.c")
SOURCE_OBJ	:= $(SOURCES:$(SOURCE_DIR)/%.c=$(BUILD_DIR)/%.o)

.PHONY: all
all:	XGIS_iDHU_ASW
	@echo "Finished building" $(TARGET) "target."

$(BUILD_DIR):
	@mkdir -p $(BUILD_DIR)

.SECONDEXPANSION:
$(SOURCE_OBJ) : $$(patsubst $(BUILD_DIR)/%.o,$(SOURCE_DIR)/%.c,$$@)
	@echo "Compiling" $< "..."	
	$(CC) -c -o $@ $(CFLAGS) $(INCLUDES) $<

XGIS_iDHU_ASW:  $(BUILD_DIR) $(SOURCE_OBJ)
	@echo "Building" $(TARGET) "target."

	$(LD) -o $(BUILD_DIR)/XGIS-DHU-ASW-PC $(SOURCE_OBJ) $(LIBGLUE) $(FWP_LIB) $(LOPTIONS) $(LDFLAGS)

	@echo "XGIS_iDHU_ASW_PC is ready!"

.PHONY: clean
clean:
	cd $(BUILD_DIR); find . -name '*.gcno' -delete
	cd $(BUILD_DIR); find . -name '*.gcda' -delete
	cd $(BUILD_DIR); find . -name '*.gcov' -delete