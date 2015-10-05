#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include <Suit.hpp>

char *		Suit::string()
{
	char * buffer = new char[32];
	
	switch(suit_) {
		case 0x0:
			strcpy(buffer, "clubs");
			break;
		case 0x1:
			strcpy(buffer, "diamonds");
			break;
		case 0x2:
			strcpy(buffer, "hearts");
			break;
		case 0x3:
			strcpy(buffer, "spades");
			break;
		default:
			printf("invalid suit %x\n", suit_);
			abort();
	}

	return buffer;
}

