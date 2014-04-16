
#include <set>
#include <iostream>

using namespace std;

struct foo {
	foo(int na, int nb): a(na), b(nb) {
		cout << "foo ctor" << endl;
	}
	foo(foo const & f): a(f.a), b(f.b) {
		cout << "foo copy ctor" << endl;
	}
	~foo() {
		cout << "foo dtor" << endl;
	}
	int a;
	int b;
};

struct less_foo {
	bool	operator()(foo const & x, foo const & y) {
		if(x.a < y.a) return true;
		if(x.a > y.a) return false;

		return (x.b < y.b);
		//if(x.a < y.a) return true;
		//if(x.a > y.a) return false;
	}
};

int main() {

	std::set<foo, less_foo> s;
	
	s.insert(foo(1,2));
	s.insert(foo(1,3));
	
	cout << "exit" << endl;
}





