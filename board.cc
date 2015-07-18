#include "board.h"
#include "view.h"
#include "concrete_pieces.h"
#include <vector>
#include <sstream>
#include <iostream>

Board* Board::singleton = NULL;


Board::Board() {
	std::vector <Pieces*> tmp;
	tmp.assign(8, NULL);
	theBoard.assign(8, tmp);
	p1Score = 0;
	p2Score = 0;
	turn = 0;
	p1 = NULL;
	p2 = NULL;
	gd = NULL;
	td = NULL;	
}

Board::~Board() {
	delete gd;
	delete td;
	delete p1;
	delete p2;
	p1Score = 0;
	p2Score = 0;
}
	
	
Board* Board::getInstance() {
	if(singleton) return singleton;
	singleton = new Board;
	atexit(cleanup);
	return singleton;
}

void Board::cleanup() {
   delete singleton;
}


void Board::remove(int r, int c) {
	if(0 <= r && r < 8 && 0 <= c && c < 8 && theBoard[r][c]) {
		delete theBoard[r][c];
		theBoard[r][c] = NULL;
		td->notify(r, c);
	}
	else std::cout << "invalid remove" << std::endl;
}

void Board::add(int r, int c, char p) {
	if(0 <= r && r < 8 && 0 <= c && c < 8) {
		if(theBoard[r][c]) {
			delete theBoard[r][c];
			theBoard[r][c] = NULL;
		}
		if(p == 'r' || p == 'R') theBoard[r][c] = new Rook(r, c, p);
		if(p == 'n' || p == 'N') theBoard[r][c] = new Knight(r, c, p);
		if(p == 'b' || p == 'B') theBoard[r][c] = new Bishop(r, c, p);
		if(p == 'q' || p == 'Q') theBoard[r][c] = new Queen(r, c, p);
		if(p == 'k' || p == 'K') theBoard[r][c] = new King(r, c, p);
		if(p == 'p' || p == 'P') theBoard[r][c] = new Pawn(r, c, p, false);
		td->notify(r, c, p);
	}
	else std::cout << "not valid add" << std::endl;
}

std::vector <int> Board::convert(std::string pos) {
	std::stringstream ss(pos);
	char c;
	int n;
	std::vector <int> result;
	ss >> c >> n;
	result.push_back(8 - n);
	result.push_back(c - 'a');
	return result;
}




void Board::play() {
	while(true) {
		std::string command;
		std::cin >> command;
		if(command == "setup") {
			std::string opt;
			std::cin >> opt;
			if(opt == "-") {
				std::string pos;
				std::cin >> pos;
				remove(convert(pos)[0], convert(pos)[1]);
				td->print();
			}
			else {
				char piece;
				std::string pos;
				std::cin >> piece >> pos;
				add(convert(pos)[0], convert(pos)[1], piece);
				td->print();
			}
		}
	}
}



