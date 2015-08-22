#include <sys/time.h>

#define DEBUG

#ifdef DEBUG
#	include <iostream>
#	define PRINT(x) cout << x << endl
#else
#	define PRINT(x)
#endif

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

template<class Dispatcher, class... Subs>
class A {
	public:	
		typedef A<Dispatcher, Subs...> a_type;

		virtual ~A() {}

		int	call() {
			//cout << "A" << endl;

			//PRINT(sizeof...(Subs));
			
			//call<foo, Subs...>(&a_type::foo, ((Subs*)this)...);
			__call<Dispatcher, Subs*...>(
					(dynamic_cast<Subs*>(this))...
					);
		}
};

//================================================================

#define DISPATCH_ROOT(  thisclass, dispatcher, x) public A< dispatcher, thisclass<x...>, x... >
#define DISPATCH_BRANCH(thisclass,     parent, x) public parent< thisclass<x...>, x... >


struct dispatch_foo {
	template<class T> static void call(T *t) { t->foo(); }
};


template<class... Subs> class B: DISPATCH_ROOT(B, dispatch_foo, Subs) {
	public:
		virtual ~B() {}
	private:
		friend class dispatch_foo;
		int foo() {
			PRINT("B");
		}
};

template<class... Subs> class C: DISPATCH_BRANCH(C, B, Subs) {
	private:
		friend class dispatch_foo;
		int foo () {
			PRINT("C");
		}
};

template<class... Subs> class D: DISPATCH_BRANCH(D, B, Subs) {
	private:
		friend class dispatch_foo;
		int foo () {
			PRINT("D");
		}
};

#define DISPATCH_LEAF(thisclass,a,b) public a<b<>, thisclass>, public b<>

class E: DISPATCH_LEAF(E, C, D) {
	public:
		typedef C<D<>, E>::a_type e_type;
	private:
		friend class dispatch_foo;
		int foo () {
			PRINT("E");
		}
};

int main() {

	E* e = new E;
	
	e->E::e_type::call();
	
	
	
	/*
	
	timespec t1,t2;

	clock_gettime(CLOCK_REALTIME, &t1);

	for(int i = 0; i < 100; i++) e->E::e_type::call();


	clock_gettime(CLOCK_REALTIME, &t2);

	cout << t2.tv_sec << endl;
	cout << t2.tv_sec << endl;

	cout << t2.tv_nsec - t1.tv_nsec << endl;
*/
	

}





