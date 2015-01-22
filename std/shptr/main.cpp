#include <stdio.h>
#include <memory>

using namespace std;





class bar;

class foo
{
public:
	foo() {
		printf("foo constructor\n");
	}
	foo(foo&) {
		printf("foo copy constructor\n");
	}
	foo(const foo&) {
		printf("foo const copy constructor\n");
	}
	~foo();
	void operator=(foo&)
	{
		printf("foo operator=(foo&)\n");
	}
	
	shared_ptr<bar> b;
};

class bar {
public:
	bar() {
		printf("bar constructor\n");
	}
	~bar() {
		printf("bar destructor\n");
	}
	
	weak_ptr<foo> f;
};

foo::~foo() {
	printf("foo destructor\n");
	printf("b.use_count(): %i\n",b.use_count());
	if (b) {
		printf("b->f.expired(): %i\n",b->f.expired());
	}
}


struct foo_deleter {
	void operator ()( foo const * p) { 
		printf("foo_deleter\n");
		if (p->b) {
			printf("p->b->f.expired(): %i\n",p->b->f.expired());
		}
		delete p; 
	}
};


int main()
{
	shared_ptr<foo> f( new foo(), foo_deleter() );
	f->b = shared_ptr<bar>( new bar() );
	f->b->f = f;
	printf("f->b->f.expired(): %i\n",f->b->f.expired());
	
	return 0;
}

