LIBS = -lOpenCL

all:
	g++ main.cpp other.cpp -g -o solve.out $(LIBS) -pthread -std=c++0x
	g++ glut.cpp -g -o play.out -std=c++0x -lGL -lglut -lGLU

