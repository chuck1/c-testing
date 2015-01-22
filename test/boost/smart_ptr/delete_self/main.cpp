#include <iostream>

#include <boost/shared_ptr.hpp>

#include <boost/thread.hpp>

class Master;


class Foo
{
public:
	Foo(boost::shared_ptr<Master> master): master_(master){}
	
	void delete_self();
	
	void do_stuff(int);
	
	boost::shared_ptr<Master> master_;
	
};

class Master
{
public:
	boost::shared_ptr<Foo> foo;
	
	void reset_foo()
	{
		foo.reset();
	}
};

void Foo::delete_self()
{
	master_->reset_foo();
	
	//return boost::thread(boost::bind(&Master::reset_foo, master_));
}

void Foo::do_stuff(int a)
{
	std::cout << a << std::endl;
	if ( a > 10 )
	{
		delete_self();
	}
}



int main()
{
	boost::thread t;
	
	boost::shared_ptr<Master> master(new Master);

	
	master->foo.reset(new Foo(master));
	
	int a = 0;
	while (true)
	{
		if (master->foo)
		{
			master->foo->do_stuff(a++);
		}
	}
	
	
	
	t.join();
	
	
}
