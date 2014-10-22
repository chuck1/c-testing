#include "node.hpp"
#include "add.hpp"
#include "eq.hpp"

node::node(char const * str):str_(str)
{
}

add	node::operator+(node* n)
{
	return add(this, n);
}
eq	node::operator=(node* n)
{
	return eq(this, n);
}



