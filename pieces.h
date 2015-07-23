#include <utility>
#include <vector>
#ifndef __PIECES_H__
#define __PIECES_H__
class Pieces {
	protected:
		int r; //row of the piece
		int c; //column of the piece
		bool Move; //whether the piece has been moved or not
		std::vector < std::pair <int ,int> > range; //the coords that the piece MIGHT reach
		char name;
	public:
		bool getStatus();
		virtual bool moveCheck(int row, int col, int new_row, int new_col) = 0; //this check whether the move made by the piece is valid or not on a plane board
		Pieces(int r, int c, int name,bool Move = false): r(r), c(c), name(name) {}
		char getName();
		void setMove(bool move);
		int getr();
		int getc();
		void setr(int row);
		void setc(int col);
		virtual void setRange() = 0;
		std::vector< std::pair <int, int> > getRange();
		~Pieces();	
};
#endif
