.PHONY: all
all:	FwProfile-hw FwProfile-pc
	@echo "finished building all targets"

FwProfile-hw:
	@echo "+-------------------------------+"
	@echo "| building fwprofile HW target |"
	@echo "+-------------------------------+"
	make -f ./Makefile-hw.mk all
	@echo "+----------------------------+"
	@echo "| built fwprofile HW target |"
	@echo "+----------------------------+"
	@echo

FwProfile-pc:
	@echo "+------------------------------+"
	@echo "| building fwprofile PC target |"
	@echo "+------------------------------+"
	make -f ./Makefile-pc.mk ifsw
	@echo "+---------------------------+"
	@echo "| built fwprofile PC target |"
	@echo "+---------------------------+"
	@echo

.PHONY: clean
clean:
	make -f ./Makefile-hw.mk clean
	make -f ./Makefile-pc.mk clean
