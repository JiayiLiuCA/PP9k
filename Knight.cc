#include "concrete_pieces.h"
#include "pieces.h"
#include <iostream>
#include <cmath>


bool Knight::moveCheck(int row, int col, int new_row, int new_col) {
	std::cout << "start" << std::endl;
	if ((row < 0) || (row > 7) || (col < 0) || (col > 7) ||
		(new_row < 0) || (new_row > 7) || (new_col < 0) || (new_row > 7)) {
		std::cout << "out of range" << std::endl;
		return false;
	}
	int diff_row = std::abs(row - new_row);
	int diff_col = std::abs(col - new_col);
	std::cout << "diff_row is " << diff_row << std::endl;
	std::cout << "diff_col is " << diff_col << std::endl;
	if ((diff_row * diff_col == 2) && 
		(diff_row + diff_col == 3)) {
		return true;
	}
	else {
		return false;
	}
}
