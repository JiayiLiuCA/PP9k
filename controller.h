#ifndef __CONTROLLER_H__
#define __CONTROLLER_H__
#include "board.h"

class Controller {
		Board* game; //this keeps track of the game board status
		bool isComputer; // if the controller is computer then it is true
	public:
		makeMove(int old_r, int old_c, int r, int c) = 0; //controller declares a move
		Controller(bool isComputer, Board* gameboard);//constructor for Controller
		~Controller();
};
#endif
