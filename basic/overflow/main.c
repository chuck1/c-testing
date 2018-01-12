#include <stdio.h>
#include <math.h>

unsigned int mylog2(unsigned int x)
{
	unsigned int c = 0;
	while(x > 1)
	{
		x >>= 1;
		++c;
	}
	return c;
}

unsigned int solve(unsigned int b, unsigned int c)
{
	/*
	 b = 1 << (a mod 32)
	 */
	/*
	 c = a / 32
	 */

	return mylog2(b) + c * 32;
}

int test(unsigned int a)
{
	unsigned int y = solve(1 << (a % 32), a / 32);
	
	/*
	printf("\n");
	printf("a                     %16u\n", a);
	printf("a mod 32              %16u\n", a % 32);
	printf("a / 32                %16u\n", a / 32);
	printf("\n");
	printf("1 << a                %16u\n", 1 << a);
	printf("1 << (a mod 32)       %16u\n", 1 << (a % 32));
	printf("log2(1 << (a mod 32)) %16u\n", mylog2(1 << (a % 32)));
	printf("(a / 32) * 32         %16u\n", (a / 32) * 32);
	*/

	printf("solve                 %16u\n", y);

	if(y == a) 
		return 0;	
	else
		return 1;
}
int main()
{
	for(unsigned int i = 1; i < (1 << 16); ++i)
	{
		if(test(i) != 0)
		{
			printf("FAIL\n");
			break;
		}
	}

	return 0;
}




