CC		= gcc
CFLAGS		= -O0 -W -Wall -Wextra -Werror -std=gnu89 -pedantic -ggdb #-m32
DEFS		= -DPC_TARGET

AR		= ar
ARFLAGS		= crs

FWROOT 		= $(shell pwd)
TARGET		= pc
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

.PHONY: all
all:	ifsw
	@echo "finished building all targets"

.PHONY: clean
clean:
	rm -f $(BUILDDIR)/*.[ao]

