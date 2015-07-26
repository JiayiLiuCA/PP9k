#ifndef __COMPUTER_H__
#define __COMPUTER_H__
#include <string>
#include <sstream>
#include <iostream>
#include "controller.h"
#include <sstream>
#include <iostream>

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
};

class Computer4: public Controller {
	public:
		void makeMove();
		Computer4(Board* game, char team);
};

#endif
