#include "concrete_pieces.h"
#include "pieces.h"
#include <iostream>
#include <cmath>


bool Knight::moveCheck(int row, int col, int new_row, int new_col) {
	int diff_row = abs(row - new_row);
	int diff_col = abs(col - new_col);
	if ((diff_row * diff_col == 2) && 
		(diff_row + diff_col == 3)) {
		return true;
	}
	else {
		return false;
	}
}
