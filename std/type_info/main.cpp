
#include <typeindex>
#include <iostream>

using namespace std;

struct foo {
	virtual ~foo() {}
	void	type() {
		
		std::type_index type(typeid(*this));
		
		cout << type.name() << " " << type.hash_code() << endl;
	}
	foo*	alloc() {
		return new __typeof__(*this);
	}
};

struct bar: foo {};

int main() {
	
	foo* f = new bar;
	
	f->type();
	
}


