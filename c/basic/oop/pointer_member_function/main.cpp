#include <cstdio>
using namespace std;


struct A {
	virtual void doit() {
		//cout << "A" << endl;
	}
};

struct B: A {
	virtual void doit() {
		//cout << "B" << endl;
	}
	void call_
};


typedef void(A::*funA)();
typedef void(B::*funB)();

struct call {};
struct call_doit: call {};

int main() {

}


