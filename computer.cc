#include <iostream>
#include "computer.h"
#include <string>
#include <vector>
#include <stdlib.h>
#include <time.h>

string string_convert(std::pair <int, int> p) {
	string str = "";
	istringstream ss(p.first);
	char c1;
	ss >> c1;
	istringstream ss(p.second);
	char c2;
	ss >> c2;
	str = str + c1 + " " + c2;
	return str;
}
	
	

string Computer::makeMove() {
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
						tmp.push_back(string_convert(tmp_pair));
					}
				}
			}
			else if (name >= 'a' && name <= 'z' && team == 'z') {
				for (int x = 0; x < range.size(); x++) {
					std::pair <int, int> tmp_pair = tmp_range[x];
					if (ruleCheck(i,j,tmp_pair.first,tmp_pair.second)) {
						tmp.push_back(string_convert(tmp_pair));
					}
				}
			}
		}
	}
	srand(time(NULL));
	int random = rand()%(tmp.size()-1);
	string str_rtn = tmp[random];
	return str_rtn;
}













