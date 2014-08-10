
libs = -lglut -lGL -lGLU

src = scene.cpp glut.cpp conics.cpp opengl_tools.cpp ellipse.cpp body.cpp

obj = $(patsubst %.cpp, build/%.o, $(src))

flags = -Wall -std=c++0x

inc = -I.

all: build/libconic.a build/test/glut/glut

build/%.o: %.cpp
	mkdir -p $(dir $@)
	g++ -g -c $^ -o $@ $(flags)

build/libconic.a: $(obj)
	ar rcs $@ $(obj)

build/test/glut/glut: test/glut/main.cpp build/libconic.a
	mkdir -p $(dir $@)
	g++ test/glut/main.cpp $(src) -g -o $@ $(inc) $(libs) $(flags)

build/test/conic/conic: test/conic/main.cpp build/libconic.a
	mkdir -p $(dir $@)
	g++ test/conic/main.cpp $(src) -g -o $@ $(inc) $(libs) $(flags) 

clean:
	rm -rf build

