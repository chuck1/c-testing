HPATH = -I/usr/include/nvidia-current/
LPATH = -L/usr/lib/nvidia-current/
LIBS = -lOpenCL


all:
	g++ main.c -o solve.out $(HPATH) $(LIBS) -pthread -std=c++0x
	g++ glut.cpp -o play.out -std=c++0x -lGL -lglut -lGLU

