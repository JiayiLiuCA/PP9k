#ifndef __HUMAN_H__
#define __HUMAN_H__

#include "controller.h"


class Human: public Controller{
	public: 
		string makeMove();
};
#endif
