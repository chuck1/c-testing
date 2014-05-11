#include <iostream>
#include <typeinfo>
#include <string>
using namespace std;

void whats_my_arg(int(*f)()) {
	cout << "int(*)()" << endl;

	(*f)();
}

template<class T>
void whats_my_arg(T t) {
	cout << typeid(t).name() << endl;
}

struct bar {};

int foo() { cout << "foo" << endl; }

int main() {

	whats_my_arg(0);
	whats_my_arg("1");
	whats_my_arg(1.4);
	whats_my_arg(bar());
	whats_my_arg(foo);
	whats_my_arg(bar());
	whats_my_arg(bar());


	return 0;	
}

