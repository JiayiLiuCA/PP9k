#include <cmath>
#include <iostream>
#include "concrete_pieces.h"

bool Pawn::moveCheck(int row, int col, int new_row, int new_col) {
	if ((row < 0) || (row > 7) || (col < 0) || (col > 7) ||
		(new_row < 0) || (new_row > 7) || (new_col < 0) || (new_row > 7)) {
		return false;
	}
	int diff_row = new_row - row;
	int diff_col = std::abs(new_col -col);
	if (name == 'p') {
		if ((diff_row == 1) && (diff_col <= 1)) {
			return true;
		}
		else if ((diff_row == 2) && (diff_col == 0)) {
			if (row == 1) {
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
			if (row == 6) {
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


void Pawn::setRange() {
	while(range.size() != 0) {
		range.pop_back();
	}
	std::pair <int, int> tmp;
	if(getName() == 'p') {
		tmp.first = r + 2;
		tmp.second = c;
		if(r == 1)range.push_back(tmp);
		tmp.first = r + 1;
		if(moveCheck(r, c, r + 1, c))range.push_back(tmp);
		tmp.second = c + 1;
		if(moveCheck(r, c, r + 1, c + 1))range.push_back(tmp);
		tmp.second = c - 1;
		if(moveCheck(r, c, r + 1, c - 1))range.push_back(tmp);
	}
	else {
		tmp.first = r - 2;
		tmp.second = c;
		if(r == 6)range.push_back(tmp);
		tmp.first = r - 1;
		if(moveCheck(r, c, r - 1, c))range.push_back(tmp);
		tmp.second = c + 1;
		if(moveCheck(r, c, r - 1, c + 1))range.push_back(tmp);
		tmp.second = c - 1;
		if(moveCheck(r, c, r - 1, c - 1))range.push_back(tmp);

}

