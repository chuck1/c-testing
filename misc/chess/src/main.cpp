#include <stdio.h>
#include <string.h>

enum Color { WHITE, BLACK };
enum Type { ROOK='r',KNIG='n',BISH='b',KING='k',QUEE='q',PAWN='p' };

class Pos
{
	public:
		Pos();
		Pos(int,int);
		void	set(int,int);
		void	rotate();

		Color color;
		int x,y;
};

struct Piece
{
	public:
		Piece();
		Piece(Pos,Color,Type);
		Pos	pos;
		Type	type;
};

class Player
{
	public:
		Player(Color);
		void			reset();
		Piece*			pieces;
		Color			color;
};

class Board
{
	public:
		Board();
		void	print();
		Player	white;
		Player	black;
};

// source

Pos::Pos()
{}
Pos::Pos(int nx, int ny):
	x(nx), y(ny)
{

}
void	Pos::set(int nx, int ny)
{
	
}
void	Pos::rotate()
{
	x = 7 - x;
	y = 7 - y;
}

Piece::Piece()
{}
Piece::Piece(Pos npos, Color ncolor, Type ntype):
	pos(npos),
	type(ntype)
{
	if( ncolor == Color::BLACK )
	{
		pos.rotate();
	}
}

Player::Player(Color ncolor):
	color(ncolor)
{
	pieces = new Piece[16];

	pieces[0] =	Piece(Pos(0,0),color,Type::ROOK),
	pieces[1] = 	Piece(Pos(1,0),color,Type::KNIG);
	pieces[2] = 	Piece(Pos(2,0),color,Type::BISH);
	pieces[3] = 	Piece(Pos(3,0),color,Type::KING);
	pieces[4] = 	Piece(Pos(4,0),color,Type::QUEE);
	pieces[5] = 	Piece(Pos(5,0),color,Type::BISH);
	pieces[6] = 	Piece(Pos(6,0),color,Type::KNIG);
	pieces[7] = 	Piece(Pos(7,0),color,Type::ROOK);
	pieces[8] = 	Piece(Pos(0,1),color,Type::PAWN);
	pieces[9] = 	Piece(Pos(1,1),color,Type::PAWN);
	pieces[10] = 	Piece(Pos(2,1),color,Type::PAWN);
	pieces[11] = 	Piece(Pos(3,1),color,Type::PAWN);
	pieces[12] =	Piece(Pos(4,1),color,Type::PAWN);
	pieces[13] = 	Piece(Pos(5,1),color,Type::PAWN);
	pieces[14] = 	Piece(Pos(6,1),color,Type::PAWN);
	pieces[15] = 	Piece(Pos(7,1),color,Type::PAWN);

}

Board::Board():
	white(Color::WHITE),
	black(Color::BLACK)
{

}
void	Board::print()
{
	char cm[8][8];
	memset(cm,' ',64);

	Piece* p = NULL;
	for(int a=0;a<16;++a)
	{
		p = white.pieces + a;
		cm[p->pos.x][p->pos.y] = p->type;

		p = black.pieces + a;
		cm[p->pos.x][p->pos.y] = p->type;


	}
	
	printf("+---+---+---+---+---+---+---+---+-\n");
	for(int j=7;j>=0;--j)
	{
		for(int i=0;i<8;++i)
		{
			printf("| %c ",cm[i][j]);
		}
		printf("|\n");
		printf("+---+---+---+---+---+---+---+---+-\n");

	}
}

int main()
{
	Board b;
	b.print();
}


