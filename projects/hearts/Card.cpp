#include <string.h>
#include <stdio.h>
#include <stdlib.h>

#include <Card.hpp>

char * Card::string()
{
	char * buffer = new char[128];

	switch(value_) {
		case 0x0:
			strcpy(buffer, "two  ");
			break;
		case 0x1:
			strcpy(buffer, "three");
			break;
		case 0x2:
			strcpy(buffer, "four ");
			break;
		case 0x3:
			strcpy(buffer, "five ");
			break;
		case 0x4:
			strcpy(buffer, "six  ");
			break;
		case 0x5:
			strcpy(buffer, "seven");
			break;
		case 0x6:
			strcpy(buffer, "eight");
			break;
		case 0x7:
			strcpy(buffer, "nine ");
			break;
		case 0x8:
			strcpy(buffer, "ten  ");
			break;
		case 0x9:
			strcpy(buffer, "jack ");
			break;
		case 0xa:
			strcpy(buffer, "queen");
			break;
		case 0xb:
			strcpy(buffer, "king ");
			break;
		case 0xc:
			strcpy(buffer, "ace  ");
			break;
		default:
			printf("invalid card value %x\n", value_);
			abort();
	}

	strcat(buffer, " of ");

	strcat(buffer, suit_.string());

	return buffer;
}
