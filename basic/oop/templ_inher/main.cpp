struct A{};
struct B:A{};



template <class T> class Foo
{
public:
	void Do(T* const){};
};



template <class T0,class T1> class Bar:
	public Foo<T0>,
	public Foo<T1>
{
public:
	void Do(T1* const);
};


template <class T0,class T1> void Bar<T0,T1>::Do(T1* const p)
{
	Foo<T0>::Do(p);
	Foo<T1>::Do(p);
};

template class Bar<Foo<A>,B>;

int main()
{

}
