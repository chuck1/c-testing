#include <memory>
#include <iostream>

#define FUNC std::cout <<__PRETTY_FUNCTION__ << std::endl

struct foo
{
	virtual ~foo()
	{
		FUNC;
	}
};

struct del
{
	void	operator()(void* f)
	{
		FUNC;
		delete f;
	}
};

struct bar: foo
{
virtual ~bar()
{
	FUNC;
}
};

int main()
{

	std::shared_ptr<bar> f(new bar, del());





}


