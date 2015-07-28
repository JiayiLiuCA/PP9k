#include "human.h"
#include <iostream>


Human::Human(Board *game, char team): Controller(game, team) {}


void Human::makeMove() {
	std::string opt;
	std::string s;
	std::cin >> opt;
	if(std::cin.eof()) {
		game->setPlaying(false);
		return;
	}
	if(opt == "move") {
		std::getline(std::cin, s);
		game->notify(s, this->getTeam());
	}
	else if(opt == "resign") game->notify(opt, this->getTeam());
	else if(opt == "undo") game->undo();
	else {
		std::cout << "invalid command please enter again" << std::endl;
		this->makeMove();
	}
}



