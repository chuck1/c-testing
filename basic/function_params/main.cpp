
#include <iostream>



void fun(int a[])
{
	std::cout << sizeof(a) << std::endl;

	a[10] = 1; // argh!!!
}

int main()
{

	int a[10];

	fun(a);

}

