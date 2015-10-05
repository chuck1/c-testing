#ifndef SUB_HPP
#define SUB_HPP

#include <stdlib.h>
#include <stdio.h>


#include "node.hpp"
#include "op.hpp"


class sub: public Op<A,B>
{
	public:
	sub(A a, B b): Op<A,B>("-", a, b) {}
	
	virtual Node_s	New(Node_s a, Node_s b)
	{
		return Node_s(new sub(a,b));
	}
};



#endif

