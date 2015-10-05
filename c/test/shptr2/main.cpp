#include <memory>
#include <iostream>
using namespace std;
int main()
{
	shared_ptr<int> a;
	shared_ptr<int> b = a;

	a.reset(new int(1));

	cout << a << endl;

	cout << b << endl;
	
	return 0;
}
