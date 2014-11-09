#include <iostream>

#define FUNC std::cout << __PRETTY_FUNCTION__ << std::endl

struct foo
{
	virtual void fun() { FUNC; }
};
struct hello: foo
{

};
struct bar: hello
{
	virtual void fun() { FUNC; }

};

int main()
{

	foo* f = new bar;


	f->fun();
	f->foo::fun();

	bar* b;
	
	
	b->hello::fun();
}


