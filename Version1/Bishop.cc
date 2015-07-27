#include "concrete_pieces.h"
#include "pieces.h"
#include <iostream>
#include <cmath>


bool Bishop::moveCheck(int row, int col, int new_row, int new_col) {
	if ((row < 0) || (row > 7) || (col < 0) || (col > 7) ||
		(new_row < 0) || (new_row > 7) || (new_col < 0) || (new_col > 7)) {
		return false;
	}
	bool tmp;
	int diff_row = std::abs(row - new_row);
	if (diff_row == 0) {
		return false;
	}
	int diff_col = std::abs(col - new_col);
	tmp = (diff_row == diff_col);
	return tmp;
}


void Bishop::setRange() {
	int dx[] = {1, -1, 1, -1};
	int dy[] = {1, -1, -1, 1};
	while(range.size() != 0) {
		range.pop_back();
	}
	std::pair <int, int> tmp;
	for(int i = 0; i < 4; i ++) {
		for(int j = 1; j < 8; j++) {
			tmp.first = (r + j * dy[i]);
			tmp.second = (c + j * dx[i]);
			if(moveCheck(r, c, r + j * dy[i], c + j * dx[i])) range.push_back(tmp);
		}
	}
}
