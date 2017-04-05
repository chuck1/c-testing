#include <stdio.h>


struct foo
{
	void next() {}
	foo& operator++() {}
};

template<typename T, void(T::*v)() = &T::next>
void fun()
{
	printf("1\n");
}
template<typename T, T&(T::*v)() = &T::operator++>
void fun()
{
	printf("2\n");
}

int main()
{
	fun<foo, &foo::next>();
	fun<foo, &foo::operator++>();


}



