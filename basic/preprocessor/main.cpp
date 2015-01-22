#include <stdio.h>

#define PNT(x) STR(x)
#define STR(name) #name
#define A hello
#define B world
#define C A''B
#define D PNT(C)

int main()
{
	printf(D"\n");
	
	return 0;
}

