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
		int p1Score;
		int p2Score;
		View* gd; // the graphical display
		View* td; // the text display
		Board();  //Constructor constructs an empty board
		~Board();
		static void cleanup();
	public:
		void play(); //this command begins the whole game 
		static Board* getInstance(); 
		std::vector<int> convert(string pos); //this translates the string coordinates and return the number coords in a vector of int
//the methods below are designed to use in setup mode
//---------------------------------------------------------------
		void remove(int r, int c); //remove the pieces at (r, c)
		void add(int r, int c, char p); //add a piece at (r, c)
		bool checkBoard(); //check whether the current board is "valid" in setup mode thus determing whether to end setup mode or not
//---------------------------------------------------------------		
		void notify(string move); //the boards take moving commands from controller
		void move(int oldr, int oldc, int newr, int newc); //move a piece fromoldrow oldcol to new row new col
		bool ruleCheck(int oldr, int oldc, int newr, int newc);//this checks whether this move is legal or not


};
#endif
