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
	str = c1 + str;
	return str;
}
	
	

void Computer::makeMove() {
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
						//std::cout << "chess name: " << name << std::endl;
						//std::cout << "current team: " << this->getTeam() << std::endl;
						std::vector< std::pair <int, int> > range = tmp_p->getRange();
						if (name >= 'A' && name <= 'Z' && this->getTeam() == 'A') {
							std::cout << "team is " << name << std::endl;
							for (int x = 0; x < range.size(); x++) {
								std::pair <int, int> tmp_pair = range[x];
								//std::cout << "range is " << range.size() << std::endl;
								if (game->ruleCheck(i,j,tmp_pair.first,tmp_pair.second)) { 
									std::cout << "first ruleCheck: " << i << j << tmp_pair.first << tmp_pair.second << " is true" << std::endl;
									std::cout << "second ruleCheck: " << game->ruleCheck(i,j,tmp_pair.first, tmp_pair.second) << std::endl;
									std::string s = string_convert(i,j) + " " +
										string_convert(tmp_pair.first,tmp_pair.second);
									std::cout << "input :" << s << std::endl;
									tmp.push_back(s);
								}
							}
						}
						else if (name >= 'a' && name <= 'z' && this->getTeam() == 'z') {
							std::cout << "chess name: " << name << std::endl;
							for (int x = 0; x < range.size(); x++) {
								std::pair <int, int> tmp_pair = range[x];
								//std::cout << "range is " << range.size() << std::endl;
								if (game->ruleCheck(i,j,tmp_pair.first,tmp_pair.second)) {
									std::string s = string_convert(i,j) + " " +
										string_convert(tmp_pair.first, tmp_pair.second);
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

