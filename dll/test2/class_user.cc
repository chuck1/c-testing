
#include <iostream>
#include <cstdlib>
#include <cstdio>

#include "Helper.hpp"
#include "myclass.h"


using namespace std;

//MyClass*	(*create)();
//void		(*destroy)(MyClass*);

/*
void load(void*& handle,char const * filename) {
	handle = dlopen(filename, RTLD_LAZY);
	if(handle == NULL) {
		cerr << dlerror() << endl;
		exit(0);
	}

	create = (MyClass* (*)())dlsym(handle, "create_object");
	destroy = (void (*)(MyClass*))dlsym(handle, "destroy_object");

	MyClass::create_ = (MyClass* (*)())dlsym(handle, "create_object");

}
*/
int main(int argc, char **argv) {

	// plugin 1
	Helper<MyClass> h1("myclass1.so","MyClass");
	Helper<MyClass> h2("myclass2.so","MyClass");

	MyClass* c1 = h1.create_();
	MyClass* c2 = h2.create_();

	c1->DoSomething();
	c2->DoSomething();

	//delete c1;

	h1.destroy_(c1);
	h2.destroy_(c2);
}


