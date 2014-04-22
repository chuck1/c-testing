
class Helper;

/* if you want a class or function to have access to only a subset
 * of the private members of your class, derive from a base class
 * that defines that subset of members and the friendship.
 */

class Base {
	public:
		friend class Helper;

	protected:
		void fun1() {}
};

class Derived: public Base {
	protected:
		void fun2() {}

};

class Helper {
	public:
		void fun(Derived& b) {
			b.fun1();
			b.fun2(); // error: ‘void Derived::fun2()’ is protected
		}
};

int main() {

	Derived d;
	
	Helper h;

	h.fun(d);
	
	
	
}



