#include <iostream>
#include <memory>
using namespace std;

class Child;

struct Parent {
	Parent() { cout << "parent ctor" << endl; }
	~Parent() { cout << "parent dtor" << endl; }
	
	void release();

	shared_ptr<Child>		child_;
};

struct Child {

	Child(std::shared_ptr<Parent> parent): parent_(parent) {
		cout << "child ctor" << endl;
	}
	~Child() {
		cout << "child dtor" << endl;
		parent_.reset();
	}
	
	
	shared_ptr<Parent>		parent_;
};

void Parent::release() {
	child_.reset();
}

int main() {

	shared_ptr<Parent>		parent(new Parent);
	
	parent->child_.reset(new Child(parent));
	
	parent->release();
}


