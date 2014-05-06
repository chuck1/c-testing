
#include <iostream>
#include <boost/asio.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/bind.hpp>

struct foo {
	~foo() {
		std::cout << "destroyed" << std::endl;
	}
	void print(const boost::system::error_code& /*e*/) {
		std::cout << "Hello, world!\n";
	}
};

void print(const boost::system::error_code& /*e*/) {
	std::cout << "Hello, world!\n";
}

int main() {
	boost::asio::io_service io;

	boost::asio::deadline_timer t(io, boost::posix_time::seconds(5));

	//t.async_wait(&print);

	{
		boost::shared_ptr<foo> f(new foo);
	
		t.async_wait(boost::bind(&foo::print, f, _1));
	}

	io.run();

	return 0;
}





