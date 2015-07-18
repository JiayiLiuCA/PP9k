#include <cmath>
#include <iostream>
#include "concrete_pieces.h"

bool Pawn::moveCheck(int oldr, int oldc, int newr, int newc) {
	if ((row < 0) || (row > 7) || (col < 0) || (col > 0) ||
		(new_row < 0) || (new_row > 7) || (new_col < 0) || (new_row > 7)) {
		return false;
	}
	int diff_row = newr - oldr;
	int diff_col = abs(newc - oldc);
	if (name == 'P') {
		if ((diff_row == 1) && (diff_col <= 1)) {
			return true;
		}
		else if ((diff_row == 2) && (diff_col == 0)) {
			if (oldr == 1) {
				return true;
			}
			else {
				return false;
			}
		}
		else {
			return false;
		}
	}
	else {
		if ((diff_row == -1) && (diff_col <= 1)) {
			return true;
		}
		else if ((diff_row == -2) && (diff_col == 0)) {
			if (oldr == 7) {
				return true;
			}
			else {
				return false;
			}
		}
		else {
			return false;
		}
	}
}

bool Pawn::getStatus() {
	return doubleMove;
}
	

