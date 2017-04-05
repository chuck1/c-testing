
#include <iostream>

#include "List.hpp"

using namespace std;

int main()
{
	
	List l;

	l.append(1);
	l.append(2);
	l.append(3);
	l.append(4);
	l.append(5);

	cout << l.fromLast(0)->data << endl;
	cout << l.fromLast(1)->data << endl;
	cout << l.fromLast(2)->data << endl;
	cout << l.fromLast(3)->data << endl;
	cout << l.fromLast(4)->data << endl;
	
}

