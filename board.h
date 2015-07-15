#include "pieces.h"
#include "controller.h"
#include "view.h"
#include <vector>


class Board {
		//to make sure we only have one game board, we use the singleton pattern
		static Board* singleton;	
		<vector <vector <Pieces* > > > theBoard; //the board
		Controller* p1;  //Player 1
		Controller* p2;  //Player 2
		View* gd; // the graphical display
		View* td; // the text display
		Board();  //Constructor constructs an empty board
		~Board();
		static void cleanup();
	public:
		void play(); //this command begins the whole game 
		static Board* getInstance(); 
		void remove(int r, int c); //remove the pieces at (r, c)
		void add(int r, int c, char p); //add a piece at (r, c)
};
