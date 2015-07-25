#include <iostream>
#include "computer.h"
#include <string>
#include <vector>
#include <stdlib.h>
#include <time.h>
#include <sstream>
#include "pieces.h"
#include "controller.h"

Computer::Computer(Board *game, char team): Controller(game,team) {}

std::string string_convert(int a, int b) {
	std::string str;
	int a1 = 8-a;
	std::ostringstream ss;
	ss << a1;
	str = ss.str();
	char c1 = 'a' + b;
	str = str + c1;
	return str;
}
	
	

void Computer::makeMove() {
	std::vector <std::string> tmp;
	for (int i = 0; i < 7; i++) {
		for (int j = 0; j < 7; j++) {
			char name = game->getPiece(i,j)->getName();
			std::vector< std::pair <int, int> > range = game->getPiece(i,j)->getRange();
			if (name >= 'A' && name <= 'Z' && this->getTeam() == 'A') {
				for (int x = 0; x < range.size(); x++) {
					std::pair <int, int> tmp_pair = range[x];
					if (game->ruleCheck(i,j,tmp_pair.first,tmp_pair.second)) {
						std::string s = string_convert(i,j) + " " +
							   string_convert(tmp_pair.first,tmp_pair.second);
						tmp.push_back(s);
					}
				}
			}
			else if (name >= 'a' && name <= 'z' && this->getTeam() == 'z') {
				for (int x = 0; x < range.size(); x++) {
					std::pair <int, int> tmp_pair = range[x];
					if (game->ruleCheck(i,j,tmp_pair.first,tmp_pair.second)) {
						std::string s = string_convert(i,j) + " " +
							   string_convert(tmp_pair.first, tmp_pair.second);
						tmp.push_back(s);
					}
				}
			}
		}
	}
	srand(time(NULL));
	int random = rand()%(tmp.size()-1);
	std::string opt;
	while (std::cin >> opt) {
		if (opt == "move") {
			game->notify(tmp[random], this->getTeam());
			break;
		}
		else {
			std::cout << "invalid command please enter again" << std::endl;
		}
	}
}
