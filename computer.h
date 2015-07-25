#ifndef __COMPUTER_H__
#define __COMPUTER_H__
#include <string>
#include "controller.h"

class Computer: public Controller {
	public:
		void makeMove();
		Computer(Board* game, char team);
};
#endif
