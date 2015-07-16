#ifndef __BOARD_H__
#define __BOARD_H__

#include "pieces.h"
#include "controller.h"
#include "view.h"
#include <vector>


class Board {
		//to make sure we only have one game board, we use the singleton pattern
		static Board* singleton;	
		<vector <vector <Pieces* > > > theBoard; //the board
		Controller* p1;  //Player 1 (white-player)
		Controller* p2;  //Player 2 (black-player)
		View* gd; // the graphical display
		View* td; // the text display
		Board();  //Constructor constructs an empty board
		~Board();
		static void cleanup();
	public:
		void play(); //this command begins the whole game 
		static Board* getInstance(); 
		//the methods below are designed to use in setup mode
		Pieces* convert(string pos); //this translates the string coordinates and return the pointer at that position
		void remove(string pos); //remove the pieces position
		void add(string pos, char p); //add a piece at (r, c)
		bool checkBoard(); //check whether the current board is "valid" in setup mode thus determing whether to end setup mode or not

		void move(string pos1, string pos2); //move a piece from pos1 to pos2


};
#endif
