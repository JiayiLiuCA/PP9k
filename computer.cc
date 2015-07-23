#include <iostream>
#include "computer.h"
#include <string>
#include <vector>
#include <stdlib.h>
#include <time.h>
#include <sstream>

std::string string_convert(int a, int b) {
	std::string str = "";
	int a1 = 8-a;
	std::istringstream ss(a1);
	char c1;
	ss >> c1;
	char c2 = 'a' + b;
	str = str + c2 + c1;
	return str;
}
	
	

std::string Computer::makeMove() {
	std::vector <std::string> tmp;
	for (int i = 0; i < 7; i++) {
		for (int j = 0; j < 7; j++) {
			char name = game->theBoard[i][j]->getName();
			std::vector< std::pair <int, int> > range = game->theBoard[i][j]->getRange();
			if (name >= 'A' && name <= 'Z' && team == 'A') {
				for (int x = 0; x < range.size(); x++) {
					std::pair <int, int> tmp_pair = range[x];
					if (game->ruleCheck(i,j,tmp_pair.first,tmp_pair.second)) {
						std::string s = string_convert(i,j) + " " +
							   string_convert(tmp_pair.first,tmp_pair.second);
						tmp.push_back(s);
					}
				}
			}
			else if (name >= 'a' && name <= 'z' && team == 'z') {
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
	std::string str_rtn =  tmp[random];
	return str_rtn;
}













