
#include <stdio.h>

struct bar {
	int a;
	const char *c;
};

struct foo
{
	const char* c;
	int a;
	bar b;
};

int main()
{
	/*
	foo g[] = {
		{"hello",1,0},
		{"goodbye",2,0}
	};
	
	foo f[] = {
		{"abc",1,g},
		{"def",2,0}
	};
	
	
	for ( int a = 0; a < 2; a++ ) {
		printf("%s %i %p\n",f[a].c,f[a].a,f[a].f);
		if (f[a].f) {
			for ( int b = 0; b < 2; b++ ) {
				printf("\t%s %i %p\n",f[a].f[b].c,f[a].f[b].a,f[a].f[b].f);
			}
		}
	}
	
	
	*/
	
	foo f = {"hello",0,{1,"world"}};
	
	
	
	return 0;
}

