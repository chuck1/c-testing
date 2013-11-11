ProjectName = PWSX

ECHO        = echo
RMDIR       = rm -fr
MKDIR       = mkdir -p
AR          = ar
CXX         = g++

ROOT        = ./../../../../

cppfiles   := 
cppfiles   += ./../../Model/Model.cpp
cppfiles   += ./../../Model/Model_6.cpp
cppfiles   += ./../../Model/Model_1.cpp
cppfiles   += ./../../Model/Model_2.cpp
cppfiles   += ./../../Model/Model_3.cpp
cppfiles   += ./../../Model/Model_4.cpp
cppfiles   += ./../../Model/Model_5.cpp
cppfiles   += ./../../main.cpp
cppfiles   += ./../../PW/Block/Block.cpp
cppfiles   += ./../../PW/CartSet/CartSet.cpp
cppfiles   += ./../../PW/Connector/Connector.cpp
cppfiles   += ./../../PW/Domain/Domain.cpp
cppfiles   += ./../../PW/PW/PW.cpp
cppfiles   += ./../../PW/BoundaryCondition/BoundaryCondition.cpp
cppfiles   += ./../../PW/VolumeCondition/VolumeCondition.cpp
cppfiles   += ./../../PW/RectangularExtrusion/RectangularExtrusion.cpp
cppfiles   += ./../../PW/Spacing/Spacing.cpp
cppfiles   += ./../../PW/ConnectionBoundaryCondition/ConnectionBoundaryCondition.cpp
cppfiles   += ./../../PW/Pattern/Pattern.cpp
cppfiles   += ./../../PW/Point/Point.cpp


hpaths    := 
hpaths    += ./../../../Include
hpaths    += $(ROOT)

lpaths    :=

defines   := 
defines   += _DEBUG
defines   += _LINUX64
defines   += _OPENGL

libraries := 
libraries += regex

cflags    := 
cflags    += -std=c++0x -g -Wall -Wno-unknown-pragmas
cflags    += $(addprefix -D, $(defines))
cflags    += $(addprefix -I, $(hpaths))

lflags    := 
lflags    += $(addprefix -L, $(lpaths))
lflags    += -Wl,--start-group $(addprefix -l, $(libraries)) -Wl,--end-group

objsdir  = obj
cpp_o    = $(addprefix $(objsdir)/, $(subst ./, , $(subst ../, , $(patsubst %.cpp, %.cpp.o, $(cppfiles)))))
obj      = $(cpp_o)
bin      := ./../../../Bin/linux64/PWSX

all: $(bin)

clean:
	@$(ECHO) clean
	@$(RMDIR) $(objsdir)
	@$(RMDIR) $(bin)

$(bin): $(obj)
	@$(ECHO) comiling $@
	@$(MKDIR) `dirname $@`
	@$(CXX) $(cflags) -o $@ $(obj) $(lflags)
	@$(ECHO) building $@ complete!

%.cpp.o: $(filter %$(strip $(subst .cpp.o,.cpp, $(subst $(objsdir),, $@))), $(%))
	@$(ECHO) compiling $(filter %$(strip $(subst .cpp.o,.cpp, $(subst $(objsdir),, $@))), $(cppfiles))...
	@$(MKDIR) $(dir $(@))
	@$(CXX) $(cflags) -c $(filter %$(strip $(subst .cpp.o,.cpp, $(subst $(objsdir),, $@))), $(cppfiles)) -o $@ $(lflags)
	@$(PARSEDEPEND)
