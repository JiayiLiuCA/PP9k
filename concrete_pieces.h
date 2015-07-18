#ifndef __CONCRETE_PIECES_H__
#define __CONCRETE_PIECES_H__
	
#include "pieces.h"
#include <vector>

class King:public Pieces {
		std::vector <Pieces*> attackers;
	public:
		King(int r, int c, char name, std::vector <Pieces*> attackers): Pieces(), row(r), col(c), name(name), attackers(attackers) {}
		bool moveCheck();
};

class Queen:public Pieces {
	public:
		Queen(int r, int c, char name): Pieces(), row(r), col(c), name(name) {}
		bool moveCheck();
};

class Bishop:public Pieces {
	public:
		Bishop(int r, int c, char name): Pieces(), row(r), col(c), name(name) {}
		bool moveCheck();
};

class Rook:public Pieces {
	public:
		Rook(int r, int c, char name): Pieces(), row(r), col(c), name(name) {}
		bool moveCheck();
};

class Knight:public Pieces {
	public:
		Knight(int r, int c, char name): Pieces(), row(r), col(c), name(name) {}
		bool moveCheck();
};

class Pawn:public Pieces {
		bool doubleMove; //if a Pawn has just moved 2 cells then this is true
	public:
		Pawn(int r, int c, char name, bool move): Pieces(), row(r), col(c), name(name), doubleMove(move) {}
		bool moveCheck();
		bool getStatus(); //a getter for doubleMove
};
#endif
