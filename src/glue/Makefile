all:	libglue-hw libglue-pc

libglue-hw:
	make -f ./Makefile-hw.mk all

libglue-pc:
	make -f ./Makefile-pc.mk

.PHONY: clean
.IGNORE: clean
clean:
	make -f ./Makefile-hw.mk clean
	make -f ./Makefile-pc.mk clean
