#include <set>
#include <iostream>

using namespace std;

struct foo
{
	foo( int i ): i_(i)
	{}
	int i_;

	bool operator<( foo f ) const
	{
		return (i_ < f.i_);
	}
};

int main()
{
	set<foo> a;
	a.insert(foo(3));
	a.insert(foo(1));
	a.insert(foo(2));

	for( auto it = a.begin(); it != a.end(); it++ )
	{
		cout << (*it).i_ << endl;
	}

	return 0;
}






