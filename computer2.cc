#include <iostream>
#include "computer.h"
#include <string>
#include <vector>
#include <stdlib.h>
#include <time.h>
#include <sstream>
#include "controller.h"
#include "pieces.h"

Computer2::Computer2(Board *game, char team): Controller(game,team) {}

void Computer2::makeMove() {
	std::string opt;
	while (std::cin >> opt) {
		if (opt == "move") {
			std::vector <std::string> tmp;
			int max_profit = 0;
			for (int i = 0; i < 8; i++) {
				for (int j = 0; j < 8; j++) {
					Pieces *tmp_p = game->getPiece(i,j);
					if (tmp_p != NULL) {
						char name = tmp_p->getName();
						std::vector <std::pair <int, int> > range = tmp_p->getRange();
						if (std::abs(name - this->getTeam()) < 25) {
							for (int x = 0; x < range.size(); x++) {
								std::pair <int, int> tmp_pair = range[x];
								if (game->ruleCheck(i,j,tmp_pair.first,tmp_pair.second)) {
									Pieces *target = game->getPiece(tmp_pair.first,tmp_pair.second);
									int profit = 0;
									if (target != NULL) {
										char target_name = target->getName();
										profit += value(target_name);
									}
									game->move(i,j,tmp_pair.first,tmp_pair.second);
									if (game->check('k') || game->check('K')) {
										profit += 999;
									}
									game->preundo();
									std::string s = string_convert(i,j) + " " +
										string_convert(tmp_pair.first,tmp_pair.second);
									if (name == 'P' && tmp_pair.first == 0) {
										s = s + " " + 'Q';
									}
									if (name == 'p' && tmp_pair.first == 7) {
										s = s + " " + 'q';
									}
									if (profit == max_profit) {
										tmp.push_back(s);
									}
									if (profit > max_profit) {
										max_profit = profit;
										tmp.clear();
										tmp.push_back(s);
									}
								}
							}
						}
					}
				}
			}
			srand(time(NULL));
			int random = rand()%(tmp.size());
			game->notify(tmp[random], this->getTeam());
			break;
		}
		else {
			std::cout << "invalid command please enter again" << std::endl;
		}
	}
}


