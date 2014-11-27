#ifndef PTR_HPP
#define PTR_HPP

#include <stdlib.h>
#include <stdio.h>
#include <memory>
#include <cassert>

#include "node.hpp"
#include "op.hpp"
#include "add.hpp"
//#include "sub.hpp"
#include "eq.hpp"



/** @brief pointer
 *
 * hides the pointers of the actual objects
 * handles the construction of appropriate types for various operations
 */
class ptr
{
	public:
		ptr(Node_s a, Node_s b)
		{
			n_ = std::shared_ptr<NodeBase>(new Eq(a, b));
		}
	public:
		ptr(NodeBase* n): n_(n) {
			assert(n_);
		}
		ptr(Node_s n): n_(n) {
			assert(n_);
		}
	public:
		void	print()
		{
			n_->print();
		}
		void	printp()
		{
			n_->printp();
		}
		void	print_type()
		{
			n_->print_type();
		}


		// template math
/*		template<typename T> ptr		operator+(T const & t)
		{
			return ptr(new Add(n_, Node_s(new Node<T>(new T(t)))));
		}
		template<typename T> ptr		operator-(T const & t)
		{
			//return ptr(new sub(n_, Node<T>(new T(t))));
			return ptr();
		}
		
*/

		// math
		ptr		operator+(ptr& p)
		{
			std::cout << __PRETTY_FUNCTION__ << std::endl;
			return ptr(new Add(n_, p.n_));
		}
/*		ptr	operator-(ptr& p)
		{
			return ptr(new sub(n_, p.n_));
		}*/
		ptr	operator=(ptr& p)
		{
			return ptr(new Eq(n_, p.n_));
		}

		void	operator+=(ptr& p)
		{
			n_ = Node_s(new Add(n_, p.n_));
		}
		void	operator+=(ptr&& p)
		{
			n_ = Node_s(new Add(n_, p.n_));
		}

		/*
		void	operator-=(ptr& p)
		{
			n_ = Node_s(new sub(n_, p.n_));
		}
		void	operator-=(ptr&& p)
		{
			n_ = Node_s(new sub(n_, p.n_));
		}
		*/
		// manip
		ptr		resolve()
		{
			return ptr(n_->resolve());
		}
		/*
		ptr	get_ldist()
		{

			auto o = std::dynamic_pointer_cast<Op>(n_);
			if(!o) abort();

			return ptr(o->ldist());

		}
		void	ldist()
		{

			auto o = std::dynamic_pointer_cast<Op>(n_);
			if(o == 0) abort();

			n_ = o->ldist();

		}
		*/
		Node_s		n_;
};


#endif

