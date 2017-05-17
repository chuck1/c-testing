CXX_FLAGS = -std=c++0x -g -Wall -Werror


all:
	g++ -o test main.cpp ${CXX_FLAGS}
asm:
	g++ -S -DASSEMBLY -o main.s main.cpp ${CXX_FLAGS}
