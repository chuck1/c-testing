#include <stdio.h>

int main() {



	int a = 1;
	int b = 1;
	int c = 0;
	
	
	
	while(c < 1000000000) {
		c = a + b;
		printf("%i\n",c);
		a = b;
		b = c;
	}
	
	
	return 0;

}








