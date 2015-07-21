#ifndef __PIECES_H__
#define __PIECES_H__
class Pieces {
		int r;
		int c;
		bool Move;
	protected:
		char name;
	public:
		bool getStatus();
		virtual bool moveCheck(int row, int col, int new_row, int new_col) = 0; //this check whether the move made by the piece is valid or not on a plane board
		Pieces(int r, int c, int name,bool Move = false): r(r), c(c), name(name) {}
		char getName();
		void setMove(bool move);
		int getr();
		int getc();
		~Pieces();	
};
#endif
