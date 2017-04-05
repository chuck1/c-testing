

#include <memory>
#include <map>


using namespace std;

class foo {
public:
};



class bar: public foo {
public:
};

int main() {

	shared_ptr<foo> f;

	f.reset(new bar());

	shared_ptr<bar> b( new bar() );

	f.reset();

	f = b;


	shared_ptr<foo> f2(b);


	map<int,shared_ptr<foo> > m;

	m[0] = b;




	weak_ptr<foo> fu = f;

	shared_ptr<bar> bu = static_pointer_cast<bar>(fu.lock());











	return 1;

}


