
struct bar
{

};

template <class A> struct desc
{
	typedef A ptr_t;
	
	A* a;
};

struct factory
{
	template <class A> A*	create()
	{
		return (new A);
	}
};

int main()
{
	factory f;
	
	desc<int> d;
	
	desc<int>::ptr_t i;
	
	int* ip = f.create<int>();
	
	d.a = f.create<int>();
}

