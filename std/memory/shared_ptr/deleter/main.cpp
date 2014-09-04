#include <memory>
#include <iostream>

using namespace std;

struct foo {
	foo() { cout << "ctor" << endl; }
	~foo() { cout << "dtor" << endl; }
	foo(foo const &) { cout << "copy ctor" << endl; }
	foo(foo &&) { cout << "move ctor" << endl; }
};

struct del {
	void operator()(foo* ptr) {
		cout << "deleter" << endl;
		delete ptr;
	}
};

int main() {

	shared_ptr<foo> s(new foo, del());
	

}

