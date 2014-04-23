
class Helper1;
class Helper2;

class Constructor;
class Derived;

/* Creating custom class scopes
 *
 *       common
 *      /  |   \
 *     /   |    \
 * base1  base2  ...
 *    \    |    /
 *     \   |   /
 *      derived
 * 
 * common  - members used by all bases
 * base    - members accessible by friends
 * derived - constructor accessible by friends
 * 
 * the base classes contain member that are accessible only to its friends and derived
 *
 */

class Common {
	protected:
		int data;
};

class Base1: virtual public Common {
	protected:
		friend class Helper1;
		Base1() {}
	private:
		void fun1() { data = 1; }
};

class Base2: virtual public Common {
	protected:
		friend class Helper2;
		Base2() {}
	private:
		void fun2() { data = 2; }
};

class Derived: public Base1, public Base2 {
	protected:
		friend class Constructor;
		Derived() {}
	public:
		void	fun() {
			//Base1::fun1(); // error:
			//Base2::fun2(); // error:
		}
};

class Constructor {
	public:
		Derived*	create() {
			return new Derived;
		}
};	

class Helper1 {
	public:
		void fun1(Derived* d) {
			d->fun1();
			//d->fun2(); // error: ‘void Derived::fun2()’ is protected
		}

		Derived*	create() {
			//return new Derived; // error: ‘Derived::Derived()’ is protected
		}
};
class Helper2 {
	public:
		void fun2(Derived* d) {
			//d->fun1(); // error: ‘void Derived::fun1()’ is protected
			d->fun2();
		}

		Derived*	create() {
			//return new Derived; // error: ‘Derived::Derived()’ is protected
		}
};


int main() {

	//Derived d; // error: ‘Derived::Derived()’ is protected
	
	Helper1 h1;
	Helper2 h2;
	Constructor c;

	Derived* d = c.create();

	h1.fun1(d);
	h2.fun2(d);

	d->fun();

	//d->fun1(); // error: ‘void Derived::fun2()’ is protected
	//d->fun2(); // error: ‘void Derived::fun2()’ is protected

}



