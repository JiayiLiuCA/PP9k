#include "concrete_pieces.h"
#include "pieces.h"
#include <iostream>
#include <cmath>


bool Bishop::moveCheck(int row, int col, int new_row, int new_col) {
	bool tmp;
	int diff_row = abs(row - new_row);
	if (diff_row == 0) {
		return false;
	}
	int diff_col = abs(col - new_col);
	tmp = (diff_row == diff_col);
	return tmp;
}

