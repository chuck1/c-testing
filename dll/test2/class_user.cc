#include <dlfcn.h>
#include <iostream>
#include <cstdlib>
#include "myclass.h"

using namespace std;

MyClass*	(*create)();
void		(*destroy)(MyClass*);

void use() {
	MyClass* myClass = create();
	myClass->DoSomething();
	destroy( myClass );
}

void load(void*& handle,char const * filename) {
	handle = dlopen(filename, RTLD_LAZY);
	if(handle == NULL) {
		cerr << dlerror() << endl;
		exit(0);
	}

	create = (MyClass* (*)())dlsym(handle, "create_object");
	destroy = (void (*)(MyClass*))dlsym(handle, "destroy_object");
}

int main(int argc, char **argv) {

	void* handle = NULL;

	// plugin 1
	load(handle, "myclass1.so");

	use();

	dlclose(handle);

	// plugin 2
	load(handle, "myclass2.so");

	use();

	dlclose(handle);
}


