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


#include "board.h"

Player::Player(Board* board,Color ncolor):
	color(ncolor)
{
	pieces_[0] =	new Rook(board, Pos(0,0),color,0);
	pieces_[1] = 	new Knight(board, Pos(1,0),color,1);
	pieces_[2] = 	new Bishop(board, Pos(2,0),color,2);
	pieces_[3] = 	new King(board, Pos(3,0),color,3);
	pieces_[4] = 	new Queen(board, Pos(4,0),color,4);
	pieces_[5] = 	new Bishop(board, Pos(5,0),color,5);
	pieces_[6] = 	new Knight(board, Pos(6,0),color,6);
	pieces_[7] = 	new Rook(board, Pos(7,0),color,7);
	pieces_[8] = 	new Pawn(board, Pos(0,1),color,8);
	pieces_[9] = 	new Pawn(board, Pos(1,1),color,9);
	pieces_[10] = 	new Pawn(board, Pos(2,1),color,10);
	pieces_[11] = 	new Pawn(board, Pos(3,1),color,11);
	pieces_[12] =	new Pawn(board, Pos(4,1),color,12);
	pieces_[13] = 	new Pawn(board, Pos(5,1),color,13);
	pieces_[14] = 	new Pawn(board, Pos(6,1),color,14);
	pieces_[15] = 	new Pawn(board, Pos(7,1),color,15);
}
Player::~Player()
{
	//delete[] pieces_;
	//for(int i = 0; i < 16; ++i) delete pieces_[i];
}
void	Player::possible_moves()
{
	moves_.clear();
	
	Piece* p;
	
	for(int i = 0; i < 16; ++i)
	{
		p = pieces_[i];
		
		if(p->pos.valid())
		{
			p->possible_moves();
			moves_.insert(moves_.end(), p->moves_.begin(), p->moves_.end());
		}
	}
	
	printf("player has %i possible moves\n",(int)moves_.size());
}


Board::Board():
	white_(this, Color::WHITE),
	black_(this, Color::BLACK)
{
	refresh_map();
}
void	Board::refresh_map()
{
	for(int a=0;a<8;++a) for(int b=0;b<8;++b) map_[a][b] = NULL;

	Piece* p = NULL;
	for(int a=0;a<16;++a)
	{
		p = white_.pieces_[a];
		map_[p->pos.x][p->pos.y] = p;

		p = black_.pieces_[a];
		map_[p->pos.x][p->pos.y] = p;
	}
}
Piece*	Board::get(PieceID pid)
{
	if(pid.color_ == Color::WHITE)
		return white_.pieces_[pid.i_];

	if(pid.color_ == Color::BLACK)
		return white_.pieces_[pid.i_];

	return NULL;
}
void	Board::apply(Move m)
{
	Piece* p = get(m.pieceid_);
	
	map_[p->pos.x][p->pos.y] = NULL;
	
	p->pos = m.dest_;

	Piece* oldp = map_[p->pos.x][p->pos.y];
	
	if(oldp != NULL)
	{
		oldp->pos.x = -1;
		oldp->pos.y = -1;
	}
	
	
	map_[m.dest_.x][m.dest_.y] = p;
}
void	Board::reset_cm()
{
	Piece* p = NULL;

	for(int j=7;j>=0;--j)
	{
		for(int i=0;i<8;++i)
		{
			p = map_[i][j];
			if(p == NULL)
			{
				sprintf(cm_[i][j]," ");
				continue;
			}

			if(p->color_ == Color::WHITE)
				sprintf(cm_[i][j],"%s%c%s",KRED,p->type,KNRM);

			if(p->color_ == Color::BLACK)
				sprintf(cm_[i][j],"%s%c%s",KBLU,p->type,KNRM);
		}
	}
}
void	Board::reset_cm(std::vector<Move> moves)
{
	reset_cm();

	PieceID pid;
	Piece* p;
	Move m;

	for(auto m = moves.begin(); m != moves.end(); ++m)
	{
		pid = m->pieceid_;

		p = get(pid);

		if(p->color_ == Color::WHITE)
			sprintf(cm_[m->dest_.x][m->dest_.y],"%s%c%s",KYEL,p->type,KNRM);
		if(p->color_ == Color::BLACK)
			sprintf(cm_[m->dest_.x][m->dest_.y],"%s%c%s",KCYN,p->type,KNRM);

	}
}
void	Board::print()
{
	printf("   +---+---+---+---+---+---+---+---+\n");
	for(int j=7;j>=0;--j)
	{
		printf(" %i ",j+1);
		for(int i=0;i<8;++i)
		{
			printf("| %s ",cm_[i][j]);
		}
		printf("|\n");
		printf("   +---+---+---+---+---+---+---+---+\n");
	}
	printf("     a   b   c   d   e   f   g   h  \n");
}



