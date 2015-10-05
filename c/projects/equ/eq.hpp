#ifndef EQ_HPP
#define EQ_HPP

#include "op.hpp"

class Eq: public Op
{
	public:
		Eq(Node_s a, Node_s b): Op("=", a, b) {}

		virtual Node_s	New(Node_s a, Node_s b)
		{
			return Node_s(new Eq(a,b));
		}


		/*	void mul_post(node* n) {
			mul* l = new mul(l_, n);
			mul* r = new mul(r_, n);

			l_ = l;
			r_ = r;
			}*/
};


#endif
