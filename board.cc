#include "board.h"
#include "textdisplay.h"
#include "concrete_pieces.h"
#include "human.h"
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
		if((it == pieces.begin() + 42 || it == pieces.begin() + 10) && (*it != 1))  {
			std::cout << "invalid number of Kings" << std::endl;
			return false;  //must have exactly 1 King on each side
		}	
		else if ((it == pieces.begin() + 16 || it == pieces.begin() + 48) && *it > 1) {
			std::cout << "invalid number fo Queens" << std::endl;
			return false; //can have at most one Queen
		}
		else if((it == pieces.begin() + 15 || it == pieces.begin() + 47) && *it > 8) {
			std::cout << "invalid number of Pawns" << std::endl;
			return false; //can have at most 8 Pawn
		}
		else if(*it > 2)  {
			std::cout << "invalid number of other pieces (e.g. Bishops, Knights or Rooks)" << std::endl;
			return false; //everything else must have at most 2
		}
	}
	if(check('K') || check('k')) {
		std::cout << "King is in check!" << std::endl;
		return false;
	}
	for(int i = 0; i < 8; i ++) {
		Pieces* tmp = theBoard[1][i];
		Pieces* tmp2 = theBoard[7][i];
		if(tmp != NULL && (tmp->getName() == 'P' || tmp->getName() == 'p')) {
			std::cout << "Pawn(s) are not in valid position" << std::endl;
			return false;
		}
		if (tmp2 != NULL && (tmp2->getName() == 'p' || tmp2->getName() == 'P')) {
			std::cout << "Pawn(s) are not in valid position" << std::endl;
			return false;
		}
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
	if (diff_row != 0) {
		dir_row = diff_row / (new_row - row);
	}
	else {
		dir_row = 0;
	}
	if (diff_col != 0) {
		dir_col = diff_col / (new_col - col);
	}
	else {
		dir_col = 0;
	}
	if (tmp->moveCheck(row,col,new_row,new_col) == false) {
		std::cout << tmp->getName() << std::endl;
		std::cout << tmp->moveCheck(row,col,new_row,new_col) << std::endl;
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

void Board::notify(std::string move) {
	std::stringstream ss(move);
	std::string pos1, pos2;
	ss >> pos1 >> pos2;
	int oldr, oldc, newr, newc;
	oldr = convert(pos1)[0];
	oldc = convert(pos1)[1];
	newr = convert(pos2)[0];
	newc = convert(pos2)[1];
	if(!ruleCheck(oldr, oldc, newr, newc)) {
		std::cout << "invalid move please enter again" << std::endl;
		if(turn == 0) p1->makeMove();
		else p2->makeMove();
	}
	else this->move(oldr, oldc, newr, newc);
}




bool Board::check(char king) {
	int newr, newc, oldr, oldc;
		for(std::vector < std::vector <Pieces*> >::iterator it = theBoard.begin(); it != theBoard.end(); it ++) {
			for(std::vector <Pieces*>::iterator i = it->begin(); i != it->end(); i ++) {
				if(*i != NULL) {
					if((*i)->getName() == king) {
						newr = (*i)->getr();
						newc = (*i)->getc();
						std::cout << newr << " " << newc << std::endl;
					}}}}
		for(std::vector< std::vector <Pieces*> >::iterator it = theBoard.begin(); it != theBoard.end(); it ++) {
			for(std::vector <Pieces*>::iterator i = it->begin(); i != it->end(); i ++) {
				if(*i != NULL) {
					oldr = (*i)->getr();
					oldc = (*i)->getc();
					std::cout << oldr << " " << oldc << std::endl;
					if(ruleCheck(oldr, oldc, newr, newc)) return true;
				}}}
	return false;
}

				

void Board::move(int oldr, int oldc, int newr, int newc) {
	char name = theBoard[oldr][oldc]->getName();
	if(theBoard[newr][newc] != NULL) {
		delete theBoard[newr][newc];
		td->notify(newr, newc);
	}
	theBoard[newr][newc] = theBoard[oldr][oldc];
	td->notify(oldr, oldc);
	td->notify(newr, newc, name);
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
				else if(opt == "stdinit") {
					for(int i = 0; i < 8; i ++) {
						add(1, i, 'p');
						add(6, i, 'P');
						if(i == 0) {
							add(i, 0, 'r');
							add(i, 7, 'r');
							add(i, 1, 'n');
							add(i, 6, 'n');
							add(i, 2, 'b');
							add(i, 5, 'b');
							add(i, 3, 'q');
							add(i, 4, 'k');
						}
						if(i == 7) {
							add(i, 0, 'R');
							add(i, 7, 'R');
							add(i, 1, 'N');
							add(i, 6, 'N');
							add(i, 2, 'B');
							add(i, 5, 'B');
							add(i, 3, 'Q');
							add(i, 4, 'K');
						}
					}
				}
				else if(opt == "done") {
					if(checkBoard()) break;
					else std::cout << "the current board is invalid you cannot exit setup mode" << std::endl;
				}
			}
		}
		else if(command == "game") {
			std::string player1, player2;
			std::cin >> player1 >> player2;
			if(player1 == "human") p1 = new Human(this);
			else std::cout << "not support for AI now" << std::endl;
			if(player2 == "human") p2 = new Human(this);
			else std::cout << "not support for AI now" << std::endl;
			while(true) {
				if(turn == 0) {
					p1->makeMove();
					turn = 1;
				}
				else {
					p2->makeMove();
					turn = 0;
				}
			}
		}

	}
}
				

