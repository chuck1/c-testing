#ifndef _GET_OPT_H
#define _GET_OPT_H

#include <ctype.h>
#include <stdio.h>     /* for printf */
#include <stdlib.h>    /* for exit */
    /* for getopt_long; standard getopt is in unistd.h */

class MyGetOpt {
public:
	
	struct MyOption {
		int c;
		char *arg;
	};
	
	MyGetOpt();
	int GetLong ( int argc, char **argv, const char *shortopts, const struct option *long_options );
	int Get ( int argc, char **argv, const char *shortopts );
	MyOption 	*opt;
	int 		optc;
};

#include "MyGetOpt.cpp"

#endif