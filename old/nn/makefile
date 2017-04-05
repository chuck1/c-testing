cpp_files := main.cpp network.cpp

o_files   := $(patsubst %.cpp, %.o, $(cpp_files))

cflags    := -Wall -std=c++0x

%.o: %.cpp
	@echo compiling $<...
	@g++ $(cflags) -c $< -o $@

all: $(o_files)
	@echo compiling nn...
	@g++ $(cflags) $(o_files) -o nn

clean:
	@rm -f *.o

