#include <iostream>
using namespace std;

struct A {
	void fun() { cout << "A" << endl; }
};

struct B:A {
	void fun() { cout << "B" << endl; }
};

struct C:A {
	void fun() { cout << "C" << endl; }
};

int main() {

	C* c = new C;
	
	c->fun();

	B* b = (B*)c;

	b->fun();
}

