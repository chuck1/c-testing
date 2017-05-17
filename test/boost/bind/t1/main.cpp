#include <iostream>
#include <boost/bind.hpp>
#include <boost/function.hpp>




struct Foo
{
	void (*handle_)(int);

	boost::function< void (int) > func_;

	void go()
	{
		func_(1);
	}

};

void f1(int a)
{
	std::cout << "f1" << std::endl;
}

void f2(int a)
{
	std::cout << "f2" << std::endl;
}

void f3(int a,double b)
{
	std::cout << "f3" << std::endl;
}

int main()
{
	Foo f;

	f.func_ = &f1;

	f.go();

	f.func_ = boost::bind(f2, _1);

	f.go();

	f.func_ = boost::bind(f3, _1, 1.1);

	f.go();



}








