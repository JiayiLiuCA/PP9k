#include "human.h"
#include <iostream>


Human::Human(Board *game): Controller(game) {}


void Human::makeMove() {
	std::string opt;
	std::string pos1;
	std::string pos2;
	std::cin >> opt;
	if(opt == "move") {
		std::cin >> pos1 >> pos2;
		std::cout << "the notify sent to game is " << pos1 << " " << pos2 << std::endl;
		game->notify(pos1 + " " + pos2);
	}
	else if(opt == "resign") game->notify(opt);
	else {
		std::cout << "invalid command please enter again" << std::endl;
		this->makeMove();
	}
}
	

	
