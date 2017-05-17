#include <stdio.h>

#include <set>
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

	set<shared_ptr<foo>> s;

	shared_ptr<foo> f4(new foo);
	
	{
		shared_ptr<foo> f0(new foo);
		shared_ptr<foo> f1(new foo);
		shared_ptr<foo> f2(new foo);
		shared_ptr<foo> f3(new foo);
		

		f0->d = 1;
		f1->d = 0;
		f2->d = 1;
		f3->d = 0;
		f4->d = 0;

		s.insert(f0);
		s.insert(f1);
		s.insert(f2);
		s.insert(f3);
		s.insert(f4);
	}

	f4.reset();

	auto itc = s.begin();
	auto itp = itc;
	while(itc != s.end()) {
		if((*itc)->d) {
			if(itc == itp) {
				s.erase(itc);
				itc = s.begin();
				itp = itc;
			} else {
				s.erase(itc);
				itc = itp;
				itc++;
			}
		} else {
			s.insert(f4);

			itp = itc;
			itc++;
		}
	}
	
	printf("exit\n");

	return 0;
}


