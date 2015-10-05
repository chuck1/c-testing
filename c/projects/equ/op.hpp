#ifndef OP_HPP
#define OP_HPP

#include <stdlib.h>
#include <stdio.h>
#include <string>
#include <iostream>

#include "NodeBase.hpp"

namespace private_impl {
	typedef char yes;
	typedef char (&no)[2];

	struct anyx { template <class T> anyx(const T &); };

	no operator << (const anyx &, const anyx &);
	no operator >> (const anyx &, const anyx &);
	
	
	template <class T> yes check(T const&);
	no check(no);

	template <typename StreamType, typename T>
		struct has_loading_support {
			static StreamType & stream;
			static T & x;
			static const bool value = sizeof(check(stream >> x)) == sizeof(yes);
		};
}

struct anyx {
	template <class T> anyx(const T &) {}
};

/*static inline std::ostream& operator<<(std::ostream& os, const anyx &)
//std::ostream& operator<<(std::ostream& os, const anyx &)
{
	os << "ERROR";
	return os;
}*/


//class Op: public NodeBase
class Op: public NodeBase
{
	public:
		virtual std::shared_ptr<NodeBase>	New(Node_s, Node_s) = 0;

	public:


		Op(char const * str, Node_s l, Node_s r): str_(str), l_(l), r_(r) {}

		virtual ~Op() {}


		virtual void		print()
		{
			printf("(");
			l_->print();
			std::cout << " " << str_ << " ";
			r_->print();
			printf(")");
		}
		virtual void		print_type()
		{
			printf("(");
			l_->print_type();
			std::cout << " " << str_ << " ";
			r_->print_type();
			printf(")");
		}
		virtual void		printp()
		{
			printf("(");
			std::cout << l_;
			std::cout << " " << str_ << " ";
			std::cout << r_;
			printf(")");
		}


		std::string	str_;

		//Node_s		l_;
		//Node_s		r_;
		std::shared_ptr<NodeBase>	l_;
		std::shared_ptr<NodeBase>	r_;
};

#endif

