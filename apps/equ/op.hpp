#ifndef OP_HPP
#define OP_HPP

#include <stdlib.h>
#include <stdio.h>

struct add;
struct op;
struct eq;
struct ptr;

#include "node.hpp"

struct op: public node
{

	op(char const * str, node* l, node* r): node(str), l_(l), r_(r) {}

	virtual ~op() {}

	virtual node*	New(node*, node*) = 0;

	virtual void print()
	{
		printf("(");
		l_->print();
		node::print();
		r_->print();
		printf(")");
	}
	virtual void print_type()
	{
		printf("(");
		l_->print_type();
		node::print();
		r_->print_type();
		printf(")");
	}

	node*		ldist()
	{
		op* o = dynamic_cast<op*>(l_);
		if(o)
		{
			node* ret = o->New(New(o->l_, r_), New(o->r_, r_));
			return ret;
		}
		return 0;
	}


	node*	l_;
	node*	r_;
};

#endif

