#include "concrete.pieces.h"
#include <iostream>
#include <cmath>

bool King::moveCheck(int oldr, int oldc, int newr, int newc) {
	if ((row < 0) || (row > 7) || (col < 0) || (col > 0) ||
		(new_row < 0) || (new_row > 7) || (new_col < 0) || (new_row > 7)) {
		return false;
	}
	int diff_row = abs(oldr - newr);
	int diff_col = abs(oldc - newc);
	if (diff_row + diff_col == 1 || diff_row * diff_col == 1) {
		return true;
	}
	else {
		return false;
	}
}

	

