#LIBS = -lOpenCL
LIBS = -lOpenCL -lGL -lglut -lGLU
#LIBS = -l/usr/lib/x86_64-linux-gnu/libOpenCL.so

SRC = src/other.cpp src/step_pairs.cpp src/step_bodies.cpp src/kernel.cpp src/universe.cpp src/Frame.cpp

O_FILES = $(patsubst src/%.cpp, build/%.o, $(SRC))


all: play.out solv.out

play.out: $(O_FILES) build/glut.o
	@echo link $@
	@g++ -g -o $@ build/glut.o $(O_FILES) $(LIBS) -I. -std=c++0x

solv.out: $(O_FILES) build/main.o
	@echo link $@
	@g++ -g -o $@ build/main.o $(O_FILES) $(LIBS) -I. -pthread -std=c++0x

$(O_FILES) build/main.o build/glut.o: build/%.o: src/%.cpp body.h
	@echo build $@
	@mkdir -p $(dir $@)
	@g++ -g -c -o $@ $< -I. -std=c++0x

clean:
	rm -rf build/

cleandata:
	rm -f data_*

