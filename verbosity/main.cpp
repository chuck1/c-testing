
#include <iostream>

template<typename A>
class bar
{
};

typedef bar< bar<int> > T;

T foo()
{
	std::cout << __PRETTY_FUNCTION__ << std::endl;

	return T();
}


int main()
{

	foo();

}




