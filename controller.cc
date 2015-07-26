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

int value(char p) {
	if (p == 'q' || p == 'Q') {
		return 7;
	}
	else if (p == 'r' || p == 'R') {
		return 5;
	}
	else if (p == 'b' || p == 'B') {
		return 4;
	}
	else if (p == 'n' || p == 'N') {
		return 3;
	}
	else {
		return 1;
	}
}

