


class Pieces {
	protected:
		char name;
		int row;
		int col;
	public:
		virtual bool moveCheck(int oldr, int oldc, int newr, int newc) = 0; //this check whether the move made by the piece is valid or not on a plane board
};
