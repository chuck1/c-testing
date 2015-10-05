/*
#include <stdio.h>     /* for printf *//*
#include <stdlib.h>    /* for exit *//*
#include <getopt.h>    /* for getopt_long; standard getopt is in unistd.h */

#include "../../mylib/getopt/mygetopt.h"

int main (int argc, char **argv) {
    
	mygetopt go;
	
	
	go.get(argc,argv,"abc:");
	
	/*
	static struct option long_options[] = {
        {"add", 1, 0,		256},
        {"append", 0, 0,	257},
        {"delete", 1, 0,	258},
        {"verbose", 0, 0,	259},
        {"create", 1, 0,	'c'},
        {"file", 1, 0,		260},
        {NULL, 0, NULL,		0}
    };
	
	go.get_long(argc,argv,"abc:d:012",long_options);
	*/
	
	for ( int a = 0; a < go.optc; a++ )
	{
		printf("%i '%s'\n", go.opt[a].c, go.opt[a].arg);
	}
	
	
    exit (0);
}
