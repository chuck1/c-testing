ProjectName = charlib

ROOT        = ./../
HOME        = ./
SOURCE      = $(HOME)
INCLUDE     = $(HOME)
LIB         = $(HOME)

-include $(ROOT)make/makefile.Def.mk

libraries    := 
libraries    += $(ROOT)tinyxml/libtinyxml.a
libraries    += $(ROOT)Math/Lib/linux64/libMath.a
libraries    += $(ROOT)StackTrace/Lib/linux64/libStackTrace.a
libraries    += $(ROOT)CommandLine/Lib/linux64/libCommandLine.a
libraries    += $(ROOT)Except/Lib/linux64/libExcept.a

objsdir = obj

libs = $(addprefix $(objsdir)/, $(subst ./, , $(subst ../, , $(subst .a,.a_o, $(libraries)))))

bin := $(LIB)linux64/lib$(ProjectName).a

all: $(bin)

clean:
	@$(ECHO) clean
	@$(RMDIR) $(objsdir)
	@$(RMDIR) *.cppo
	@$(RMDIR) $(bin)

%.a_o:
	@$(ECHO) `dirname $@`
	@$(MKDIR) -p `dirname $@`
	@$(ECHO) copying $@...
	@$(ECHO) filter: %$(subst $(objsdir),,$(subst .a_o,.a,$@))
	@$(ECHO) $(CP) $(filter %$(subst $(objsdir),,$(subst .a_o,.a,$@)), $(libraries)) $@$(subst .a_o,.a,$@)
	@$(CP) $(filter %$(subst $(objsdir),,$(subst .a_o,.a,$@)), $(libraries)) $@
	@$(AR) x $@
	
	
	
$(bin): $(libs)
	@$(ECHO) $(libraries)
	@$(ECHO) $(libs)
	@$(MKDIR) `dirname $(bin)`
	@$(ECHO) $(AR) rcs $(bin) *.cppo *.cpp.o
	@$(AR) rcs $(bin) *.cppo *.cpp.o
	 
	
	
	@$(ECHO) building $@ complete!

