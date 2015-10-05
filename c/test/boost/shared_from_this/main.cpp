#include <iostream>
#include <memory>

#include <boost/enable_shared_from_this.hpp>
#include <boost/shared_ptr.hpp>

class Y;

class Y: public boost::enable_shared_from_this<Y>
{
public:
	boost::shared_ptr<Y> f()
	{
		return shared_from_this();
	}
};

int main()
{
	boost::shared_ptr<Y> y(new Y);

	boost::shared_ptr<Y> z(y.get());

	
	std::cout << y.use_count() << std::endl;
	std::cout << z.use_count() << std::endl;

	boost::shared_ptr<Y> x = y->f();
	
	std::cout << y.use_count() << std::endl;
	std::cout << z.use_count() << std::endl;

	return 0;
}


