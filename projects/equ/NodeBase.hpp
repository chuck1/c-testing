#ifndef NODEBASE_HPP
#define NODEBASE_HPP

#include <stdlib.h>
#include <stdio.h>
#include <memory>

#include "decl.hpp"


class NodeBase: public std::enable_shared_from_this< NodeBase >
{
	public:
		virtual ~NodeBase() {}

		virtual void	print() = 0;
		virtual void	print_type()
		{
			std::cout << typeid(*this).name();
		}
		void		printp()
		{
			printf(" %p ", this);
		}
		
		virtual Node_s	resolve()
		{
			throw 0;
		}

		virtual Node_s	resolve_add(Node_s)
		{
			throw 0;
		}

		virtual Node_s		operator+(Node_s)
		{
			throw 0;
			return Node_s();
		}

};




#endif
