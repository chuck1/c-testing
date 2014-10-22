#ifndef ADD_HPP
#define ADD_HPP

#include <stdlib.h>
#include <stdio.h>

struct add;
struct op;
struct eq;
struct ptr;

#include "node.hpp"
#include "op.hpp"


struct add: op {
	add(node*, node*); 
	virtual node*	New(node* a, node* b) { return new add(a,b); }
};



#endif

