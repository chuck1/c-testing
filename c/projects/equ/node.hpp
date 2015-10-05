#ifndef NODE_HPP
#define NODE_HPP

#include <stdlib.h>
#include <stdio.h>
#include <memory>

#include "decl.hpp"

#include "add.hpp"
#include "eq.hpp"
#include "NodeBase.hpp"


class Float: public NodeBase
{
	public:
		virtual ~Float() {}

	public:
		friend class ptr;

		Float(float f): f_(f) {}

	public:
		virtual void print()
		{
			printf(" %f ", f_);
		}
	public:
		// math
		Node_s		operator+(Node_s r)
		{
			auto rf = std::dynamic_pointer_cast<Float>(r);
			if(rf)
			{
				return Node_s(new Float(f_ + rf->f_));
			}

			throw 0;
			return Node_s();
		}

		template<typename B> Eq		operator=(B b)
		{
			return Eq(shared_from_this(), b);
		}

		

	private:
		float		f_;

};



#endif
