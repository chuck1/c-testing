
inc_paths = -I/usr/include/python3.5
lib_paths = 
libs = -lboost_python-py35 -lpython3.5m

all: libhello.so test

libhello.so: hello.cpp hello.h
	#g++ hello.cpp -c -shared -o libhello.so -std=c++0x ${inc_paths}
	g++ hello.cpp -shared -o libhello.so -fPIC -std=c++0x ${inc_paths} ${libs}

test: main.cpp hello.h
	g++ main.cpp -o test -std=c++0x ${inc_paths} ${lib_paths} ${libs}

clean:
	rm -f libhello.so

