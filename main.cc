#include "board.h"
#include <iostream>

int main() {
	Board *b = Board::getInstance();
	b->add(5, 5, 'n');
	//b->add(7, 4, 'K');
	std::cout << b->ruleCheck(5, 5, 7, 4) << std::endl;
}
