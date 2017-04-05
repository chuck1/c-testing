
HPP_FILES = $(shell find . -name *.hpp)

CPP_FILES = $(shell find . -name *.cpp)

BIN_FILES = $(patsubst ./%.cpp, build/%, $(CPP_FILES))

all: $(BIN_FILES)

help:
	@#echo $(CPP_FILES)
	@#echo $(BIN_FILES)

$(BIN_FILES): build/% :./%.cpp $(HPP_FILES)
	@mkdir -p $(dir $@)
	g++ -g $< -o $@

