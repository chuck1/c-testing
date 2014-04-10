here      := $(shell pwd)
rootname  := C++/
root      := $(shell expr $(here) : '\(.*$(rootname)\)')

mode := lib
os   := lin64

hpaths    :=
hpaths    += $(root)SIG/inc

lpaths    :=

defines   := 
defines   += __DEBUG__
defines   += __LIN__

libraries := 
libraries += glut
libraries += GLU


-include $(root)../make/Makefile.Cpp.mk
