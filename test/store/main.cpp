#include <iostream>
#include <typeinfo>

using namespace std;

class C0{};
class C1:public C0{};
class C2:public C1{};

template <class A> class Ptr
{
public:
	void Set(A* a)
	{
		cout << typeid(this).name() << endl;
		m_a = a;
	}

	A* m_a;
};

template <class A,class B> class Link:
	virtual public A,
	virtual public B
{
public:
	template <class C> void Set(C* c)
	{
		cout << typeid(this).name() << endl;

		A::Set(c);
		B::Set(c);
	}
};





template class Link<Ptr<C0>,Ptr<C1> >;

typedef Link<Ptr<C0>,Ptr<C1> >	L01;



template class Link<L01,	Ptr<C2> >;

typedef Link<L01,Ptr<C2> >		L12;





template void L01::Set<C1>(C1*);
template void L12::Set<C2>(C2*);



class F0:
	virtual public Ptr<C0>
{

};

class F1:
	virtual public F0,
	virtual public L01
{

};

class F2:
	virtual public F1,
	virtual public L12
{

};

int main()
{
	C2* c2 = new C2;

	F2 f2;

	f2.L12::Set(c2);
	
	cout << f2.Ptr<C0>::m_a << endl;
	cout << f2.Ptr<C1>::m_a << endl;
	cout << f2.Ptr<C2>::m_a << endl;
	
	delete c2;

	return 0;
}

