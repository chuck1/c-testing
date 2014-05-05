
#include <iostream>

using namespace std;

struct foo {
	virtual ~foo() {}
	virtual void fun() { cout << "foo" << endl; }
};
struct bar: foo {
	virtual ~bar() {}
	virtual static void fun() { cout << "bar" << endl; }
};

int main() {}



