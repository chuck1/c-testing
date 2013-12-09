#include <vector>
#include <stdio.h>
#include <string.h>
#include <sys/time.h>
#include <cmath>
/*
#define KNRM  "\x1B[0m"
#define KRED  "\x1B[31m"
#define KGRN  "\x1B[32m"
#define KYEL  "\x1B[33m"
#define KBLU  "\x1B[34m"
#define KMAG  "\x1B[35m"
#define KCYN  "\x1B[36m"
#define KWHT  "\x1B[37m"
*/

#include "board.h"

int main()
{
	Board b;
	Board b0(b);
	
	timeval start;
	timeval end;
	
	int us;
	
	/*	b.white_.pieces_[0]->possible_moves();
		b.reset_cm(b.white_.pieces_[0]->moves_);
		b.print();
		*/

	std::vector<Move> moves;
	//int j;
	
	gettimeofday(&start,0);
	
	int steps = 10000;
	int i;
	for(i = 0; i < steps; ++i)
	{
		b.white_.possible_moves();

		moves = b.white_.moves_;

		if(moves.size() == 0) break;

		Move m = moves.at(0);

		b0.apply(m);
		//b0.reset_cm();
		//b0.print();
	}
	
	
	gettimeofday(&end,0);  /* get current time; same as: timer = time(NULL)  */
	
	us = std::abs(int(end.tv_usec - start.tv_usec));
	int ms = (us - (us % 1000))/1000;
	
	printf("%i steps in %i ms\n",i,ms);
}



