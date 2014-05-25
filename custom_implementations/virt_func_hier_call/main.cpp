#include <iostream>
using namespace std;

struct A;

struct dispatch_fun1 {
	template<class E> inline static void	visit(E* const & e, int i) {
		e->E::fun1(i);
	}
};

struct dispatch_fun2 {
	template<class E> inline static void	visit(E* const & e) {
		e->E::fun2();
	}
};


struct A {
	
	template<class D, typename... Args> inline void		dispatch(Args... a) {
		D::visit(this, a...);
	}
	
	virtual void	fun1(int) { cout << "A::fun1" << endl; }
	virtual void	fun2() { cout << "A::fun2" << endl; }

};

struct B: A {
	
	template<class D, typename... Args> inline void		dispatch(Args... a) {
		A::dispatch<D>(a...);

		D::visit(this, a...);
	}
	
	virtual void	fun1(int) { cout << "B::fun1" << endl; }
	virtual void	fun2() { cout << "B::fun2" << endl; }

};

/*void	dispatch_fun1::visit(A* a) {
	a->call(*this);
}*/

int main() {
	B b;
	
	b.dispatch<dispatch_fun1>(1);
	b.dispatch<dispatch_fun2>();
}


