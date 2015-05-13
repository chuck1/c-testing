
#include <boost/thread/future.hpp>

#include <iostream>

using namespace boost;

int main()
{

	std::cout << BOOST_VERSION << std::endl;
/*
	boost::future<int> f1 = async([]() { return 123; });
	future<string> f2 = f1.then([](future<int> f) {
			return f.get().to_string(); // here .get() won't block
			});

	std::cout << f2.get() << std::endl;
*/
	return 0;
}

