#include <iostream>
#include <thread>

using namespace std;

struct foo
{
	void	print()
	{
		cout << "hello" << endl;
	}
};

int main()
{
	foo f;
	
	thread t( &foo::print, std::ref(f) );

	t.join();

	return 0;
}






