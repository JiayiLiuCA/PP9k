#include "concrete_pieces.h"
#include "pieces.h"
#include <iostream>
#include <cmath>


bool Rook::moveCheck(int row, int col, int new_row, int new_col) {
	if ((row < 0) || (row > 7) || (col < 0) || (col > 0) ||
		(new_row < 0) || (new_row > 7) || (new_col < 0) || (new_row > 7)) {
		return false;
	}
	int diff_row = abs(row - new_row);
	int diff_col = abs(col - new_col);
	if (diff_row + diff_col == 0) {
		return false;
	}
	else if (diff_row * diff_col == 0) {
		return true;
	}
	else {
		return false;
	}
}