
#include <stdlib.h>

class Node
{
public:
	Node(int d)
	{
		data = d;
		parent = NULL;
		left = NULL;
		right = NULL;
	}
	void	addNode(Node* n)
	{
		if(n->data <= data) {
			if(left == NULL) {
				left = n;
				n->parent = this;
			} else {
				left->addNode(n);
			}
		} else if(n->data > data) {
			if(right == NULL) {
				right = n;
				n->parent = this;
			} else {
				right->addNode(n);
			}
		}
	}
	Node*	find(int d, int& depth)
	{
		depth++;

		if(d == data) return this;

		if(d < data) {
			if(left == NULL) return NULL;
			return left->find(d, depth);
		}
		if(right == NULL) return NULL;
		return right->find(d, depth);
	}

	Node*	parent;
	Node*	left;
	Node*	right;
	int	data;
};

class Tree
{
public:
	Tree()
	{
		root = NULL;
	}
	void	addNode(Node* n)
	{
		if(root == NULL) {
			root = n;
		} else {
			root->addNode(n);
		}
	}
	void	addNode(int d)
	{
		Node* n = new Node(d);

		addNode(n);
	}
	Node*	find(int d)
	{
		int dep;
		return find(d, dep);
	}
	Node*	find(int d, int& depth)
	{
		if(root == NULL) return NULL;
		
		depth = -1;

		return root->find(d, depth);
	}
	Node*	lca(int d0, int d1)
	{
		int dep0;
		int dep1;
		
		Node* n0 = find(d0, dep0);
		Node* n1 = find(d1, dep1);

		// check for NULL
		if((n0 == NULL) || (n1 == NULL)) return NULL;
		
		// check for root
		if(n0 == root) return root;
		if(n1 == root) return root;

		// equalize depth
		while(dep0 > dep1) {
			n0 = n0->parent;
			dep0--;
		}
		while(dep1 > dep0) {
			n1 = n1->parent;
			dep1--;
		}
		
		while(1) {
			if(n0 == n1) break;
			n0 = n0->parent;
			n1 = n1->parent;
		}
		return n0;
	}

	Node*	root;
};




