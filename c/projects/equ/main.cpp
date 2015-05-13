#include <stdlib.h>
#include <stdio.h>
#include <iostream>


#include "node.hpp"
#include "op.hpp"
#include "add.hpp"
//#include "sub.hpp"
#include "eq.hpp"

/*struct sub: op {
  sub(node&, node&);
  };
  struct mul: op {
  mul(node&, node&);
  };
  struct div: op {
  div(node&, node&);
  };*/



//add::add(snode l, snode r): op("+", l, r) {}
//sub::sub(snode l, snode r): op("-", l, r) {}

/*  mul::mul(node& l, node& r): op("*", l, r) {}
  div::div(node& l, node& r): op("/", l, r) {}
  */



//void apply(eq* e, char const * str, node* n) {
//}



/*template<typename T> struct numerical: public node
{
	numerical(T t): node(""), value_(t) {}

	virtual void	print()
	{
		std::cout << " " << value_ << " ";
	}
	virtual void	print_type()
	{
		printf(" numerical ");
	}

	T	value_;
};*/

#include "ptr.hpp"


class Value
{
	public:
		float				value_;
		ptr				units_;
};

class Meter: public NodeBase
{
	virtual void	print()
	{
		printf(" meter ");
	}
};

std::ostream&	operator<<(std::ostream& os, Meter const &)
{
	os << "m";
	return os;
}

void test1()
{
	/*auto n0 = ptr::make<int>(1);
	auto n1 = ptr::make<int>(2);
	auto n2 = ptr::make<int>(3);
	auto n3 = ptr::make<int>(3);
*/
	//auto e = ((n0 + n1) = n2);

	//e.print(); printf("\n");

	//e += n3;

	//e.ldist();
	/*
	   e.print(); printf("\n");

	   e.print_type(); printf("\n");

	   e.printp(); printf("\n");
	   */
}
void test2()
{
	ptr p0(new Meter);
	ptr p1(new Meter);
	
	
	p0.print(); std::cout << std::endl;


	ptr p2 = p0 + p1;

	p2.print_type(); std::cout << std::endl;

}




int main()
{
	ptr a(new Meter);
	ptr b(new Meter);
	
	
	ptr c = a + b;
	
	ptr d = c.resolve();
	
	d.print_type(); std::cout << std::endl;
	d.print(); std::cout << std::endl;

	return 0;	
}







