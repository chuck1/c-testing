#include <stdio.h>

#include <map>
#include <memory>

using namespace std;

struct foo {
	foo() {
		printf("ctor\n");
	}
	foo(foo const &) {
		printf("copy ctor\n");
	}
	~foo() {
		printf("dtor\n");
	}
	int d;
};

int main() {

	map<int,shared_ptr<foo>> m;

	{
		shared_ptr<foo> f0(new foo);
		shared_ptr<foo> f1(new foo);
		shared_ptr<foo> f2(new foo);
		shared_ptr<foo> f3(new foo);

		f0->d = 1;
		f1->d = 0;
		f2->d = 1;
		f3->d = 0;

		m[0] = f0;
		m[1] = f1;
		m[2] = f2;
		m[3] = f3;
	}

	printf("loop\n");

/*	auto it = m.begin();
	while(it != m.end()) {
		if(it->second->d) {
			it = m.erase(it);
		} else {
			it++;
		}
	}
*/
	
	auto itc = m.begin();
	auto itp = itc;
	while(itc != m.end()) {
		if(itc->second->d) {
			if(itc == itp) {
				m.erase(itc);
				itc = m.begin();
				itp = itc;
			} else {
				m.erase(itc);
				itc = itp;
				itc++;
			}
		} else {
			itp = itc;
			itc++;
		}
	}
	
	printf("exit\n");

	return 0;
}


