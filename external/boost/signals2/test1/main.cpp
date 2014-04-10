#include <boost/signals2.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/bind.hpp>

class foo
{
public:
	void	handle(int){}
};


int main()
{

	boost::shared_ptr<foo> f;


	boost::signals2::signal<void(int)> s;


	s.connect( boost::bind( &foo::handle, f, _1 ) );

	s(1);
}

