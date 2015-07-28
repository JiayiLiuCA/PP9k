#include "board.h"
#include <iostream>
#include "textdisplay.h"

int main(int argc, char* argv[]) {
	std::cout << argc << std::endl;
	int graphic = 0;
	Board *b = Board::getInstance();
	if(argc == 2) graphic = 1;
	b->play(graphic);
}
