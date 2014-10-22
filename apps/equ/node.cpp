#include "node.hpp"
#include "add.hpp"
#include "eq.hpp"

node::node(char const * str):str_(str)
{
}

add	node::operator+(snode n)
{
	return add(shared_from_this(), n);
}
eq	node::operator=(snode n)
{
	return eq(shared_from_this(), n);
}



