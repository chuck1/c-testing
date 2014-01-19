#include <stdio.h>
#include <typeinfo>

void print_byte(void * v, int s) {

	unsigned char * c = (unsigned char*)v;

	for(int i = 0; i < s; ++i) {
		printf("%02X ", c[i]);
	}
	printf("\n");
}

struct base { /*as before */ };

template<typename Derived, typename Base>
struct intermediate : Base {
	virtual size_t size() const { return sizeof(Derived); }
};

struct derived : intermediate<derived, base>
{
int a[10];
};

struct further_derived : intermediate<further_derived, derived>
{
int b[20];
};


int main() {

	derived d0;
	further_derived d1;
	
	
	printf("%i\n", (int)d0.size());
	printf("%i\n", (int)d1.size());
	
}



