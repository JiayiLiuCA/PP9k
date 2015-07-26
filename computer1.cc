#include <iostream>
#include "computer.h"
#include <string>
#include <vector>
#include <stdlib.h>
#include <time.h>
#include <sstream>
#include "pieces.h"
#include "controller.h"
#include <cmath>

Computer1::Computer1(Board *game, char team): Controller(game,team) {}

void Computer1::makeMove() {
	std::cout << "in makeMove" << std::endl;
	std::string opt;
	while (std::cin >> opt) {
		if (opt == "move") {
			std::vector <std::string> tmp;
			for (int i = 0; i < 8; i++) {
				for (int j = 0; j < 8; j++) {
					Pieces * tmp_p = game->getPiece(i,j);
					if (tmp_p != NULL) {
						char name = tmp_p->getName();
						std::vector< std::pair <int, int> > range = tmp_p->getRange();
						if (std::abs(name - this->getTeam()) < 25) {
							//std::cout << "name :" << name << " team: " << this->getTeam() << std::endl;
							for (int x = 0; x < range.size(); x++) {
								std::pair <int, int> tmp_pair = range[x];
								//std::cout << "陈梓涵傻逼" << i << j << tmp_pair.first << tmp_pair.second << std::endl;
								if (game->ruleCheck(i,j,tmp_pair.first,tmp_pair.second)) {
									std::string s = string_convert(i,j) + " " +
										string_convert(tmp_pair.first,tmp_pair.second);
									if (name == 'P' && tmp_pair.first == 0) {
										s = s + " " + 'Q';
									}
									if (name == 'p' && tmp_pair.first == 7) {
										s = s + " " + 'q';
									}
									std::cout << "input :" << s << std::endl;
									tmp.push_back(s);
								}
							}
						}
					}
				}
			}
			srand(time(NULL));
			int random = rand()%(tmp.size()-1);
			std::cout << "chosen move is **************************************" << tmp[random] << std::endl;
			game->notify(tmp[random], this->getTeam());
			break;
		}
		else {
			std::cout << "invalid command please enter again" << std::endl;
		}
	}
}

