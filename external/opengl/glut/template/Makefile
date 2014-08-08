
libs = -lglut -lGL -lGLU

src = scene.cpp glut.cpp conics.cpp opengl_tools.cpp

all:
	g++ main.cpp $(src) -g -o glut $(libs) -Wall -std=c++0x
	g++ conic_test.cpp $(src) -g -o conic_test $(libs) -Wall -std=c++0x

