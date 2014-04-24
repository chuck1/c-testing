#include "myclass.h"
#include <iostream>

using namespace std;

// custom functionality

extern "C" MyClass* MyClass_create()
{
	  return new MyClass;
}

extern "C" void MyClass_destroy( MyClass* object )
{
	  delete object;
}

MyClass::MyClass()
{
	  x = 40;
}

void MyClass::DoSomething()
{
	  cout<<x<<endl;
}
