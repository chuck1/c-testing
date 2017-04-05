#include <stdio.h>

#include "linked_list.h"

int main()
{
	ll<char> list;
	list.insert( 0, 'a' );
	list.insert( 0, 'b' );
	list.insert( 0, 'c' );
	list.insert( 0, 'd' );
	list.insert( 0, 'e' );
	list.insert( 0, 'f' );



	ll_node<char> *node = list.begin();
	for( ; node != NULL; node = node->next_ )
	{
		printf("%c\n", node->t_);
	}
}
