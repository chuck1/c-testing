ProjectName = NetworkTest1

FILE        = makefile

ROOT        = ./../../../../
SOURCE      = ./../../
BIN			= ./../../../bin/linux64/

-include $(ROOT)make/makefile.Def.mk


cppfiles   := 
cppfiles   += $(SOURCE)main.cpp


hpaths    := 
hpaths    += ./../../../include
hpaths    += $(ROOT)Network/include

lpaths    := 
lpaths    += $(ROOT)Network/lib/linux64

defines   := 


libraries := Network


-include $(ROOT)make/makefile.Bin.mk

