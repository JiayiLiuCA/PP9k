#ifndef __COMPUTER_H__
#define __COMPUTER_H__
#include <string>
#include <sstream>
#include <iostream>
#include "controller.h"
#include <sstream>
#include <iostream>

std::string string_convert(int a, int b) {
	std::string str;
	int a1 = 8 - a;
	std::ostringstream ss;
	ss << a1;
	str = ss.str();
	char c1 = 'a' + b;
	str = c1 + str;
	return str;
}

class Computer1: public Controller {
	public:
		void makeMove();
		Computer1(Board* game, char team);
};

class Computer2: public Controller {
	public:
		void makeMove();
		Computer2(Board* game, char team);
};

class Computer3: public Controller {
	public:
		void makeMove();
		Computer3(Board* game, char team);
}

class Computer4: public Controller {
	public:
		void makeMove();
		Computer4(Board* game, char team);
}

#endif
