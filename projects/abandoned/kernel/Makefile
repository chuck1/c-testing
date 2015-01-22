here      := $(shell pwd)
rootname  := C++/
root      := $(shell expr $(here) : '\(.*$(rootname)\)')



hpaths    := 
hpaths    += $(root)kernel/inc
hpaths    += $(root)external/PhysX/Include
hpaths    += $(root)external/glew/include
hpaths    += $(root)external
hpaths    += $(root)jess/inc


defines   := 
defines   += __DEBUG__
defines   += __LIN__

-include $(root)make/Makefile.Lib.mk
