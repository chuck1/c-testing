
#include <iostream>
#include <memory>
#include <map>
#include <utility>

using namespace std;

struct foo {
	public:
		foo() { cout << "ctor" << endl; }
		foo(foo const && f) {
			cout << "move ctor" << endl;
			
		}
		void fun() {}
	private:

		foo(foo const &) { cout << "copy ctor" << endl; }
		foo& operator=(foo const &) { cout << "assignment" << endl; return *this; }
		
};


int main() {
	
	


	map<int,foo> m;
	
	foo f1;
	
	//std::pair<int,foo> p1;
	
	//p1.second.fun();

	//m.at(1);

	m.emplace(1,move(f1));

	//m.insert(p1);

	//m.insert(make_pair(1,f));
}


