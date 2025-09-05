#!/bin/bash

##FOR GR716a##
#cginit: initializes the memory controller clockgate
#u : routes the standard out to grmon 
#grmon3 -uart /dev/ttyUSB1 -gdb -cginit -u

##FOR GR740 DEV BOARD##
#cginit: initializes the memory controller clockgate
#u : routes the standard out to grmon 
grmon4 -ftdi -gdb -cginit -u