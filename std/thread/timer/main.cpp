#include <iostream>
#include <thread>
#include <chrono>

void term_handler()
{
	std::cout << "terminated!" << std::endl;
	abort();
}

template <typename duration_t> struct timer
{
	timer( std::function<void()> func, long int duration, long int repeat = 0 ): duration_(duration), func_(func), repeat_(repeat), t_( &timer::run, this )
	{
	
	}
	~timer()
	{
		t_.detach();
	}
	void run()
	{
		//std::set_terminate( term_handler );

		//std::this_thread::sleep_for( duration_ );
		func_();

		if( repeat_ > 0 )
		{
			while( ( --repeat_ ) > 0 )
			{
				//std::this_thread::sleep_for( duration_ );
				func_();
			}
		}
		if( repeat_ < 0 )
		{
			while(1)
			{
				//std::this_thread::sleep_for( duration_ );
				func_();
			}
		}
	}
	void join()
	{
		t_.join();
	}
	std::thread t_;
	long int duration_;
	std::function<void()> func_;
	long int repeat_;
};

struct foo
{
	foo(): a(0) {}
	void print()
	{
		std::cout << "hello " << a++ << std::endl;
	}
	int a;
};



int main()
{
	std::set_terminate( term_handler );
	
	foo f;

	timer<std::chrono::seconds> t1( std::bind( &foo::print, &f ), 5, 10 );
	timer<std::chrono::seconds> t2( std::bind( &foo::print, &f ), 5, 10 );

	//t.join();

	return 0;
}






