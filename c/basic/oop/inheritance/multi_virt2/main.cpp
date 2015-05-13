
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

template<class Dispatcher, class... Subs> class A {
	public:	
		typedef A<Dispatcher, Subs...> a_type;

		virtual ~A() {}

		int	call() {
			//cout << "A" << endl;

			PRINT(sizeof...(Subs));
			
			//call<foo, Subs...>(&a_type::foo, ((Subs*)this)...);
			__call<Dispatcher, Subs*...>(
					(dynamic_cast<Subs*>(this))...
					);
		}
};

//================================================================


struct dispatch_foo {
	template<class T> static void call(T *t) { t->foo(); }
};


class B {
	public:
		virtual ~B() {}
	private:
		friend class dispatch_foo;
		int foo() {
			PRINT("B");
		}
};

class C: virtual public B {
	private:
		friend class dispatch_foo;
		int foo () {
			PRINT("C");
		}
};

class D: virtual public B {
	private:
		friend class dispatch_foo;
		int foo () {
			PRINT("D");
		}
};


class E: public C, public D {
	private:
		friend class dispatch_foo;
		int foo () {
			PRINT("E");
		}
};

int main() {

	E* e = new E;
	
	dispatch_foo::call(e);

}





