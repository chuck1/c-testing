#LIBS = -lOpenCL
LIBS = -lOpenCL
#LIBS = -l/usr/lib/x86_64-linux-gnu/libOpenCL.so

SRC = other.cpp src/step_pairs.cpp src/step_bodies.cpp src/kernel.cpp src/universe.cpp src/Frame.cpp

all:
	g++ main.cpp $(SRC) -g -o solve.out $(LIBS) -I. -pthread -std=c++0x
	g++ glut.cpp $(SRC) -g -o play.out $(LIBS) -I. -std=c++0x -lGL -lglut -lGLU

