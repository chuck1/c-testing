#ifndef __MYCLASS_H__
#define __MYCLASS_H__

#include <dlfcn.h>
#include <iostream>
#include <cstdlib>
#include <cstdio>

using namespace std;

class MyClass {
	public:
		MyClass();

		/* use virtual otherwise linker will try to perform static linkage */
		virtual void DoSomething();

	protected:
		int x;
};

class Helper {
	public:
		Helper(char const * filename) {
			handle_ = dlopen(filename, RTLD_LAZY);
			if(handle_ == NULL) {
				cerr << dlerror() << endl;
				exit(0);
			}
			
			create_	= (MyClass* (*)())dlsym(handle_, "MyClass_create");
			if(create_ == NULL) {
				cerr << dlerror() << endl;
				exit(0);
			}

			destroy_ = (void (*)(MyClass*))dlsym(handle_, "MyClass_destroy");


		}
		~Helper() { dlclose(handle_); }
		
		void*		handle_;
		
		MyClass*	(*create_)();
		void		(*destroy_)(MyClass*);
};


#endif

