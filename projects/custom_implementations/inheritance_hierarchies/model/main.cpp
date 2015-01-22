

struct A {
	virtual void fun1() {}
};

struct B : virtual A {
	virtual void fun1() {}

};

struct C : virtual B {

};



struct A_1: virtual A {
	//virtual void fun1() {}

};

struct B_1 : virtual A_1, virtual B {

};

struct C_1 : B_1, C {

};



struct A_1_a: A_1 {

};

struct B_1_a : A_1_a, B_1 {

};

struct C_1_a : B_1_a, C_1 {

};


int main() {

	B_1 b;

}


