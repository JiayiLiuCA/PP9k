#include "human.h"
#include <iostream>


Human::Human(Board *game): Controller(game) {}


void Human::makeMove() {
	std::string pos1;
	std::string pos2;
	std::cin >> pos1 >> pos2;
	game->notify(pos1 + " " + pos2);
}
	

	
