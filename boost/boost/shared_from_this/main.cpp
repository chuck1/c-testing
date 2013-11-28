#include <iostream>
#include <memory>

#include <boost/enable_shared_from_this.hpp>
#include <boost/shared_ptr.hpp>

namespace gal
{
	template <class T> class enable_shared_from_this:
		public boost::enable_shared_from_this<T>
	{
	public:
		template <class U> boost::shared_ptr<U> shared_from_this()
		{
			boost::shared_ptr<T> t = boost::enable_shared_from_this<T>::shared_from_this();
			
			return boost::dynamic_pointer_cast<U>( t );
		}
	};
}


class Y:
	public gal::enable_shared_from_this<Y>
{
public:
	Y() {}
	virtual ~Y() {}
};

class Z:
	public Y
{
public:
	Z() {}
	virtual ~Z() {}
};



int main()
{
	boost::shared_ptr<Y> y(new Y);
	
	boost::shared_ptr<Z> z(new Z);
	
	
	
	boost::shared_ptr<Z> a = z->shared_from_this<Z>();
	
	
	
	//y->f();

	//z->f();
	
	return 0;
}



