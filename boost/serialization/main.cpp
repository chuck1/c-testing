
#include <cstdlib>
#include <iostream>



using namespace std;

struct A {

	static void* operator new(size_t size, int a);

	int a;
};

struct B: A {
	int b;
};

static void* A::operator new(size_t size, int type)
{
	cout << "new A " << size << " " << type << endl;
	cout << "B: " << sizeof(B) << endl;
	
	void* p = malloc(size);
	return p;
}

int main() {


	A* a = new(1) A;



}




