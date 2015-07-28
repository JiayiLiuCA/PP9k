#include "human.h"
#include <iostream>


Human::Human(Board *game, char team): Controller(game, team) {}


void Human::makeMove() {
	std::string opt;
	std::cin >> opt;
	std::string s;
	while(std::cin >> opt) {
		if(opt == "move") {
			std::getline(std::cin, s);
			game->notify(s, this->getTeam());
		}
		else if(opt == "resign") game->notify(opt, this->getTeam());
		else if(opt == "undo") game->undo();
		else std::cout << "invalid command please enter again" << std::endl;
	}
}



