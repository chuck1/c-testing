#include <memory>
#include <iostream>

using namespace std;

struct foo {
	foo() { cout << "ctor" << endl; }
	~foo() { cout << "dtor" << endl; }
	foo(foo const &) { cout << "copy ctor" << endl; }
	foo(foo &&) { cout << "move ctor" << endl; }
};

struct delbase {};

struct del: delbase {
	void operator()(foo* ptr) {
		cout << "deleter" << endl;
		delete ptr;
	}
};

int main() {

	shared_ptr<foo> s(new foo, del());
	
	auto d = get_deleter<del>(s);
	auto e = get_deleter<delbase>(s);

	cout << d << endl;
	cout << e << endl;

}

