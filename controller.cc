#include "controller.h"
#include <sstream>


Controller::~Controller() {
	game = NULL;
}


char Controller::getTeam() {
	return team;
}

std::string string_convert (int a, int b) {
	std::string str;
	int a1 = 8 - a;
	std::ostringstream ss;
	ss << a1;
	str = ss.str();
	char c1 = 'a' + b;
	str = c1 + str;
	return str;
}

