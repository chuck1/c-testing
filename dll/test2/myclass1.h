#ifndef __MYCLASS1_H__
#define __MYCLASS1_H__

#include "myclass.h"

class MyClass1: public MyClass {
	public:
		MyClass1();
		~MyClass1();

		/* use virtual otherwise linker will try to perform static linkage */
		virtual void DoSomething();

	private:
		int y;
};

#endif
