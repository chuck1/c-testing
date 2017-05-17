#include <iostream>

class Foo
{
public:
	

};

Foo& operator<<(Foo& f, const char* c)
{
	std::cout << c;
	return f;
}
Foo& operator<<(Foo& f, const int i)
{
	std::cout << i;
	return f;
}
Foo& operator<<(Foo& f, Foo&(*func)(Foo&))
{
	func(f);
	return f;
}
Foo& endl(Foo& f)
{
	std::cout << std::endl;
	return f;
}


int main()
{
	Foo f;

	f << "hello ";
	
	f << 1;

	f << endl;









	return 0;
}

