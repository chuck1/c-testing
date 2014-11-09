#ifndef OP_HPP
#define OP_HPP

#include <stdlib.h>
#include <stdio.h>

struct add;
struct op;
struct eq;
struct ptr;

#include "node.hpp"

struct op;

typedef std::shared_ptr<op> sop;

struct op: public node
{

	op(char const * str, snode l, snode r): node(str), l_(l), r_(r) {}

	virtual ~op() {}

	virtual snode	New(snode, snode) = 0;

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
	virtual void	printp()
	{
		printf("(");
		l_->printp();
		node::print();
		r_->printp();
		printf(")");
	}

	snode		ldist()
	{
		sop o = std::dynamic_pointer_cast<op>(l_);
		if(o)
		{
			snode ret = o->New(New(o->l_, r_), New(o->r_, r_));
			return ret;
		}
		return snode();
	}


	snode	l_;
	snode	r_;
};

#endif

