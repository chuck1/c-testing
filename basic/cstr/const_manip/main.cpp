
#include <iostream>
#include <string.h>

using namespace std;

char const * foo(char const * c) {
	cout << "foo" << endl;
	
	cout << "len: " << strlen(c) << endl;
	
	
	char * d = new char[strlen(c)];
	
	memcpy(d,c,strlen(c));

	return d;
}

void func() {

	static char const * s1 = foo(__PRETTY_FUNCTION__);

	cout << s1 << endl;
}

int main() {

	func();
	func();

	
	


	return 0;

}


