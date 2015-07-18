#ifndef __CONCRETE_PIECES_H__
#define __CONCRETE_PIECES_H__
	
#include "pieces.h"
#include <vector>

class King:public Pieces {
		std::vector <Pieces*> attackers;
	public:
		King(int r, int c, char name, std::vector <Pieces*> attackers): Pieces(r, c, name), attackers(attackers) {}
		bool moveCheck(int oldr, int oldc, int newr, int newc);
};

class Queen:public Pieces {
	public:
		Queen(int r, int c, char name): Pieces(r, c, name) {}
		bool moveCheck(int oldr, int oldc, int newr, int newc);
};

class Bishop:public Pieces {
	public:
		Bishop(int r, int c, char name): Pieces(r, c, name) {}
		bool moveCheck(int oldr, int oldc, int newr, int newc);
};

class Rook:public Pieces {
	public:
		Rook(int r, int c, char name): Pieces(r, c, name) {}
		bool moveCheck(int oldr, int oldc, int newr, int newc);
};

class Knight:public Pieces {
	public:
		Knight(int r, int c, char name): Pieces(r, c, name) {}
		bool moveCheck(int oldr, int oldc, int newr, int newc);
};

class Pawn:public Pieces {
		bool doubleMove; //if a Pawn has just moved 2 cells then this is true
	public:
		Pawn(int r, int c, char name, bool move): Pieces(r, c, name), doubleMove(move) {}
		bool moveCheck(int oldr, int oldc, int newr, int newc);
		bool getStatus(); //a getter for doubleMove
};
#endif
