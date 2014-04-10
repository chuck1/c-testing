#include <memory>

#include <boost/numeric/ublas/vector.hpp>

using namespace std;

class Base: public enable_shared_from_this<Base>
{
public:
	void doit()
	{
		shared_ptr<Base> ptr( shared_from_this() );
	}
};

class Foo: public Base
{
public:
	virtual void something() {}

	shared_ptr<float> f;
	
	weak_ptr<int> i;
	
	boost::numeric::ublas::vector<float> v;
};

int main()
{
	shared_ptr<Foo> f( new Foo );
	
	f->doit();
	
	return 0;
}
