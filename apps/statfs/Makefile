
include_dir = -I/usr/include/python2.7
libs = -lboost_python

all: build/libstatfs.so build/statfs build/dispfs libstatfs.so

build/statfs: statfs.cpp stat.hpp
	mkdir -p build
	g++ statfs.cpp -o build/statfs -std=c++0x

build/dispfs: dispfs.cpp stat.hpp
	mkdir -p build
	g++ dispfs.cpp -o build/dispfs -std=c++0x


build/export.o: export.cpp stat.hpp
	mkdir -p build
	g++ -Wall -fPIC export.cpp -c -o build/export.o -std=c++0x $(include_dir)

build/libstatfs.so: build/export.o
	mkdir -p build
	g++ -shared -Wl,-soname,libstatfs.so.1 -o build/libstatfs.so.1.0 build/export.o -lboost_python $(libs)

	ln -sf libstatfs.so.1.0 build/libstatfs.so.1
	ln -sf libstatfs.so.1.0 build/libstatfs.so

libstatfs.so:
	ln -sf build/libstatfs.so.1.0 libstatfs.so

clean:
	rm -rf build
	rm -f *.so

