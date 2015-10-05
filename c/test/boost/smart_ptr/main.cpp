#include <boost/shared_ptr.hpp>

class A{};
class B:public A{};

int main()
{
	boost::shared_ptr<A> p1;

	p1.reset(new B);
	
	boost::shared_ptr<B> p2 = p1;
	
	
	return 0;
}