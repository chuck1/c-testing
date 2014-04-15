#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>

//#include "ctest1.h"

int main(int argc, char **argv) 
{
	void *lib_handle;

	//void (*fn)();

	int x;
	char *error;
	
	char const * libpath = "./libctest.so"; //"/opt/lib/libctest.so";
	
	lib_handle = dlopen(libpath, RTLD_LAZY);
	if (!lib_handle) 
	{
		fprintf(stderr, "%s\n", dlerror());
		exit(1);
	}
	
	void (*fn_hello)() = dlsym(lib_handle, "hello");
	if ((error = dlerror()) != NULL)  
	{
		fprintf(stderr, "%s\n", error);
		exit(1);
	}
	
	void (*fn_world)() = dlsym(lib_handle, "world");
	if ((error = dlerror()) != NULL)  
	{
		fprintf(stderr, "%s\n", error);
		exit(1);
	}
	
	(*fn_hello)();
	(*fn_world)();

	dlclose(lib_handle);
	return 0;
}
