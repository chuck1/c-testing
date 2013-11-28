#include <boost/bind.hpp>
#include <boost/function.hpp>

#include <iostream>

using namespace std;


class A
{
public:
	void f(int i)
	{
		cout << i << endl;	
	}
};


class B
{
public:
	
};

int main()
{
	boost::function<void(A*)> func2;
	
	func2 = boost::bind(&A::f,_1,2);

	auto func = boost::bind(&A::f,_1,1);
	
	
	
	
	
	A* a;

	func(a);

	func2(a);

	return 0;
}




