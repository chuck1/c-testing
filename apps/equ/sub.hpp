#ifndef SUB_HPP
#define SUB_HPP

#include <stdlib.h>
#include <stdio.h>

struct add;
struct op;
struct eq;
struct ptr;

#include "node.hpp"
#include "op.hpp"


struct sub: op {
	sub(node*, node*); 
	virtual node*	New(node* a, node* b) { return new sub(a,b); }
};



#endif

