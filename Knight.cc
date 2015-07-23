#include "concrete_pieces.h"
#include "pieces.h"
#include <iostream>
#include <cmath>


bool Knight::moveCheck(int row, int col, int new_row, int new_col) {
	if ((row < 0) || (row > 7) || (col < 0) || (col > 7) ||
		(new_row < 0) || (new_row > 7) || (new_col < 0) || (new_row > 7)) {
		return false;
	}
	int diff_row = std::abs(row - new_row);
	int diff_col = std::abs(col - new_col);
	if ((diff_row * diff_col == 2) && 
		(diff_row + diff_col == 3)) {
		return true;
	}
	else {
		return false;
	}
}


void Knight::setRange() {
	int dx[] = {1, -1, 1, -1, 2, -2, 2, -2};
	int dy[] = {2, 2, -2, -2, 1, 1, -1, -1};
	while(range.size() != 0) {
		range.pop_back();
	}
	std::pair <int, int> tmp;
	for(int i = 0; i < 8; i ++) {
		tmp.first = (r + dy[i]);
		tmp.second = (c + dx[i]);
		if(moveCheck(r, c, r + dy[i], c + dx[i])) range.push_back(tmp);
	}
}
