#include <iostream>
#include "computer.h"
#include <string>
#include <vector>
#include <stdlib.h>
#include <time.h>
#include <sstream>
#include "pieces.h"
#include "controller.h"


Computer1::Computer1(Board *game, char team): Controller(game, team) {}


void Computer1::makeMove() {
	std::vector <std::string> outcomes;
	char team = getTeam();
	std::string s;
	std::cin >> s;
	if(s == "move") {
		for(int i = 0; i < 8; i ++) {
			for(int j = 0; j < 8; j ++) {
				if((game->getPiece(i, j) != NULL) && abs(team - (game->getPiece(i, j))->getName()) < 25) {
					Pieces * tmp = game->getPiece(i, j);
					std::vector <std::pair <int, int> > range = tmp->getRange();
					for(std::vector <std::pair <int, int> >::iterator it = range.begin(); it != range.end(); it ++) {
						int newr = it->first;
						int newc = it->second;
						if(game->preCheck(i, j, newr, newc)) {
							if(game->ruleCheck(i, j, newr, newc)) {
									std::string s = string_convert(i,j) + " " + string_convert(newr, newc); 
									outcomes.push_back(s);
							}
						}
					}
				}
			}
		}
		srand(time(NULL));
		int random = rand() % (outcomes.size() - 1);
		game->notify(outcomes[random], this->getTeam());
	}
	else std::cout << "invalid command please enter again" << std::endl;
}
							
					

	
