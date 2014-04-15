#include <cstdio>

template <typename A> class foo {
	public:
		foo(A a): a_(a) {}
		void	print();
		A	a_;
};



template <> void foo<int>::print() {
	printf("%i\n",a_);
}

template <> void foo<double>::print() {
	printf("%lf\n",a_);
}

struct S {};

int main() {
	
	

	foo<int> f(1);
	f.print();

	foo<double> d(1);
	d.print();

}

