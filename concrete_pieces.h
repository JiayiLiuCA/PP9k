#ifndef __CONCRETE_PIECES_H__
#define __CONCRETE_PIECES_H__
	
#include "pieces.h"

class King:public Pieces {
		vector <Pieces*> attackers;
	public:
		King(int r, int c, char name,vector <Pieces*> attackers): row(r), col(c), name(name), attackers(attackers);
		moveCheck();
};

class Queen:public Pieces {
	public:
		moveCheck();
};

class Bishop:public Pieces {
	public:
		moveCheck();
};

class Rook:public Pieces {
	public:
		moveCheck();
};

class Knight:public Pieces {
	public:
		moveCheck();
};

class Pawn:public Pieces {
		bool doubleMove; //if a Pawn has just moved 2 cells then this is true
	public:
		moveCheck();
		bool getStatus(); //a getter for doubleMove
};
#endif
