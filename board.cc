#include "board.h"
#include "textdisplay.h"
#include "concrete_pieces.h"
#include <vector>
#include <string>
#include <sstream>
#include <iostream>
#include <cmath>

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
		if(p == 'p' || p == 'P') theBoard[r][c] = new Pawn(r, c, p);
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

bool Board::checkBoard() {
	std::vector <int> pieces (60, 0);
	for(std::vector < std::vector <Pieces*> >::iterator it = theBoard.begin(); it != theBoard.end(); it ++) {
		for(std::vector <Pieces*>::iterator i = it->begin(); i != it->end(); i ++) {
			if(*i != NULL) {
				pieces[(*i)->getName() - 'A'] += 1;
			}
		}
	}
	for(std::vector <int>::iterator it = pieces.begin(); it != pieces.end(); it ++) {
		if((it == pieces.begin() + 42 || it == pieces.begin() + 10) && (*it != 1))  return false;  //must have 1 King on each side	
		else if ((it == pieces.begin() + 16 || it == pieces.begin() + 48) && *it > 1) return false; //can have at most one Queen
		else if((it == pieces.begin() + 15 || it == pieces.begin() + 47) && *it > 8) return false; //can have at most 8 Pawn
		else if(*it > 2)  return false; //everything else must have at most 2
	}
	return true;
}

bool Board::ruleCheck(int row, int col, int new_row, int new_col) {
	if (theBoard[row][col] == NULL) {
		return false;
	}
	Pieces *tmp = theBoard[row][col];
	char n = tmp->getName();
	int diff_row = std::abs(row - new_row);
	int diff_col = std::abs(col - new_col);
	int dir_row;
	int dir_col;
	if (!diff_row) {
		dir_row = diff_row / (new_row - row);
	}
	else {
		dir_row = 0;
	}
	if (!diff_col) {
		dir_col = diff_col / (new_col - col);
	}
	else {
		dir_col = 0;
	}
	if (tmp->moveCheck(row,col,new_row,new_col) == false) {
		return false;
	}
	else if (n == 'N' || n == 'n' || n == 'K' || n == 'k') {
	    return true;
	}
	else if (n == 'R' || n == 'r' || n == 'Q' || n == 'q' || n == 'B' || n == 'b') {
		for (int i = 0; i < diff_row; i++) {
			if (theBoard[row + dir_row][col + dir_col] != NULL) {
				return false;
			}
		}
	}
	else if (n == 'P' && diff_col == 0) {
		if (theBoard[row+1][col] != NULL) {
			return false;
		}
		if (diff_row == 2 && theBoard[row+2][col] != NULL) {
			return false;
		}
		else {
			return true;
		}
	}
	else if (n == 'P' && diff_col == 1) {
		if (theBoard[new_row][new_col] != NULL || (*theBoard[row][new_col]).getStatus()) {
			return true;
		}
		else {
			return false;
		}
	}
	else if (n == 'p' && diff_col == 0) {
		if (theBoard[row-1][col] != NULL) {
			return false;
		}
		if (diff_row == 2 && theBoard[row-2][col] != NULL) {
			return false;
		}
		else {
			return true;
		}
	}
	else if (n == 'p' && diff_col == 1) {
		if (theBoard[new_row][new_col] != NULL || (*theBoard[row][new_col]).getStatus()) {
			return true;
		}
		else {
			return false;
		}
	}
}

		

bool Board::check(int side) {
	int newr, newc, oldr, oldc;
	if(side == 0) {
		for(std::vector < std::vector <Pieces*> >::iterator it = theBoard.begin(); it != theBoard.end(); it ++) {
			for(std::vector <Pieces*>::iterator i = it->begin(); i != it->end(); i ++) {
				if(*i != NULL) {
					if((*i)->getName() == 'K') {
						newr = (*i)->getr();
						newc = (*i)->getc();
					}}}}
		for(std::vector< std::vector <Pieces*> >::iterator it = theBoard.begin(); it != theBoard.end(); it ++) {
			for(std::vector <Pieces*>::iterator i = it->begin(); i != it->end(); i ++) {
				if(*i != NULL) {
					oldr = (*i)->getr();
					oldc = (*i)->getc();
					if(ruleCheck(oldr, oldc, newr, newc)) return true;
				}}}}
	else {
		for(std::vector< std::vector <Pieces*> >::iterator it = theBoard.begin(); it != theBoard.end(); it ++) {
			for(std::vector <Pieces*>::iterator i = it->begin(); i != it->end(); i ++) {
				if(*i != NULL) {
					if((*i)->getName() == 'k') {
						newr = (*i)->getr();
						newc = (*i)->getc();
					}}}}
		for(std::vector< std::vector <Pieces*> >::iterator it = theBoard.begin(); it != theBoard.end(); it ++) {
			for(std::vector <Pieces*>::iterator i = it->begin(); i != it->end(); i ++) {
				if(*i != NULL) {
					oldr = (*i)->getr();
					oldc = (*i)->getc();
					if(ruleCheck(oldr, oldc, newr, newc)) return true;
				}}}}
	return false;
}

				



					

		


void Board::play() {
	while(true) {
		std::string command;
		std::cin >> command;
		if(command == "setup") {
				delete td;
				td = new TextDisplay();
				td->print();
			while(true) {
				std::string opt;
				std::cin >> opt;
				if(opt == "-") {
					std::string pos;
					std::cin >> pos;
					remove(convert(pos)[0], convert(pos)[1]);
					td->print();
				}
				else if(opt == "+") {
					char piece;
					std::string pos;
					std::cin >> pos >> piece;
					add(convert(pos)[0], convert(pos)[1], piece);
					td->print();
				}
				else if(opt == "=") {
					std::string color;
					std::cin >> color;
					if(color == "white") turn = 0;
					else if(color == "black") turn = 1;
					else std::cout << "not valid color" << std::endl;
				}
				else if(opt == "done") {
					if(checkBoard()) break;
					else std::cout << "the current board is invalid you cannot exit setup mode" << std::endl;
				}
			}
		}
	}
}
				


