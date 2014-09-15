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
			printf("%s",str_);
		}

		char const * str_;

		// math
		add	operator+(node* n);
		eq	operator=(node* n);
};

struct op: public node
{

	op(char const * str, node* l, node* r): node(str), l_(l), r_(r) {}

	virtual ~op() {}

	virtual node*	New(node*, node*) = 0;

	virtual void print()
	{
		printf("(");
		l_->print();
		node::print();
		r_->print();
		printf(")");
	}

	node*		ldist()
	{
		op* o = dynamic_cast<op*>(l_);
		if(o)
		{
			node* ret = o->New(New(o->l_, r_), New(o->r_, r_));
			return ret;
		}
		return 0;
	}


	node*	l_;
	node*	r_;
};

struct add: op {
	add(node*, node*); 
	virtual node*	New(node* a, node* b) { return new add(a,b); }
};
/*struct sub: op {
  sub(node&, node&);
  };
  struct mul: op {
  mul(node&, node&);
  };
  struct div: op {
  div(node&, node&);
  };*/

add::add(node* l, node* r): op("+", l, r) {}
/*sub::sub(node& l, node& r): op("-", l, r) {}
  mul::mul(node& l, node& r): op("*", l, r) {}
  div::div(node& l, node& r): op("/", l, r) {}
  */
struct eq: op {

	eq(node*, node*);

	virtual node*	New(node* a, node* b) { return new eq(a,b); }


	/*	void mul_post(node* n) {
		mul* l = new mul(l_, n);
		mul* r = new mul(r_, n);

		l_ = l;
		r_ = r;
		}*/
};

eq::eq(node* l, node* r): op("=", l, r)
{
}

node::node(char const * str):str_(str)
{
}


void apply(eq* e, char const * str, node* n) {
}

add	node::operator+(node* n)
{
	return add(this, n);
}
eq	node::operator=(node* n)
{
	return eq(this, n);
}

/*add	operator+(node& n0, node& n1)
  {
  add ret(n0, n1);
  return ret;
  }*/

struct ptr
{
	public:
		ptr(char const * s): n_(new node(s)) {}

		ptr(ptr p0, ptr p1)
		{
			n_ = new eq(p0.n_, p1.n_);
		}
	private:
		ptr(node* n): n_(n) {}
	public:
		void	print()
		{
			n_->print();
		}

		// math
		ptr	operator+(ptr& p)
		{
			return ptr(new add(n_, p.n_));
		}
		ptr	operator=(ptr& p)
		{
			return ptr(new eq(n_, p.n_));
		}

		void	operator+=(ptr& p)
		{
			n_ = new add(n_, p.n_);
		}
		void	operator+=(ptr&& p)
		{
			n_ = new add(n_, p.n_);
		}
		// manip
		ptr	ldist()
		{

			op* o = dynamic_cast<op*>(n_);
			if(o == 0) abort();
			
			return ptr(o->ldist());

		}

		node*	n_;
};

int main() {

	ptr n0("1");
	ptr n1("2");
	ptr n2("3");

	ptr e = ((n0 + n1) = n2);

	e.print(); printf("\n");

	e += ptr("4");

	e.print(); printf("\n");

	ptr d(e.ldist());
	
	d.print(); printf("\n");

	return 0;
}

