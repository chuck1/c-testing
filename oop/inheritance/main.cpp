#include <stdio.h>
#include <typeinfo>

void pb(void* v, int c) {
	
	unsigned char* a = (unsigned char*)v;
	unsigned char* b = a + c;
	
	for(; a < b; ++a)
	{
		printf("%02X ", *a);
	}
	printf("\n");
}

struct base {};

template<typename T, typename S> struct serial: S {
//	virtual ~serial() {}
	void size() {
		printf("%i\n", (int)sizeof(T));
		
		pb(this, sizeof(T));
	}
};

struct foo: serial<foo, base> {
	foo(): a(0x0123) {}
//	virtual ~foo() {}
	short a;
};

struct bar: serial<bar, foo> {
	bar(): b(0x4567) {}
	short b;
};

struct cat: serial<cat, bar> {
	cat(): c(0x89AB) {}
	short c;
};

int main() {
	
	foo f;
	bar b;
	cat c;
	
	f.size();
	b.size();
	c.size();
}



