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
	add(snode, snode); 
	virtual snode		New(snode a, snode b) { return snode(new add(a,b)); }
};



#endif

