LIBS = -lOpenCL


all:
	rm -rf build
	mkdir build
	cat body.h >> build/kernel.cl
	cat kernel.cl.in >> build/kernel.cl
	g++ main.c -g -o build/solve.out $(LIBS) -pthread -std=c++0x
	g++ glut.cpp -g -o build/play.out -std=c++0x -lGL -lglut -lGLU

