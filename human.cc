#include "human.h"
#include <iostream>


Human::Human(Board *game, char team): Controller(game, team) {}


void Human::makeMove() {
	std::string opt;
	std::string pos1;
	std::string pos2;
	std::cin >> opt;
	if(opt == "move") {
		std::cin >> pos1 >> pos2;
		game->notify(pos1 + " " + pos2, this->getTeam());
	}
	else if(opt == "resign") game->notify(opt, this->getTeam());
	else {
		std::cout << "invalid command please enter again" << std::endl;
		this->makeMove();
	}
}
	

	
