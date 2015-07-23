#ifndef __CONCRETE_PIECES_H__
#define __CONCRETE_PIECES_H__
	
#include "pieces.h"
#include <vector>

class King:public Pieces {
		std::vector <Pieces*> attackers;
	public:
		King(int r, int c, char name): Pieces(r, c, name) { setRange(); }
		bool moveCheck(int row, int col, int new_row, int new_col);
		void setRange();
};

class Queen:public Pieces {
	public:
		Queen(int r, int c, char name): Pieces(r, c, name) { setRange(); }
		bool moveCheck(int row, int col, int new_row, int new_col);
		void setRange();
};

class Bishop:public Pieces {
	public:
		Bishop(int r, int c, char name): Pieces(r, c, name) { setRange(); }
		bool moveCheck(int row, int col, int new_row, int new_col);
		void setRange();
};

class Rook:public Pieces {
	public:
		Rook(int r, int c, char name): Pieces(r, c, name) { setRange(); }
		bool moveCheck(int row, int col, int new_row, int new_col);
		void setRange();
};

class Knight:public Pieces {
	public:
		Knight(int r, int c, char name): Pieces(r, c, name) { setRange(); }
		bool moveCheck(int row, int col, int new_row, int new_col);
		void setRange();
};

class Pawn:public Pieces {
	public:
		Pawn(int r, int c, char name): Pieces(r, c, name) { setRange(); }
		bool moveCheck(int row, int col, int new_row, int new_col);
		void setRange();
};
#endif
