#include <stdio.h>
#include <assert.h>
#include <vector>
#include <string.h>

class node {
	public:

		virtual ~node() {}
		virtual void print() = 0;
		virtual node* copy() = 0;

		virtual node* multiply(node* n, double p);

		virtual bool operator==(node const * n) {
			printf("node op==\n");
			return false;
		}
};

class var: public node {
public:	
	var(char const * str): str_(str) {}
	
	virtual bool operator==(node const * n) {
		printf("var op==\n");
		
		var const * v = dynamic_cast<var const *>(n);
		
		if(v) {
			if(strcmp(str_, v->str_) == 0) return true;
		}

		return false;
	}
	
	
	
	virtual void print() {
		printf("%s",str_);
	}

	virtual node* copy() {
		return new var(*this);
	}

	char const * str_;


};

class add: public node {
	public:
		virtual void print() {
			for(auto it = nodes_.begin(); it != nodes_.end(); ++it) {
				(*it)->print();
				if(it != (nodes_.end()-1)) printf(" + ");
			}
		}
		
		virtual node* copy() { return new add(*this); }
		
		
		
		std::vector<node*>	nodes_;
};
class mul_node {
	public:
		mul_node(node* n, double p) {
			n_ = n->copy();
			p_ = p;
		}

		void print() {
			printf("((");
			n_->print();
			printf(")^%f)", p_);
		}

		node*		n_;
		double		p_;
};
class mul: public node {
	public:
		virtual ~mul() {}

		virtual void print() {
			for(auto it = nodes_.begin(); it != nodes_.end(); ++it) {
				it->print();
				if(it != (nodes_.end()-1)) printf(" * ");
			}
		}
		
		virtual node* multiply(node* n, double p) {
			for(auto it = nodes_.begin(); it != nodes_.end(); ++it) {
				if(it->n_->operator==(n)) {
					it->p_ += p;

					if(p == 0) nodes_.erase(it);

					return this;
				}
			}
			
			nodes_.emplace_back(n->copy(), p);
			return this;
		}
		
		virtual node* copy() { return new mul(*this); }

		std::vector<mul_node>	nodes_;
};

struct eq {

	eq(node* l, node* r) {
		assert(l);
		assert(r);

		l_ = l->copy();
		r_ = r->copy();
	}
	
	void multiply(node* n, double p) {
		l_->multiply(n,p);
		r_->multiply(n,p);
	}
	
	virtual void print() {
		assert(l_);
		assert(r_);


		l_->print();
		printf("=");
		r_->print();
		printf("\n");
	}

	node*	l_;
	node*	r_;
};

node* node::multiply(node* n, double p) {
	mul* m = new mul;
	
	m->multiply(n,p);
	m->multiply(this,1);

	return m;
}



int main() {

	var v("v");
	var r("r");
	var G("G");
	var M("M");

	mul m0, m1;

	m0.nodes_.emplace_back(v.copy(),2);
	m0.nodes_.emplace_back(r.copy(),-1);
	
	m1.nodes_.emplace_back(G.copy(),1);
	m1.nodes_.emplace_back(M.copy(),1);
	m1.nodes_.emplace_back(r.copy(),-2);
	
	

	eq e(&m0,&m1);
	
	e.print();
	
	e.multiply(&r,1);
	
	e.print();

	return 0;
}


