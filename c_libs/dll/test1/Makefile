all:

ctest:
	gcc -Wall -fPIC -c ctest1.c ctest2.c
	gcc -shared -Wl,-soname,libctest.so.1 -o libctest.so.1.0 ctest1.o ctest2.o
	
	ln -sf libctest.so.1.0 libctest.so
	ln -sf libctest.so.1.0 libctest.so.1
	
cprog:
	gcc -Wall -Wl,-rpath,. -L. cprog.c -lctest -o cprog
	
	export LD_LIBRARY_PATH=.
	
	./cprog

progdl: progdl.c
	gcc -rdynamic progdl.c -ldl -o progdl
	export LD_LIBRARY_PATH=.
	./progdl

