#include <stdio.h>
#include <typeinfo>

void print_byte(void * v, int s) {

	unsigned char * c = (unsigned char*)v;

	for(int i = 0; i < s; ++i) {
		printf("%02X ", c[i]);
	}
	printf("\n");
}


struct chunk {
	void type() {
		printf("%s\n", typeid(*this).name());
	}
	size_t size() {
		return sizeof(__typeof__(*this));
	}
};

struct foo: chunk
{
	foo(){}

	unsigned int c;		// 4
};
struct bar: foo {
	unsigned int d;
};



int main() {

	foo f;
	bar b;
	
	f.type();
	b.type();
	
	printf("%i\n", (int)f.size());
	printf("%i\n", (int)b.size());
	
}


