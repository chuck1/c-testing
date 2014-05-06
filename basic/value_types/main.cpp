#include <Verbose.hpp>

/*void foo(int a) {
	cout << "lvalue" << endl;
}*/
void foo(Verbose& v) {
	cout << "lvalue reference" << endl;
	v.speak();
}
void foo(Verbose&& v) {
	cout << "rvalue reference" << endl;
	v.speak();
}

int main () {
	
	Verbose v;
	
	foo(Verbose());
	
	foo(v);
	
	foo(move(v));
	
	
	
}

