#ifndef __BOARD_H__
#define __BOARD_H__

#include <vector>
#include <cstdlib>
#include <string>

class Pawn;

class Controller;

class Pieces;

class View;

class Board {
		//to make sure we only have one game board, we use the singleton pattern
		static Board* singleton;
		std::vector < std::vector < std::vector <Pieces*> > > attackBoard; //the board indecating which pieces can attack the 
		int turn; //determines whose turn to move, 0 represents white and 1 represents black
		std::vector <std::vector <Pieces* > > theBoard; //the board
		Controller* p1;  //Player 1 (white-player)
		Controller* p2;  //Player 2 (black-player)
		double p1Score;
		double p2Score;
		bool playing; //determine whether a game is running or not
		Pawn* enpassant; //whether there is a Pawn could be enpassant
		bool updateEnpassant; //whether the enpassant is update or not
		View* gd; // the graphical display
		View* td; // the text display
		std::vector <std::pair < std::vector <int>, std::string> > stack; //use to store the history moves;
		Board();  //Constructor constructs an empty board
		~Board();
		static void cleanup();
	public:
		bool graphmode; //whether the graph is on or not
		void clearGame(); //clear all the pieces on the board and reset a new game  
		void play(int graph, std::string); //this command begins the whole game 
		static Board* getInstance();
		void updatePiece(int r, int c);//update the attackBoard	
		void updateGrid(int r, int c);
		Pieces* getPiece(int r, int c);
		std::vector <Pieces *> getAttack(int r, int c);
		std::vector<int> convert(std::string pos); //this translates the string coordinates and return the number coords in a vector of int
//the methods below are designed to use in setup mode
//---------------------------------------------------------------
		void remove(int r, int c); //remove the pieces at (r, c)
		void add(int r, int c, char p, bool move); //add a piece at (r, c)
		bool checkBoard(); //check whether the current board is "valid" in setup mode thus determing whether to end setup mode or not
//---------------------------------------------------------------		
		void notify(std::string move, char team); //the boards take moving commands from controller
		void move(int oldr, int oldc, int newr, int newc); //move a piece fromoldrow oldcol to new row new col
		bool ruleCheck(int oldr, int oldc, int newr, int newc);//this checks whether this move is legal or not
		bool check(char king); //determine whether a king is in check or not('K' or 'k')
		bool preCheck(int row, int col, int new_row, int new_col);	
		bool checkMate(char king); //determine whether it is a checkmate for king
		void removeRange(int r, int c);
		bool castling(int r, int c, int nr, int nc, char k);
		void preundo();
		void undo();//undo a previous move
		bool stalemate(char team);

};
#endif
