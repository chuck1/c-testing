
class A {
	public:
		int a;
};

class B: private A {
};

class C: public A {
};

class D: public B, public C {
	public:
	D() {
		B::a = 1;
		C::a = 2;
	}
};

int main() {
	D d;
}

