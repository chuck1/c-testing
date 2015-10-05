#include <map>
#include <functional>
#include <iostream>
#include <sstream>

struct funcbase {};

template<typename B> struct func: funcbase
{
	std::function<B*()>	f_;
}

std::map<int, funcbase*> funcs;


struct archive
{
	template<typename B, typename D> void	register_pair()
	{
		int hc = typeid(D).hash_code();
		
		func<B>* f = new func<B>;

		f->f_ = std::function<void*()>( [](){ return new D(); } );

		funcs[hc] = 
	}
}
struct oarchive: archive
{
	oarchive(std::stringstream& nss): ss(nss) {}

	template<typename T> void	operator&(T*& t)
	{
		int hc = typeid(*t).hash_code();
		// register
		funcs[hc] = std::function<void*()>( [](){ return new T(); } );
		
		operator&(hc);

		t->serialize(*this);
	}
	
	virtual void	operator&(int v) = 0;

	std::stringstream& ss;
};
struct iarchive
{
	iarchive(std::stringstream& nss): ss(nss) {}

	template<typename T> void	operator&(T* t)
	{
		int hc;

		operator&(hc);

		auto f = funcs[hc];

		t = dynamic_cast<T*>(f());
	}

	virtual void	operator&(int& v) = 0;

	std::stringstream& ss;
};
struct binary_oarchive: oarchive
{
	binary_oarchive(std::stringstream& ss): oarchive(ss) {}

	template<typename T> void	operator&(T* t)
	{
		oarchive::operator&(t);
	}
	virtual void	operator&(int v){ ss.write((const char *)&v, sizeof(int)); }
};
struct binary_iarchive
{

};
struct xml_oarchive: oarchive
{
	xml_oarchive(std::stringstream& ss): oarchive(ss) {}
	template<typename T> void	operator&(T* t)
	{
		oarchive::operator&(t);
	}
	virtual void	operator&(int v){ ss << v << std::endl; }
};
struct xml_iarchive: iarchive
{
	xml_iarchive(std::stringstream& ss): iarchive(ss) {}

	template<typename T> void	operator&(T* t)
	{
		iarchive::operator&(t);
	}

	virtual void	operator&(int& v) {
		char buffer[128];
		ss.getline(buffer,128);
		
		v = atoi(buffer);
	}

};


struct foo
{
	foo() { f = 10; }
	virtual ~foo() {}
	template<class A> void	serialize(A & ar)
	{
		ar & f;
	}
	int f;
};
struct bar: foo
{


};

int main()
{

	std::stringstream ss;

	{
		foo* f = new bar;
	
		xml_oarchive ar(ss);

		ar & f;

		delete f;
	}
	
	std::cout << ss.str() << std::endl;

	{
		foo* f = 0;

		xml_iarchive ar(ss);

		ar & f;

		delete f;
	}

}



