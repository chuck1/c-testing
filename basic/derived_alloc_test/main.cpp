
#include <iostream>

#define CALL_FN(ptrToFunc) (*(ptrToFunc))

using namespace std;

class Foo {
	public:
		Foo(){ cout << "Foo constructor\n"; }
		virtual	~Foo(){ cout << "Foo destructor\n"; }

};

class Bar: public Foo {
	public:
		Bar(){ cout << "Bar constructor\n"; }
		~Bar(){ cout << "Bar destructor\n"; }
};

template <class T,class U> void allocate( T*& ptr ) {
	ptr = new U;
}

//template void allocate<Bar,Bar>(Bar*);

typedef void (*funcPtr)(Foo*&);


int main() {
	Foo* foo = 0;

	funcPtr f = &allocate<Foo,Bar>;

	CALL_FN(f)(foo);

	cout << foo << "\n";

	delete foo;

	return 0;
}

