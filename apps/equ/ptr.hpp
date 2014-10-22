#ifndef PTR_HPP
#define PTR_HPP

#include <stdlib.h>
#include <stdio.h>
#include <memory>

struct add;
struct op;
struct eq;
struct ptr;

#include "node.hpp"
#include "op.hpp"
#include "add.hpp"
#include "sub.hpp"
#include "eq.hpp"

typedef std::shared_ptr<node> snode;


/** @brief pointer
 *
 * hides the pointers of the actual objects
 * handles the construction of appropriate types for various operations
 */
struct ptr
{
	public:
		ptr(char const * s): n_(new node(s)) {}

		ptr(ptr p0, ptr p1)
		{
			n_ = snode(new eq(p0.n_, p1.n_));
		}
	private:
		ptr(node* n): n_(n) {}
		ptr(snode n): n_(n) {}
	public:
		void	print()
		{
			n_->print();
		}
		void	print_type()
		{
			n_->print_type();
		}

		// math
		ptr	operator+(ptr& p)
		{
			return ptr(new add(n_, p.n_));
		}
		ptr	operator-(ptr& p)
		{
			return ptr(new sub(n_, p.n_));
		}
		ptr	operator=(ptr& p)
		{
			return ptr(new eq(n_, p.n_));
		}

		void	operator+=(ptr& p)
		{
			n_ = snode(new add(n_, p.n_));
		}
		void	operator+=(ptr&& p)
		{
			n_ = snode(new add(n_, p.n_));
		}
		void	operator-=(ptr& p)
		{
			n_ = snode(new sub(n_, p.n_));
		}
		void	operator-=(ptr&& p)
		{
			n_ = snode(new sub(n_, p.n_));
		}
		// manip
		ptr	get_ldist()
		{

			sop o = std::dynamic_pointer_cast<op>(n_);
			if(!o) abort();
			
			return ptr(o->ldist());

		}
		void	ldist()
		{

			sop o = std::dynamic_pointer_cast<op>(n_);
			if(o == 0) abort();
			
			n_ = o->ldist();

		}


		snode	n_;
};


#endif

