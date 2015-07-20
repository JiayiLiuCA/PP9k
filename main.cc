#include "board.h"
#include <iostream>

int main() {
	Board *b = Board::getInstance();
	b->play();
}
