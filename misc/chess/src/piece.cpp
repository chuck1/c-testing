#include <vector>
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define KNRM  "\x1B[0m"
#define KRED  "\x1B[31m"
#define KGRN  "\x1B[32m"
#define KYEL  "\x1B[33m"
#define KBLU  "\x1B[34m"
#define KMAG  "\x1B[35m"
#define KCYN  "\x1B[36m"
#define KWHT  "\x1B[37m"


#include "piece.h"
#include "board.h"

void	Move::print()
{
	dest_.print();
}

Pos::Pos(int nx, int ny):
	x(nx), y(ny)
{

}
void	Pos::print()
{
	char c = 'a' + x;
	
	printf("%c %i\n",c,y+1);
}
void	Pos::set(int nx, int ny)
{
	
}
void	Pos::rotate()
{
	x = 7 - x;
	y = 7 - y;
}
bool	Pos::valid()
{
	if((x < 0) || (x > 7)) return false;
	if((y < 0) || (y > 7)) return false;
	return true;
}

Move::Move():
	dest_(0,0)
{

}
Piece::Piece(Board* board, Pos npos, Color ncolor, int i, Type ntype):
	color_(ncolor),
	pos(npos),
	type(ntype),
	board_(board)
{
	id_.color_ = ncolor;
	id_.i_ = i;
	
	if( ncolor == Color::BLACK )
	{
		pos.rotate();
	}
}
Move_Code		Piece::valid_move(Move move)
{
	Piece* p = board_->map_[move.dest_.x][move.dest_.y];
	
	if(p == NULL) return Move_Code::OPEN;
	
	if(p->color_ != color_) return Move_Code::CAPTURE;
	
	return Move_Code::INVALID;
}
void			Piece::possible_moves()
{
}
void			Piece::moves_straight()
{
	Move m;

	m.dest_ = pos;
	while(1)
	{
		m.dest_.x += 1;
		if(try_move(m)) break;
	}
	m.dest_ = pos;
	while(1)
	{
		m.dest_.x -= 1;
		if(try_move(m)) break;
	}
	m.dest_ = pos;
	while(1)
	{
		m.dest_.y += 1;
		if(try_move(m)) break;
	}
	m.dest_ = pos;
	while(1)
	{
		m.dest_.y -= 1;
		if(try_move(m)) break;
	}

}
void			Piece::moves_diagonal()
{
	Move m;

	m.dest_ = pos;
	while(1)
	{
		m.dest_.x += 1;	
		m.dest_.y += 1;

		if(try_move(m)) break;
	}
	m.dest_ = pos;
	while(1)
	{
		m.dest_.x -= 1;	
		m.dest_.y -= 1;

		if(try_move(m)) break;
	}
	m.dest_ = pos;
	while(1)
	{
		m.dest_.x += 1;
		m.dest_.y -= 1;

		if(try_move(m)) break;
	}
	m.dest_ = pos;
	while(1)
	{
		m.dest_.x -= 1;
		m.dest_.y += 1;

		if(try_move(m)) break;
	}

}
bool	Piece::try_move(Move m)
{
	if(!m.dest_.valid()) return true;

	Move_Code mc = valid_move(m);

	if(mc == Move_Code::INVALID) return true;

	moves_.push_back(m);

	if(mc == Move_Code::CAPTURE) return true;
	
	return false;
}

Rook::Rook(Board* board,Pos npos,Color color,int i):
	Piece(board,npos,color,i,Type::ROOK)
{}
void	Rook::possible_moves()
{
	moves_.clear();
	
	moves_straight();

	for(auto it = moves_.begin(); it != moves_.end(); ++it)
	{
		it->pieceid_ = id_;
		//it->print();
	}
}

Knight::Knight(Board* board,Pos npos,Color color,int i):
	Piece(board,npos,color,i,Type::KNIG)
{}
void	Knight::possible_moves()
{
	moves_.clear();
	
	Move m;

	m.dest_ = pos;
	m.dest_.x += 1;
	m.dest_.y += 2;
	try_move(m);

	m.dest_ = pos;
	m.dest_.x += 2;
	m.dest_.y += 1;
	try_move(m);

	m.dest_ = pos;
	m.dest_.x += 1;
	m.dest_.y += -2;
	try_move(m);

	m.dest_ = pos;
	m.dest_.x += 2;
	m.dest_.y += -1;
	try_move(m);

	m.dest_ = pos;
	m.dest_.x += -1;
	m.dest_.y += 2;
	try_move(m);

	m.dest_ = pos;
	m.dest_.x += -2;
	m.dest_.y += 1;
	try_move(m);

	m.dest_ = pos;
	m.dest_.x += -1;
	m.dest_.y += -2;
	try_move(m);

	m.dest_ = pos;
	m.dest_.x += -2;
	m.dest_.y += -1;
	try_move(m);




	for(auto it = moves_.begin(); it != moves_.end(); ++it)
	{
		it->pieceid_ = id_;
		//it->print();
	}
}

Bishop::Bishop(Board* board,Pos npos,Color color,int i):
	Piece(board,npos,color,i,Type::BISH)
{}
void	Bishop::possible_moves()
{
	moves_.clear();

	moves_diagonal();

	for(auto it = moves_.begin(); it != moves_.end(); ++it)
	{
		it->pieceid_ = id_;
		//it->print();
	}
}

King::King(Board* board,Pos npos,Color color,int i):
	Piece(board,npos,color,i,Type::KING)
{}
void	King::possible_moves()
{
	moves_.clear();

	Move m;
	
	m.dest_ = pos;
	m.dest_.x += 1;
	try_move(m);

	m.dest_ = pos;
	m.dest_.x += -1;
	try_move(m);

	m.dest_ = pos;
	m.dest_.y += 1;
	try_move(m);
	
	m.dest_ = pos;
	m.dest_.y += -1;
	try_move(m);
	
	for(auto it = moves_.begin(); it != moves_.end(); ++it)
	{
		it->pieceid_ = id_;
		//it->print();
	}
}

Queen::Queen(Board* board,Pos npos,Color color,int i):
	Piece(board,npos,color,i,Type::QUEE)
{}
void	Queen::possible_moves()
{
	moves_.clear();
	
	moves_straight();
	moves_diagonal();

	for(auto it = moves_.begin(); it != moves_.end(); ++it)
	{
		it->pieceid_ = id_;
		//it->print();
	}
}

Pawn::Pawn(Board* board,Pos npos,Color color,int i):
	Piece(board,npos,color,i,Type::PAWN)
{}
bool	Pawn::try_move(Move m)
{
	if(!m.dest_.valid()) return true;

	Move_Code mc = valid_move(m);

	//printf("pawn %i\n",mc);
	
	if(mc == Move_Code::OPEN) moves_.push_back(m);
	
	return true;
}
bool	Pawn::try_move_diag(Move m)
{
	if(!m.dest_.valid()) return true;

	Move_Code mc = valid_move(m);

	if(mc == Move_Code::INVALID) return true;
	if(mc == Move_Code::OPEN) return true;

	moves_.push_back(m);

	return false;
}
void	Pawn::possible_moves()
{
	moves_.clear();

	int y;
	if(color_==Color::WHITE)
	{
		y = 1;
	}
	else if(color_==Color::BLACK)
	{
		y = -1;
	}
	else
	{
		printf("invalid color\n");
		exit(0);
	}
	
	//printf("pawn %i %i %i\n",pos.x,pos.y,x);
	
	Move m;

	m.dest_ = pos;
	m.dest_.y += y;
	try_move(m);

	m.dest_ = pos;
	m.dest_.y += y;
	m.dest_.x += -1;
	try_move_diag(m);

	m.dest_ = pos;
	m.dest_.y += y;
	m.dest_.x += 1;
	try_move_diag(m);


	for(auto it = moves_.begin(); it != moves_.end(); ++it)
	{
		it->pieceid_ = id_;
		//it->print();
	}
}




