#ifndef __COMPUTER_H__
#define __COMPUTER_H__
#include <string>
#include "controller.h"

class Computer: public: controller {
	public:
		string makeMove();
};
#endif
