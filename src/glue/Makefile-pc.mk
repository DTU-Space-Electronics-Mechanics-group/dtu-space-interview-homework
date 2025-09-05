#compiler
CC		:= gcc
CFLAGS	:= -O0 -W -Wall -Wextra -Wno-variadic-macros -Wno-address-of-packed-member -std=gnu99 -pedantic -ggdb 
CFLAGS	+= -Wno-type-limits -Wno-unused -Wno-format
CFLAGS	+= -DWITH_FORK

#linker
LD		:= gcc

#archiver
AR		:= ar
ARFLAGS	:= crs

#paths
ROOTDIR 	:= $(realpath $(dir $(abspath $(lastword $(MAKEFILE_LIST)))))
TARGET		:= pc

SOURCE_DIR		:= $(ROOTDIR)/$(TARGET)
INCLUDE_DIR		:= $(ROOTDIR)
BUILD_DIR 		:= ../../build

DBG_INC_DIR				:= $(ROOTDIR)/debug-terminal-source
DBG_CIRC_INC_DIR	:= $(DBG_INC_DIR)/circular_hist
PC_INC_DIR				:= $(ROOTDIR)/$(TARGET)
DBG_CFG_DIR				:= $(PC_INC_DIR)/dbg_cfg

LIBGLUE_DIR	:= $(BUILD_DIR)/$(TARGET)/glue


LIBGLUE_SRC := \
    $(shell find $(PC_INC_DIR) -type f -name "*.c") \
    $(shell find $(DBG_INC_DIR) -type f -name "*.c")

# Generate .o file paths in build/pc/glue, preserving relative paths
LIBGLUE_OBJ := $(patsubst $(ROOTDIR)/%, $(LIBGLUE_DIR)/%, $(LIBGLUE_SRC:.c=.o))

# Includes for the compiler
_INCLUDES	+= -I$(INCLUDE_DIR)
_INCLUDES	+= -I$(DBG_INC_DIR)
_INCLUDES	+= -I$(DBG_CIRC_INC_DIR)
_INCLUDES	+= -I$(PC_INC_DIR)
_INCLUDES	+= -I$(DBG_CFG_DIR)

override LIBGLUE_INC := $(_INCLUDES) $(LIBGLUE_INC)

#RULES#
#----------------------------------------------------------------------------------------------#
.PHONY: all
all:	libglue
	@echo "finished building pc target"

$(LIBGLUE_DIR):
	@mkdir -p $(LIBGLUE_DIR)

.SECONDEXPANSION:
$(LIBGLUE_DIR)/%.o: $(ROOTDIR)/%.c
	@echo "Building object file $@ from $<"
	@mkdir -p $(@D)
	$(CC) -c -o $@ $(CFLAGS) $(LIBGLUE_INC) $<

libglue:  $(LIBGLUE_OBJ) $(LIBGLUE_DIR)
	@echo "creating static library $@"
	$(AR) $(ARFLAGS) $(LIBGLUE_DIR)/libglue.a $(LIBGLUE_OBJ)


.PHONY: clean
clean:
	rm -f $(LIBGLUE_OBJ) $(LIBGLUE_DIR)/*.[ao]