#ifndef __CONTROLLER_H__
#define __CONTROLLER_H__
#include "board.h"

class Controller {
		Board* game; //this keeps track of the game board status
	public:
		makeMove(int old_r, int old_c, int r, int c) = 0; //controller declares a move
		notify(




#endif
