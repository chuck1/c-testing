
#include <memory>
#include <iostream>

using namespace std;

class bar {
	public:
		void fun(shared_ptr<bar> const & b) {
			cout << b.use_count() << endl;
		}
};

class foo {
	public:
		shared_ptr<bar>&	operator->() { return shared_ptr<bar>(b_); }
		
		shared_ptr<bar>		b_;
};

int main () {
	
	foo f;
	f.b_.reset(new bar);
	
	cout << f.b_.use_count() << endl;

	f->fun(f.b_);

	cout << f.b_.use_count() << endl;

	shared_ptr<bar> b(f.operator->());
	
	cout << f.b_.use_count() << endl;
}

