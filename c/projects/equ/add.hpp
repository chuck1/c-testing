#ifndef ADD_HPP
#define ADD_HPP

#include <stdlib.h>
#include <stdio.h>


#include "node.hpp"
#include "op.hpp"

typedef char yes;
typedef char (&no)[2];

//struct anyx { template <class T> anyx(const T &); };

no operator + (const anyx &, const anyx &);
no operator + (const anyx &, const anyx &);


template <class T> yes check(T const&);
no check(no);

template <typename A, typename B>
struct has_add {
	static A & a;
	static B & b;
	static const bool value = sizeof(check(a + b)) == sizeof(yes);
};




//class add: public Op
class Add: public Op
{
	public:

		Add(Node_s a, Node_s b): Op("+", a, b) {}

		Node_s		New(Node_s a, Node_s b)
		{
			return Node_s(new Add(a,b));
		}

		Node_s		ldist()
		{
			auto o = std::dynamic_pointer_cast<Op>(l_);
			if(o)
			{
				//typedef add<typename A::L, B> nL;
				//typedef add<typename A::R, B> nR;

				auto l = New(o->l_, r_);
				auto r = New(o->r_, r_);

				auto ret = o->New(l, r);

				return ret;
			}


			return Node_s();

		}

		virtual Node_s		resolve()
		{
			//std::cout << has_add<A,B>::value;

			//((*l_) + (*r_))

			//return l_->resolve_add(r_);

			auto res = l_->operator+(r_);

			return res;
		}
};



#endif

