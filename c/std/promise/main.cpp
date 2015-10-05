#include <future>
#include <iostream>

using namespace std;

int main()
{
	promise<int> p;
	p.set_value(5);
	
	future<int> f = p.get_future();

	
	
	int i = f.get();
	
	cout << i << endl;
	
	
	
	return 0;
}


