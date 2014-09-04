#include <stdio.h>



struct node {

	node(char const *);
	virtual ~node() {}

	virtual void print() {
		printf("%s",str_);
	}

	char const * str_;
	
	
};

struct op: node {

	op(char const *, node*, node*);
	virtual ~op() {}
	
	virtual void print() {
		printf("(");
		if(l_) l_->print();
		node::print();
		if(r_) r_->print();
		printf(")");
	}
	
	node*	l_;
	node*	r_;
};
struct add: op {
	add(node*, node*); 
};
struct sub: op {
	sub(node*, node*);
};
struct mul: op {
	mul(node*, node*);
};
struct div: op {
	div(node*, node*);
};

add::add(node* l, node* r): op("+", l, r) {}
sub(node* l, node* r): op("-", l, r) {}
mul(node* l, node* r): op("*", l, r) {}
div(node* l, node* r): op("/", l, r) {}

struct eq {
	
	eq(node*, node*);

	virtual void print() {
		if(l_) l_->print();
		printf("=");
		if(r_) r_->print();
		printf("\n");
	}

	void mul_post(node* n) {
		mul* l = new mul(e->l_, n);
		mul* r = new mul(e->r_, n);
		
		e->l_ = l;
		e->r_ = r;
	}

	node*	l_;
	node*	r_;
};

eq::eq(node* l, node* r): l_(l), r_(r)
{
}

node::node(char const * str):str_(str)
{
}

op::op(char const * str, node* l, node* r): node(str), l_(l), r_(r)
{
}

void apply(eq* e, char const * str, node* n) {
}

int main() {

	node n0("1");
	node n1("2");
	node n2("3");
	node n4("4");

	op o("+",&n0,&n1);

	eq e(&o,&n2);

	e.print();

	apply(&e, "*", &n4);

	e.print();

	return 0;
}

