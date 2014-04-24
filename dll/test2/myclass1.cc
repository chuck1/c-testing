#include "myclass1.h"
#include <iostream>

using namespace std;

// custom functionality and data

extern "C" MyClass* MyClass_create()
{
	  return new MyClass1;
}
extern "C" void MyClass_destroy( MyClass* object )
{
	MyClass1* c1 = (MyClass1*)object;
	delete c1;
}



MyClass::MyClass()
{
	  x = 20;
}
void MyClass::DoSomething()
{
	  cout<<x<<endl;
}

MyClass1::~MyClass1() {
	cout << "MyClass1 destroy" << endl;
}



MyClass1::MyClass1()
{
	  y = 21;
}

void MyClass1::DoSomething()
{
	  cout << x << " " << y << endl;
}



