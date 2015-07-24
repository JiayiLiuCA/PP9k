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
	std::vector <Pieces*> empty;
	std::vector < std::vector <Pieces* > > tmp2(8, empty);
	attackBoard.assign(8, tmp2);
	p1Score = 0;
	p2Score = 0;
	turn = 0;
	p1 = NULL;
	p2 = NULL;
	gd = NULL;
	td = NULL;
	playing = false;
	enpassant = NULL;	
}

Board::~Board() {
	delete gd;
	delete td;
	delete p1;
	delete p2;
	p1Score = 0;
	p2Score = 0;
	playing = false;
	enpassant = NULL;
	updateEnpassant = false;
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
		if(theBoard[r][c] != NULL) {
			removeRange(r, c);
			delete theBoard[r][c];
		}
		theBoard[r][c] = NULL;
		td->notify(r, c);
	}
	else std::cout << "invalid remove" << std::endl;
}

void Board::add(int r, int c, char p) {
	if(0 <= r && r < 8 && 0 <= c && c < 8) {
		if(theBoard[r][c]) {
			remove(r, c);
		}
		if(p == 'r' || p == 'R') {
			theBoard[r][c] = new Rook(r, c, p);
			updatePiece(r, c);
		}
		if(p == 'n' || p == 'N') {
			theBoard[r][c] = new Knight(r, c, p);	
			updatePiece(r, c);
		}
		if(p == 'b' || p == 'B') {
			theBoard[r][c] = new Bishop(r, c, p);
			updatePiece(r, c);
		}
		if(p == 'q' || p == 'Q') {
			theBoard[r][c] = new Queen(r, c, p);
			updatePiece(r, c);
		}
		if(p == 'k' || p == 'K') {
			theBoard[r][c] = new King(r, c, p);
			updatePiece(r, c);
		}
		if(p == 'p' || p == 'P') {
			theBoard[r][c] = new Pawn(r, c, p);
			updatePiece(r, c);
		}
		td->notify(r, c, p);
	}
	else std::cout << "not valid add" << std::endl;
}

void Board::removeRange(int r, int c) {
	std::cout << "in range" << std::endl;
	Pieces* current = theBoard[r][c];
	std::vector < std::pair <int, int> > range = theBoard[r][c]->getRange();
	for(std::vector < std::pair <int, int> >::iterator it = range.begin(); it != range.end(); it ++) {
		std::cout << "first loop" << std::endl;
		int newr = it->first;
		int newc = it->second;
		std::cout << newr << " " << newc << std::endl;
		std::vector <Pieces*> attack = attackBoard[newr][newc];
		if(attack.size() != 0) {
			for( std::vector < Pieces* >::iterator ait = attackBoard[newr][newc].begin(); ait < attackBoard[newr][newc].end(); ait ++) {
		//		std::cout << "second loop" << std::endl;
		//		std::cout << "before : " << attack.size() << std::endl;
				if(*ait == current) attackBoard[newr][newc].erase(ait);
			}
		}
	}
	std::cout << "out range" << std::endl;
}


void Board::updatePiece(int r, int c) {
	removeRange(r, c);
	std::vector < std::pair <int, int> > range = theBoard[r][c]->getRange();
	for(std::vector < std::pair <int, int> >::iterator it = range.begin(); it != range.end(); it ++) {
		int newr = it->first;
		int newc = it->second;
		std::vector <Pieces*> attack = attackBoard[newr][newc];
		if(preCheck(r, c, newr, newc)) attackBoard[newr][newc].push_back(theBoard[r][c]);
	}
}

void Board::updateGrid(int r, int c) {
	std::cout << "in the grid the size is ";
	std::vector < Pieces *> attack = attackBoard[r][c];
	std::cout << attack.size() << std::endl;
	if(attack.size() == 0) {
		std::cout << "this is an empty grid" << std::endl;
		return ;
	}
	else {
		for(int i = 0; i < attack.size(); i ++) {
			Pieces* tmp = attackBoard[r][c][i];
			updatePiece(tmp->getr(), tmp->getc());
		}
	}
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
		else if((it != pieces.begin() + 15 && it != pieces.begin() + 47) && *it > 2)  {
			std::cout << "invalid number of other pieces (e.g. Bishops, Knights or Rooks)" << std::endl;
			return false; //everything else must have at most 2
		}
	}
	if(check('K')) {
		std::cout << "white king is in check" << std::endl;
		return false;
	}
	if(check('k')) {
		std::cout << "black king is in check" << std::endl;
		return false;
	}
	for(int i = 0; i < 8; i ++) {
		Pieces* tmp = theBoard[0][i];
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

bool Board::preCheck(int row, int col, int new_row, int new_col) {
	Pieces *tmp = theBoard[row][col];
	Pieces *newtmp = theBoard[new_row][new_col];
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
		std::cout << "moveCheck() fail" << std::endl;
		return false;
	}
	else if (n == 'N' || n == 'n' || n == 'K' || n == 'k') {
		return true;
	}
	else if (n == 'R' || n == 'r' || n == 'Q' || n == 'q' || n == 'B' || n == 'b') {
		for (int i = 1; i < diff_row; i++) {
			if (theBoard[row + dir_row * i][col + dir_col * i] != NULL) {
				return false;
			}
		}
		return true;
	}
	else if (n == 'p' && diff_col == 0) {
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
	else if (n == 'p' && diff_col == 1) {
		if (theBoard[new_row][new_col] != NULL || (static_cast<Pawn *>(theBoard[row][new_col]) == enpassant) && enpassant != NULL) {
			return true;
		}
		else {
			return false;
		}
	}
	else if (n == 'P' && diff_col == 0) {
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
	else if (n == 'P' && diff_col == 1) {
		if (theBoard[new_row][new_col] != NULL || ((static_cast<Pawn *>(theBoard[row][new_col]) == enpassant) && enpassant != NULL)) {
			return true;
		}
		else {
			return false;
		}
	}
}



bool Board::ruleCheck(int row, int col, int new_row, int new_col) {
	std::cout << "in rule" << std::endl;
	bool isMove = false;
	Pieces* tmp1 = theBoard[row][col];
	for(std::vector <Pieces*>::iterator it = attackBoard[new_row][new_col].begin(); it != attackBoard[new_row][new_col].end(); it ++) {
		if(*it == tmp1) isMove = true;
	}

	if(theBoard[new_row][new_col] != NULL) {
		if(abs(tmp1->getName() - theBoard[new_row][new_col]->getName()) < 25) return false;
	}
	else {
		Pieces* tmp = NULL;
		if(theBoard[new_row][new_col] != NULL) {
			tmp = theBoard[new_row][new_col];
			removeRange(new_row, new_col);
		}
		removeRange(row, col);
		theBoard[new_row][new_col] = theBoard[row][col];
		theBoard[row][col] = NULL;
		theBoard[new_row][new_col]->setr(new_row);
		theBoard[new_row][new_col]->setc(new_col);
		theBoard[new_row][new_col]->setRange();
		updateGrid(row, col);
		updateGrid(new_row, new_col);
		updatePiece(new_row, new_col);
		if((turn == 0 && check('K')) || (turn == 1 && check('k'))) {
			std::cout << "this move will put your king in check" << std::endl;
			removeRange(new_row, new_col);
			theBoard[row][col] = theBoard[new_row][new_col];
			theBoard[new_row][new_col] = tmp;
			theBoard[row][col]->setr(row);
			theBoard[row][col]->setc(col);
			theBoard[row][col]->setRange();
			updateGrid(row, col);
			updateGrid(new_row, new_col);
			if(tmp) updatePiece(new_row, new_col);
			updatePiece(row, col);
			return false;
		}
		else {
			std::cout << "king is not in check" << std::endl;
			removeRange(new_row, new_col);
			theBoard[row][col] = theBoard[new_row][new_col];
			theBoard[new_row][new_col] = tmp;
			theBoard[row][col]->setr(row);
			theBoard[row][col]->setc(col);
			theBoard[row][col]->setRange();
			updateGrid(row, col);
			updateGrid(new_row, new_col);
			if(tmp) updatePiece(new_row, new_col);
			updatePiece(row, col);
			std::cout << "end rule" << std::endl;
			return true;
		}
	}
}


void Board::notify(std::string move, char team) {
	if(move == "resign") {
		if(turn == 0) {
			std::cout << "black wins!" << std::endl;
			p2Score ++;
			playing = false;
		}
		else {
			std::cout << "white wins!" << std::endl;
			p1Score ++;
			playing = false;
		}
	}
	else {
		std::stringstream ss(move);
		std::string pos1, pos2;
		ss >> pos1 >> pos2;
		int oldr, oldc, newr, newc;
		oldr = convert(pos1)[0];
		oldc = convert(pos1)[1];
		newr = convert(pos2)[0];
		newc = convert(pos2)[1];
		std::cout << "initial over" << std::endl;
		if(theBoard[oldr][oldc] == NULL ||!ruleCheck(oldr, oldc, newr, newc)) {
			std::cout << "invalid move please enter again" << std::endl;
			if(turn == 0) p1->makeMove();
			else p2->makeMove();
			return;
		}
		else {
			char piece = theBoard[oldr][oldc]->getName();
			if(abs(piece - team) > 25) {
				std::cout << "you cannot move your opponents pieces" << std::endl;
				if(turn == 0) p1->makeMove();
				else p2->makeMove();
				return;
			}
			else {
				this->move(oldr, oldc, newr, newc);
			}

		}
	}
}




bool Board::check(char king) {
	int row, col;
	char piece;
	for(int i = 0; i < 8; i ++) {
		for(int j = 0; j < 8; j ++) {
			if(theBoard[i][j] != NULL) {
				if(theBoard[i][j]->getName() == king) {
					row = i;
					col = j;
				}}}}
	std::vector< Pieces* > tmp = attackBoard[row][col];
	for(std::vector< Pieces* >::iterator it = tmp.begin(); it != tmp.end(); it ++) {
		if(abs((*it)->getName() - king) > 25) return true;
	}
	return false;
}



void Board::move(int oldr, int oldc, int newr, int newc) {
	std::cout << "into the move " << std::endl;
	removeRange(oldr, oldc);
	char name = theBoard[oldr][oldc]->getName();
	if(name == 'p' || name == 'P') {
		std::cout << "in p/P" << std::endl;
		if(abs(newr - oldr) == 2) {
			std::cout << "in move 2" << std::endl;
			enpassant = static_cast<Pawn *>(theBoard[oldr][oldc]);
			updateEnpassant = true;
		}
		else if(theBoard[newr][newc] == NULL && abs(newc - oldc) == 1) {
			std::cout << "in enpassant" << std::endl;
			remove(oldr, newc);
			updateEnpassant = false;
		}

	}
	if(theBoard[newr][newc] != NULL) {
		if(static_cast<Pawn *>(theBoard[newr][newc]) == enpassant) enpassant = NULL;
		remove(newr, newc);
		updateEnpassant = false;
	}
	theBoard[oldr][oldc]->setMove(true);
	theBoard[newr][newc] = theBoard[oldr][oldc];
	theBoard[oldr][oldc] = NULL;
	theBoard[newr][newc]->setr(newr);
	theBoard[newr][newc]->setc(newc);
	updatePiece(newr, newc);
	updateGrid(newr, newc);
	updateGrid(oldr, oldc);	
	td->notify(oldr, oldc);
	td->notify(newr, newc, name);
	td->print();
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
				else if(opt == "stdinit") {              //this command provide a standard initial state of a chess
					for(int i = 0; i < 8; i ++) {
						add(1, i, 'p');
						add(6, i, 'P');
					}
					add(0, 0, 'r');
					add(0, 7, 'r');
					add(0, 1, 'n');
					add(0, 6, 'n');
					add(0, 2, 'b');
					add(0, 5, 'b');
					add(0, 3, 'q');
					add(0, 4, 'k');
					add(7, 0, 'R');
					add(7, 7, 'R');
					add(7, 1, 'N');
					add(7, 6, 'N');
					add(7, 2, 'B');
					add(7, 5, 'B');
					add(7, 3, 'Q');
					add(7, 4, 'K');
					td->print();
				}
				else if(opt == "done") {
					if(checkBoard()) break;
					else std::cout << "the current board is invalid you cannot exit setup mode" << std::endl;
				}
			}
		}
		else if(command == "game") {
			playing = true;
			std::string player1, player2;
			std::cin >> player1 >> player2;
			if(player1 == "human") p1 = new Human(this, 'A');
			else std::cout << "not support for AI now" << std::endl;
			if(player2 == "human") p2 = new Human(this, 'z');
			else std::cout << "not support for AI now" << std::endl;
			td->print();
			std::cout << "the battle begins!" << std::endl;
			while(true) {
				if(!updateEnpassant) enpassant = NULL;
				if(turn == 0 && playing) {
					std::cout << "white's turn to move" << std::endl;
					p1->makeMove();
				}
				else if(turn == 1 && playing) {
					std::cout << "black's turn to move" << std::endl;
					p2->makeMove();
				}
				turn = !turn;
			}
		}
	}
}


