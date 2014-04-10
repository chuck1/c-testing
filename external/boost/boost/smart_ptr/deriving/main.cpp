#include <iostream>

#include <boost/shared_ptr.hpp>

template <class T> class ptr:
	public boost::shared_ptr<T>
{
public:
	ptr( T* t )
	{
		reset( t );
	}
	T*	operator->()
	{
		return boost::shared_ptr<T>::get();
	}
};

struct foo
{

};

int main()
{
	ptr<foo> f( new foo );

	std::cout << f.get() << std::endl;	
}

