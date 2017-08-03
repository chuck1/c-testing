#include <stdio.h>

void hexstring_to_bytes(char * sbuf, unsigned char * buf, size_t buflen)
{
	char * pos = sbuf;
	size_t count = 0;
	for(; count < buflen; count++)
	{
		sscanf(pos, "%2hhx", &buf[count]);
		pos += 2;
	}
}

struct A
{
	float a, b, c;
};

int main()
{
	char sbuf[1000];
	unsigned char val[12];

	fgets(sbuf, sizeof sbuf, stdin);
	
	hexstring_to_bytes(sbuf, val, 12);

	struct A* a = (struct A*)val;


	printf("I read:\n");
	puts(sbuf);
	
	int i = 0;
	for(; i < 12; i++) printf("%02x", val[i]);
	printf("\n");

	printf("a = %f\n", a->a);
	printf("b = %f\n", a->b);
	printf("c = %f\n", a->c);

	return 0;
}

