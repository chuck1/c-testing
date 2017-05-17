#ifndef __PIECE__
#define __PIECE__

#include <vector>
/*
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
enum Color { WHITE, BLACK };
enum Type { ROOK='r',KNIG='n',BISH='b',KING='k',QUEE='q',PAWN='p' };
enum Move_Code { INVALID=0, OPEN, CAPTURE };

struct Piece;
struct Board;
class Pos
{
	public:
		//Pos();
		Pos(int,int);
		void	set(int,int);
		void	rotate();
		void	print();
		bool	valid();
	
		Color color;
		int x,y;
};
struct PieceID
{
	Color	color_;
	int	i_;
};
struct Move
{
	Move();
	PieceID		pieceid_;
	Pos		dest_;
	
	void	print();
};
struct Piece
{
	public:
		Piece(Board*,Pos,Color,int,Type);
		virtual void			possible_moves();
		Move_Code			valid_move(Move);
		virtual bool			try_move(Move);
		void				moves_straight();
		void				moves_diagonal();
	
		std::vector<Move>		moves_;
		Color				color_;
		Pos				pos;
		Type				type;
		Board*				board_;
		PieceID				id_;
};
struct Rook: public Piece
{
	Rook(Board*,Pos,Color,int);
	void		possible_moves();
};
struct Knight: public Piece
{
	Knight(Board*,Pos,Color,int);
	void		possible_moves();
};
struct Bishop: public Piece
{
	Bishop(Board*,Pos,Color,int);
	void		possible_moves();
};
struct King: public Piece
{
	King(Board*,Pos,Color,int);
	void		possible_moves();
};
struct Queen: public Piece
{
	Queen(Board*,Pos,Color,int);	void		possible_moves();

};
struct Pawn: public Piece
{
	Pawn(Board*,Pos,Color,int);
	void		possible_moves();
	bool		try_move(Move);
	bool		try_move_diag(Move);
};


#endif
