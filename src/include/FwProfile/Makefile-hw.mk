CC		= 	sparc-gaisler-elf-gcc
BSP 	?= 	gr740

# Compiler flags
_CFLAGS  += -qbsp=$(strip $(BSP))
_CFLAGS  += -Og
_CFLAGS  += -mcpu=leon3
_CFLAGS  += -qnano
_CFLAGS  += -qsvt
_CFLAGS  += -std=c99
_CFLAGS  += -Wall -Wextra -pedantic

override CFLAGS := $(_CFLAGS) $(CFLAGS)

_CFLAGS_GDB  += -qbsp=$(strip $(BSP))
_CFLAGS_GDB  += -Og
_CFLAGS_GDB  += -mcpu=leon3
_CFLAGS_GDB  += -qnano
_CFLAGS_GDB  += -qsvt
_CFLAGS_GDB  += -std=c99
_CFLAGS_GDB  += -Wall -Wextra -pedantic
_CFLAGS_GDB  += -ggdb3

override CFLAGS_GDB := $(_CFLAGS_GDB) $(CFLAGS_GDB)

DEFS		= -DDPU_TARGET

AR		= sparc-gaisler-elf-ar
ARFLAGS		= crs

FWROOT 		= $(shell pwd)
TARGET		= hw
SOURCEDIR	= $(FWROOT)/src
BUILDDIR 	= ../../../build/$(TARGET)/FwProfile

SOURCES		= $(shell ls $(SOURCEDIR)/*.c)
OBJECTS		= $(patsubst %.c,$(BUILDDIR)/%.o,$(notdir $(SOURCES)))

LIBS		= ""
INCLUDE		= ""

ifsw: $(SOURCES)
	@echo "building" $(TARGET) "target"
	mkdir -p $(BUILDDIR)
	# compile
	cd $(BUILDDIR) && $(CC) $(CFLAGS) $(DEFS) -c $(SOURCES)  
	# archive
	cd $(BUILDDIR) && $(AR) $(ARFLAGS) $(BUILDDIR)/libfwprofile.a $(OBJECTS)
	@echo "libfwprofile.a is ready"

ifsw-gdb: $(SOURCES)
	@echo "building" $(TARGET) "target"
	mkdir -p $(BUILDDIR)
	# compile
	cd $(BUILDDIR) && $(CC) $(CFLAGS_GDB) $(DEFS) -c $(SOURCES)  
	# archive
	cd $(BUILDDIR) && $(AR) $(ARFLAGS) $(BUILDDIR)/libfwprofile_gdb.a $(OBJECTS)
	@echo "libfwprofile_gdb.a is ready"

.PHONY: all
all: ifsw ifsw-gdb
	@echo "finished building all targets"

.PHONY: clean
clean:
	rm -f $(BUILDDIR)/*.[ao]