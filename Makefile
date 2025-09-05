.PHONY: all
all:	xgis-dhu-asw-hw xgis-dhu-asw-pc
	@echo "finished building all targets"

xgis-dhu-asw-hw:
	@echo "+-----------------------------------------+"
	@echo "| building XGIS DHU ASW HW target |"
	@echo "+-----------------------------------------+"
	make -f Makefile-hw.mk all
	@echo "+--------------------------------------+"
	@echo "| built XGIS DHU ASW HW target |"
	@echo "+--------------------------------------+"
	@echo

xgis-dhu-asw-pc:
	@echo "+-----------------------------------------+"
	@echo "| building XGIS DHU ASW PC target |"
	@echo "+-----------------------------------------+"
	make -f Makefile-pc.mk all
	@echo "+--------------------------------------+"
	@echo "| built XGIS DHU ASW PC target |"
	@echo "+--------------------------------------+"
	@echo

.PHONY: clean
.IGNORE: clean
clean:
	make -f Makefile-hw.mk clean
	make -f Makefile-pc.mk clean