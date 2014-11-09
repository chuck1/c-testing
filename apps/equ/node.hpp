#ifndef NODE_HPP
#define NODE_HPP

#include <stdlib.h>
#include <stdio.h>
#include <memory>

struct add;
struct op;
struct eq;
struct ptr;

struct node;

typedef std::shared_ptr<node> snode;

struct node: public std::enable_shared_from_this<node>
{
	public:
		virtual ~node() {}
	protected:
		friend struct op;
		friend struct ptr;

		node(char const *);
		node(node const & n) {}
		node(node&& n) {}
		node&	operator=(node const & n) { return *this; }


		virtual void print()
		{
			printf(" %s ",str_);
		}
		virtual void printp()
		{
			printf(" %p ", this);
		}
		virtual void	print_type()
		{
			printf(" node ");
		}

		char const * str_;

		// math
		add	operator+(snode n);
		eq	operator=(snode n);
};





#endif
