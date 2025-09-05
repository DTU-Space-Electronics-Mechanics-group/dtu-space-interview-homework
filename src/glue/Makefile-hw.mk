#BCC excecutables
CC = sparc-gaisler-elf-gcc
OBJDUMP = sparc-gaisler-elf-objdump
SIZE = sparc-gaisler-elf-size

AR = sparc-gaisler-elf-ar

#Paths to BCC includes and sources
CCROOT := /opt/${BCC_PREFIX}bcc-${BCC_VERSION}-gcc
BCC_SRC := $(CCROOT)/src/libdrv/src
BCC_INC := $(BCC_SRC)/include
BSP ?= gr740

#Paths to local includes, sources and binaries
ROOTDIR 	:= $(realpath $(dir $(abspath $(lastword $(MAKEFILE_LIST)))))
TARGET		:= hw

SOURCE_DIR		:= $(ROOTDIR)/$(TARGET)
INCLUDE_DIR		:= $(ROOTDIR)
BUILD_DIR 		:= ../../build/

DBG_INC_DIR				:= $(ROOTDIR)/debug-terminal-source
DBG_CIRC_INC_DIR	:= $(DBG_INC_DIR)/circular_hist
BOARD_INC_DIR			:= $(ROOTDIR)/$(TARGET)
DBG_CFG_DIR				:= $(BOARD_INC_DIR)/dbg_cfg
GR740_INC_DIR			:= $(BOARD_INC_DIR)/gr740

LIBGLUE_DIR	:= $(BUILD_DIR)/$(TARGET)/glue

# Compiler flags
_CFLAGS  += -qbsp=$(strip $(BSP))
_CFLAGS  += -O0
_CFLAGS	 += -DDEBUG=0  # Main Files
_CFLAGS  += -mcpu=leon3
_CFLAGS  += -qnano
_CFLAGS  += -qsvt
_CFLAGS  += -std=c99
_CFLAGS  += -Wall -Wextra -pedantic

override CFLAGS := $(_CFLAGS) $(CFLAGS)

_CFLAGS_GDB  += -qbsp=$(strip $(BSP))
_CFLAGS_GDB  += -O0
_CFLAGS_GDB	 += -DDEBUG=0  # Main Files
_CFLAGS_GDB  += -mcpu=leon3
_CFLAGS_GDB  += -qnano
_CFLAGS_GDB  += -qsvt
_CFLAGS_GDB  += -std=c99
_CFLAGS_GDB  += -Wall -Wextra -pedantic
_CFLAGS_GDB  += -ggdb3

override CFLAGS_GDB := $(_CFLAGS_GDB) $(CFLAGS_GDB)

ARFLAGS         = crs

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
LIBGLUE_SRC			= $(shell find $(SOURCE_DIR)/ -type f -name "*.[c]")
LIBGLUE_OBJ			= $(LIBGLUE_SRC:$(SOURCE_DIR)/%.c=$(LIBGLUE_DIR)/%.o)
LIBGLUE_OBJ_GDB	= $(LIBGLUE_SRC:$(SOURCE_DIR)/%.c=$(LIBGLUE_DIR)/%.o)

# Includes for the compiler
_INCLUDES	+= -I$(BCC_INC)
_INCLUDES	+= -I$(INCLUDE_DIR)
_INCLUDES	+= -I$(DBG_INC_DIR)
_INCLUDES	+= -I$(DBG_CIRC_INC_DIR)
_INCLUDES	+= -I$(BOARD_INC_DIR)
_INCLUDES	+= -I$(DBG_CFG_DIR)
_INCLUDES	+= -I$(GR740_INC_DIR)

override LIBGLUE_INC := $(_INCLUDES) $(LIBGLUE_INC)

$(LIBGLUE_DIR):
	@mkdir -p $(LIBGLUE_DIR)

.SECONDEXPANSION:
$(LIBGLUE_OBJ) : $$(patsubst $(LIBGLUE_DIR)/%.o,$(SOURCE_DIR)/%.c,$$@) $(_COMMON_C)
	@mkdir -p $(@D)
	$(CC) -c -o $@ $(CFLAGS) $(LIBGLUE_INC) $<

.SECONDEXPANSION_GDB:
$(LIBGLUE_OBJ_GDB) : $$(patsubst $(LIBGLUE_DIR)/%.o,$(SOURCE_DIR)/%.c,$$@) $(_COMMON_C)
	@mkdir -p $(@D)
	$(CC) -c -o $@ $(CFLAGS_GDB) $(LIBGLUE_INC) $<

libglue:  $(LIBGLUE_DIR) $(LIBGLUE_OBJ)
	@echo "Archiving libglue.a"
	$(AR) $(ARFLAGS) $(LIBGLUE_DIR)/libglue.a $(LIBGLUE_OBJ)

libglue-gdb:  $(LIBGLUE_DIR) $(LIBGLUE_OBJ_GDB)
	@echo "Archiving libglue_gdb.a"
	$(AR) $(ARFLAGS) $(LIBGLUE_DIR)/libglue_gdb.a $(LIBGLUE_OBJ_GDB)

.PHONY: all
all: libglue libglue-gdb
	@echo "finished building all targets"

.PHONY: clean
clean:
	rm -f $(LIBGLUE_OBJ) $(LIBGLUE_DIR)/*.[ao]
