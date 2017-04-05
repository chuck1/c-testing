#include <cstdlib>
#include <iostream>
#include <boost/signals2/signal.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/asio.hpp>
#include <thread>


/// hello_world_def_code_snippet
struct HelloWorld 
{
	HelloWorld():a_(0){}
	
	void print(const char* cstr)
	{
		std::cout << a_ << cstr;
	}

	
	int a_;
};

void print(const boost::system::error_code&,boost::asio::deadline_timer* t, int* count)
{
	if (*count < 5)
	{
		std::cout << *count << "\n";
		++(*count);

		t->expires_at(t->expires_at() + boost::posix_time::seconds(1));
		t->async_wait(boost::bind(print,boost::asio::placeholders::error, t, count));
	}
}

class foo
{
public:
	
	
	void do_something()
	{
		
		io_.post(boost::bind(&foo::func, this, 1));
		
		//use_func_ptr( [this](){ cout << "Hello -from foo\n"; } );
	}
	
	void func(int i)
	{
		
	}
	
	boost::asio::io_service io_;
};

int main()
{
	// Signal with no arguments and a void return value
	boost::signals2::signal<void (const char*)> sig;

	// Connect a HelloWorld slot
	HelloWorld hello;
	hello.a_ = 1;

	sig.connect(boost::bind(&HelloWorld::print,&hello,_1));


	

	// Call all of the slots
	sig("Hello");

	hello.a_++;

	sig("World\n");
	
	
	
	
	 
	
	
	
	
	boost::asio::io_service io;
	
	
	
	
	
	/*
	io_service_.post(
		[this, msg]()
		{
			bool write_in_progress = !write_msgs_.empty();
			write_msgs_.push_back(msg);
			if (!write_in_progress)
			{
				do_write();
			}
		});
	*/
	
	
	
	int count = 0;
	boost::asio::deadline_timer t(io, boost::posix_time::seconds(1));

	t.async_wait(
		boost::bind(print,boost::asio::placeholders::error,
		&t,
		&count));

	io.run();

	std::cout << "Final count is " << count << "\n";
	
	return 0;
}

