#include <iostream>

using namespace std;

#define P cout << __PRETTY_FUNCTION__ << endl

struct A {
	A() { P; }
	A(int) { P; }
};
struct B: virtual A {
	B() { P; }
	//B(int): A(0) { P; }
	//B(int): A(0) { P; }
};
struct C: virtual B {
	C() { P; }
	//C(): B(0) {}
	//C(int): B(0) { P; }
};

struct D: virtual B {
	D() { P; }
	//D(): B(0) {}
	//D(int): B(0) { P; }
};

struct E: C, D {
	E(): A(0) { P; }
};

int main() {
	E e;
}

