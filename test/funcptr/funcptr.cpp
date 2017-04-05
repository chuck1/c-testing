#include <iostream>

using namespace std;

class foo
{
public:
	foo(): a(0) {}
	
	int square()
	{
		return a*a;
	}
	
	int a;
};

int main()
{
	int (foo::*functocall)() = NULL;
	
	foo f;
	
	f.a = 3;
	
	functocall = &f.square;
	
	cout << functocall() << endl;
	
	return 0;
}
