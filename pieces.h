#include <>


class Pieces {
		char team;
		int row;
		int col;
	public:
		bool moveCheck() = 0; //this check whether the move made by
							  //the piece is valid or not on a plane board
};
