#ifndef __CONCRETE_PIECES_H__
#define __CONCRETE_PIECES_H__
	
#include "pieces.h"

class King:public Pieces {
	public:
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
	public:
		moveCheck();
};

