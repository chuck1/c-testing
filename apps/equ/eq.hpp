#ifndef EQ_HPP
#define EQ_HPP

#include "op.hpp"

struct eq: op {

	eq(snode, snode);

	virtual snode	New(snode a, snode b) { return snode(new eq(a,b)); }


	/*	void mul_post(node* n) {
		mul* l = new mul(l_, n);
		mul* r = new mul(r_, n);

		l_ = l;
		r_ = r;
		}*/
};


#endif
