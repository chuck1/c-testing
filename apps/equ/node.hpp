#ifndef NODE_HPP
#define NODE_HPP

#include <stdlib.h>
#include <stdio.h>

struct add;
struct op;
struct eq;
struct ptr;

struct node {
	protected:
		friend struct op;
		friend struct ptr;

		node(char const *);
		node(node const & n) {}
		node(node&& n) {}
		node&	operator=(node const & n) { return *this; }

		virtual ~node() {}

		virtual void print()
		{
			printf(" %s ",str_);
		}
		virtual void	print_type()
		{
			printf(" node ");
		}

		char const * str_;

		// math
		add	operator+(node* n);
		eq	operator=(node* n);
};





#endif
