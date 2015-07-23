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
	std::vector <string> tmp;
	for (int i = 0; i < 7; i++) {
		for (int j = 0; j < 7; j++) {
			Pieces * tmp_p = game->theBoard[i][j];
			char name = tmp_p->getName();
			std::vector< std::pair <int, int> > range = tmp_p->getRange();
			if (name >= 'A' && name <= 'Z' && team == 'A') {
				for (int x = 0; x < range.size(); x++) {
					std::pair <int, int> tmp_pair = tmp_range[x];
					if (ruleCheck(i,j,tmp_pair.first,tmp_pair.second)) {
						string s = string_convert(i,j) + " " +
							   string_convert(tmp_pair.first,tmp_pair.second);
						tmp.push_back(s);
					}
				}
			}
			else if (name >= 'a' && name <= 'z' && team == 'z') {
				for (int x = 0; x < range.size(); x++) {
					std::pair <int, int> tmp_pair = tmp_range[x];
					if (ruleCheck(i,j,tmp_pair.first,tmp_pair.second)) {
						string s = string_convert(i,j) + " " +
							   string_convert(tmp_pair.first, tmp_pair.second);
						tmp.push_back(s);
					}
				}
			}
		}
	}
	srand(time(NULL));
	int random = rand()%(tmp.size()-1);
	string str_rtn =  tmp[random];
	return str_rtn;
}













