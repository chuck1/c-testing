#ifndef __BOARD__
#define __BOARD__
/*
#include <vector>
#include <stdio.h>
#include <string.h>

#define KNRM  "\x1B[0m"
#define KRED  "\x1B[31m"
#define KGRN  "\x1B[32m"
#define KYEL  "\x1B[33m"
#define KBLU  "\x1B[34m"
#define KMAG  "\x1B[35m"
#define KCYN  "\x1B[36m"
#define KWHT  "\x1B[37m"
*/

#include "piece.h"

struct Piece;
struct Board;
class Player
{
	public:
		Player(Board*,Color);
		~Player();
		void			reset();
		void			possible_moves();
		
		Board*			board_;
		Piece*			pieces_[16];
		Color			color;
		std::vector<Move>	moves_;
};

class Board
{
	public:
		Board();
		void	reset_cm();
		void	print();
		void	reset_cm(std::vector<Move>);
		Piece*	get(PieceID);
		void	apply(Move);
		void	refresh_map();
		
		char cm_[8][8][16];

		Player	white_;
		Player	black_;
		Piece*	map_[8][8];
};

#endif
