#include <iostream>

using namespace std;

enum Flag
{
	e_FIRST = (1 << 0),
	e_SECOND = (1 << 1),
	e_THIRD = (1 << 2)
};

int main()
{
	cout << e_FIRST << endl;
	cout << e_SECOND << endl;
	cout << e_THIRD << endl;
	cout << ( e_FIRST | e_SECOND ) << endl;
	
	int condition = e_FIRST | e_SECOND;
	
	cout << ( e_THIRD & condition ) << endl;
	
	return 0;
}