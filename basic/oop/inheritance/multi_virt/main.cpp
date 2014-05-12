#include <iostream>
using namespace std;

template<class F>
void __call() {}





template<typename F, class A, class... B>
void __call(A a, B... b) {

	//a->foo();
	
	if(a == 0) throw 0;

	F::call(a);

	//((*a).*(f))();

	__call<F, B...>(b...);

}

template<class Dispatcher, class... Subs> class A {
	public:	
		typedef A<Dispatcher, Subs...> a_type;

		virtual ~A() {}

		int	call() {
			//cout << "A" << endl;

			cout << sizeof...(Subs) << endl;
			
			//call<foo, Subs...>(&a_type::foo, ((Subs*)this)...);
			__call<Dispatcher, Subs*...>(
					(dynamic_cast<Subs*>(this))...
					);
		}
};

//================================================================

#define DISPATCH_ROOT(thisclass,dispatcher,x) public A< dispatcher, thisclass<x...>, x... >
#define DISPATCH_BRANCH(thisclass,parent,x) public parent< thisclass<x...>, x... >


struct dispatch_foo {
	template<class T> static void call(T *t) { t->foo(); }
};


//template<class... Subs> class B: public A< dispatch_foo, B<Subs...>, Subs... > {
template<class... Subs> class B: DISPATCH_ROOT(B, dispatch_foo, Subs) {
	public:
		virtual ~B() {}
	private:
		friend class dispatch_foo;
		int foo() {
			cout << "B" << endl;
		}
};

//template<class... Subs> class C: public B< C<Subs...>, Subs... > {
template<class... Subs> class C: DISPATCH_BRANCH(C, B, Subs) {
	public:
		//typedef B<C>::a_type c_type;
	private:
		friend class dispatch_foo;
		int foo () {
			cout << "C" << endl;
		}
};


int main() {

	C<>* c = new C<>;


	c->C::a_type::call();

}





