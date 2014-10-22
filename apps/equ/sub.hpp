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
	sub(snode, snode); 
	virtual snode	New(snode a, snode b) { return snode(new sub(a,b)); }
};



#endif

