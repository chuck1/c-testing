#include <iostream>
#include <functional>
#include <map>
#include <vector>
#include <sys/time.h>

using namespace std;

// simulate boost signals...

struct signal {
	typedef std::function<void()>	func;

	std::map< int,std::vector<func> >	map_;

	void operator()() {
		for(auto it = map_.cbegin(); it != map_.cend(); ++it) {
			for(auto it2 = it->second.cbegin(); it2 != it->second.cend(); it2++) {
				(*it2)();
			}
		}
	}
};

// ========================================================================

class A {
	public:
		void		foo() {
			cout << "A" << endl;
			sig_();
		}
	protected:
		void		add_sig(std::function<void()> f, int i) {
			sig_.map_[i].push_back(f);
		}
	private:
		signal		sig_;

};


class B: virtual public A {
	public:
		B() {
			add_sig(std::bind(&B::fooB, this), 0);
		}

	private:
		virtual void fooB() {
			cout << "B" << endl;
		}
};


class C: virtual public A {
	public:
		C() {
			add_sig(std::bind(&C::fooC, this), 0);
		}
	private:
		virtual void fooC() {
			cout << "C" << endl;
		}
};



class D: public B, public C {
	public:
		D() {
			add_sig(std::bind(&D::fooD, this), 0);
		}
	private:
		virtual void fooD() {
			cout << "D" << endl;
		}
};


int main () {

	D* d = new D;
	
	A* a = d;
	
	timespec t1,t2;

	clock_gettime(CLOCK_REALTIME, &t1);

	for(int i = 0; i < 100; i++) a->foo();

	clock_gettime(CLOCK_REALTIME, &t2);

	cout << t2.tv_sec << endl;
	cout << t2.tv_sec << endl;

	cout << t2.tv_nsec - t1.tv_nsec << endl;
}


