

#include "Tree.hpp"

#include <iostream>

using namespace std;

int main()
{

	Tree t;

	t.addNode(3);
	t.addNode(1);
	t.addNode(2);
	t.addNode(4);
	t.addNode(5);
	
	cout << t.lca(1,5)->data << endl;
}

