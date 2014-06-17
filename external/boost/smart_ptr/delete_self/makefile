hpaths := /nfs/stak/students/r/rymalc/cfs/code/cpp/boost_1_54_0


lpaths := /nfs/stak/students/r/rymalc/cfs/code/cpp/boost_1_54_0/stage/lib

lflags := $(addprefix, -L, $lpaths)

pre := -Wl,-rpath,

rpaths := $(addprefix $(pre), $(lpaths))

cflags    := 
cflags    += -Wall -pthread -std=c++0x
cflags    += $(addprefix -I, $(hpaths))

lflags    := 
lflags    += $(addprefix -L, $(lpaths))

all:
	@clear
	@g++ -o m main.cpp $(cflags) $(lflags) -lboost_system -lboost_thread $(rpaths)

	
	