
inc_paths = -I/usr/include/python2.7
lib_paths = 
libs = -lpython2.7 -lboost_python

all:
	g++ hello.cpp -c -shared -o libhello.so -std=c++0x ${inc_paths}
	g++ main.cpp -o test -std=c++0x ${inc_paths} ${lib_paths} ${libs}

