#include <memory>
#include <iostream>
#include <stdexcept>

template <class T> class shared_ptr:
	public std::shared_ptr<T>
{
public:
	shared_ptr( T* t ):
		std::shared_ptr<T>( t )
	{

	}
	shared_ptr( shared_ptr<T> const & t ):
		std::shared_ptr<T>( static_cast<std::shared_ptr<T> >( t ) )
	{

	}
	shared_ptr( std::shared_ptr<T> const & t ):
		std::shared_ptr<T>( t )
	{

	}
	T* operator->()
	{
		if ( std::shared_ptr<T>::get() == 0 )
		{
			throw std::runtime_error("null pointer");
		}
		return std::shared_ptr<T>::get();
	}
};

class B: public std::enable_shared_from_this<B>
{
public:
	B() {}
	virtual void doit()
	{
		std::cout << "B: " << this << std::endl;
	}
	std::shared_ptr<B> f()
	{
		return shared_from_this();
	}	
};

class C: public B
{
public:
	C() {}
	void doit()
	{
		std::cout << "C: " << this << std::endl;
	}
};

class D: public C
{
public:
	D() {}
};


int main()
{
	shared_ptr<D> d_1( new D );

	
	shared_ptr<B> b = d_1->f();
	
	b->doit();
}


