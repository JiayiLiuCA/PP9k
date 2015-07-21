#ifndef __HUMAN_H__
#define __HUMAN_H__

#include "controller.h"


class Human: public Controller{
	public: 
		void makeMove();
		Human(Board* game, char team);
};
#endif
