#ifndef __PIECES_H__
#define __PIECES_H__
class Pieces {
		int r;
		int c;
	protected:
		char name;
	public:
		virtual bool moveCheck(int row, int col, int new_row, int new_col) = 0; //this check whether the move made by the piece is valid or not on a plane board
		Pieces(int r, int c, int name): r(r), c(c), name(name) {}
		~Pieces();	
};
#endif
