#include <stdio.h>
#include <assert.h>

template<typename T, typename = int>
struct foo
{
	void	operator()()
	{
		printf("no x\n");
	}
	const bool value = false;
};

template<typename T>
struct foo <T, decltype((void) &T::x, 0)>
{
	void	operator()()
	{
		printf("has x\n");
	}
	const bool value = true;
};


struct bar1
{

};

struct bar2
{
	int x;
};

struct bar3
{
	void x() {}
};

int main()
{
	foo<bar1> a;
	a();

	foo<bar2> b;
	b();

	foo<bar3> c;
	c();
	
	assert(0);

	return 0;
}

