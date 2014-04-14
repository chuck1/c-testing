
#include <cstdio>

struct Foo {
	Foo(): c(a) {}

	double	a;
	double&	b() {return a; }
	double& c;
};

int main() {

	printf("%i\n",(int)sizeof(double));
	printf("%i\n",(int)sizeof(Foo));
	
	Foo f;

	f.b() = 10;

	printf("%f\n", f.a);
	printf("%f\n", f.b());

}

