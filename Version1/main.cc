#include "board.h"
#include <iostream>
#include "textdisplay.h"

int main() {
	Board *b = Board::getInstance();
	b->play();
}
