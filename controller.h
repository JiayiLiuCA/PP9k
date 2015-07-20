#ifndef __CONTROLLER_H__
#define __CONTROLLER_H__
#include "board.h"

class Controller {
	protected:
		Board* game; //this keeps track of the game board status
	public:
		virtual void makeMove() = 0; //controller declares a move
		Controller(Board* gameboard): game(gameboard) {}//constructor for Controller
		virtual ~Controller() = 0;
};
#endif
