#include <stdlib.h>
#include <stdio.h>

struct add;
struct op;
struct eq;
struct ptr;

#include "node.hpp"
#include "op.hpp"
#include "add.hpp"
#include "sub.hpp"
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



add::add(node* l, node* r): op("+", l, r) {}
sub::sub(node* l, node* r): op("-", l, r) {}

/*  mul::mul(node& l, node& r): op("*", l, r) {}
  div::div(node& l, node& r): op("/", l, r) {}
  */


eq::eq(node* l, node* r): op("=", l, r)
{
}


void apply(eq* e, char const * str, node* n) {
}


/*add	operator+(node& n0, node& n1)
  {
  add ret(n0, n1);
  return ret;
  }*/

#include "ptr.hpp"



int main() {

	ptr n0("1");
	ptr n1("2");
	ptr n2("3");

	ptr e = ((n0 + n1) = n2);

	e.print(); printf("\n");

	e += ptr("4");

	e.ldist(); e.print(); printf("\n");

	e -= ptr("5");

	e.print(); printf("\n");

	ptr d(e.get_ldist());
	
	d.print(); printf("\n");

	d.print_type(); printf("\n");

	return 0;
}

