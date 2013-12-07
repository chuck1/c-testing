#include <vector>
#include <stdio.h>
#include <string.h>

enum Color { WHITE, BLACK };
enum Type { ROOK='r',KNIG='n',BISH='b',KING='k',QUEE='q',PAWN='p' };

struct Piece;
class Pos
{
	public:
		//Pos();
		Pos(int,int);
		void	set(int,int);
		void	rotate();
		void	print();
	
		Color color;
		int x,y;
};
struct Move
{
	Piece*	piece_;
	Pos	dest_;

	void	print();
};
struct Piece
{
	public:
		Piece(Pos,Color,Type);
		virtual std::vector<Move>	possible_moves();
		
		Pos				pos;
		Type				type;
};
struct Rook: public Piece
{
	Rook(Pos,Color);
	std::vector<Move>	possible_moves();
};
struct Knight: public Piece
{
	Knight(Pos,Color);
};
struct Bishop: public Piece
{
	Bishop(Pos,Color);
};
struct King: public Piece
{
	King(Pos,Color);
};
struct Queen: public Piece
{
	Queen(Pos,Color);
};
struct Pawn: public Piece
{
	Pawn(Pos,Color);
};

class Player
{
	public:
		Player(Color);
		void			reset();
		Piece*			pieces_[16];
		Color			color;
};

class Board
{
	public:
		Board();
		void	print();
		Player	white_;
		Player	black_;
		Piece*	map_[8][8];
};

// source

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
	printf("%i %i\n",x,y);
}
void	Pos::set(int nx, int ny)
{
	
}
void	Pos::rotate()
{
	x = 7 - x;
	y = 7 - y;
}

Piece::Piece(Pos npos, Color ncolor, Type ntype):
	pos(npos),
	type(ntype)
{
	if( ncolor == Color::BLACK )
	{
		pos.rotate();
	}
}
std::vector<Move>	Piece::possible_moves()
{
	std::vector<Move> moves;
	return moves;
}

Rook::Rook(Pos npos,Color color):
	Piece(npos,color,Type::ROOK)
{}
std::vector<Move>	Rook::possible_moves()
{
	std::vector<Move> moves;
	
	Pos temp(pos);
	
	while(1)
	{
		temp.x += 1;
		
		
	}
	
	
	for(auto it = moves.begin(); it != moves.end(); ++it)
	{
		it->print();
	}
	
	return moves;
}

Knight::Knight(Pos npos,Color color):
	Piece(npos,color,Type::KNIG)
{}
Bishop::Bishop(Pos npos,Color color):
	Piece(npos,color,Type::BISH)
{}
King::King(Pos npos,Color color):
	Piece(npos,color,Type::KING)
{}
Queen::Queen(Pos npos,Color color):
	Piece(npos,color,Type::QUEE)
{}
Pawn::Pawn(Pos npos,Color color):
	Piece(npos,color,Type::PAWN)
{}

Player::Player(Color ncolor):
	color(ncolor)
{
	pieces_[0] =	new Rook(Pos(0,0),color);
	pieces_[1] = 	new Knight(Pos(1,0),color);
	pieces_[2] = 	new Bishop(Pos(2,0),color);
	pieces_[3] = 	new King(Pos(3,0),color);
	pieces_[4] = 	new Queen(Pos(4,0),color);
	pieces_[5] = 	new Bishop(Pos(5,0),color);
	pieces_[6] = 	new Knight(Pos(6,0),color);
	pieces_[7] = 	new Rook(Pos(7,0),color);
	pieces_[8] = 	new Pawn(Pos(0,1),color);
	pieces_[9] = 	new Pawn(Pos(1,1),color);
	pieces_[10] = 	new Pawn(Pos(2,1),color);
	pieces_[11] = 	new Pawn(Pos(3,1),color);
	pieces_[12] =	new Pawn(Pos(4,1),color);
	pieces_[13] = 	new Pawn(Pos(5,1),color);
	pieces_[14] = 	new Pawn(Pos(6,1),color);
	pieces_[15] = 	new Pawn(Pos(7,1),color);
}

Board::Board():
	white_(Color::WHITE),
	black_(Color::BLACK)
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
void	Board::print()
{
	char cm[8][8];
	memset(cm,' ',64);

	Piece* p = NULL;
	for(int a=0;a<16;++a)
	{
		p = white_.pieces_[a];
		cm[p->pos.x][p->pos.y] = p->type;

		p = black_.pieces_[a];
		cm[p->pos.x][p->pos.y] = p->type;


	}

	printf("+---+---+---+---+---+---+---+---+\n");
	for(int j=7;j>=0;--j)
	{
		for(int i=0;i<8;++i)
		{
			printf("| %c ",cm[i][j]);
		}
		printf("|\n");
		printf("+---+---+---+---+---+---+---+---+\n");

	}
}

int main()
{
	Board b;

	b.white_.pieces_[0]->possible_moves();

	b.print();
}



