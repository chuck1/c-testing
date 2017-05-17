
class Base
{
protected:
//private:
	Base() {}
};

class Derived: public Base
{
public:
	Derived() {}
};

class Factory
{
public:
	template<typename T>
	T*	 inst()
	{
		return new T;
	}
};

int main()
{
	Factory f;

	f.inst<Derived>();

	//Base* b = new Base;
	//Derived* d = new Derived;

	return 0;
}

