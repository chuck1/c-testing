#include <stdio.h>

struct event
{
unsigned int time;
unsigned short value;
unsigned char type;
unsigned char number;
};

void print_bytes( void* data, int len )
{
	unsigned char *cdata = (unsigned char*)data;
	unsigned char *ptr = cdata;
	while( ptr < ( cdata + len ) )
	{
		printf( "%02X ", *ptr++ );
	}
	printf( "\n" );
}

int main()
{
	unsigned long a;
	a = 0xffffffffffffffff;


	print_bytes( &a, 8 );
	
	print_bytes( b, 11 );
	
	
	
	
	printf( "%i\n", sizeof( event ) );
	return 0;
}

