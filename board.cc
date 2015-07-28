#include "board.h"
#include "textdisplay.h"
#include "graphicdisplay.h"
#include "concrete_pieces.h"
#include "human.h"
#include "computer.h"
#include <vector>
#include <string>
#include <sstream>
#include <iostream>
#include <cmath>
#include <algorithm>
#include <fstream>

Board* Board::singleton = NULL;

bool Istesting = true;

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
	graphmode = false;
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

void Board::clearGame() {
	for(int i = 0; i < 8; i ++) {
		for(int j = 0; j < 8; j ++) {
			if(theBoard[i][j] != NULL) {
				delete theBoard[i][j];
				theBoard[i][j] = NULL;
			}
			while(attackBoard[i][j].size() != 0) attackBoard[i][j].pop_back();
		}
	}
	turn = 0;
	playing = false;
	enpassant = NULL;
	updateEnpassant = false;
	delete td;
	delete gd;
	td = NULL;
	gd = NULL;
}

void Board::remove(int r, int c) {
	if(theBoard[r][c] == NULL) return;
	if(0 <= r && r < 8 && 0 <= c && c < 8 && theBoard[r][c]) {
		if(theBoard[r][c] != NULL) {
			removeRange(r, c);
			delete theBoard[r][c];
		}
		theBoard[r][c] = NULL;
		updateGrid(r, c);
		td->notify(r, c);
		if(graphmode)gd->notify(r, c);
	}
	else std::cout << "invalid remove" << std::endl;
}

void Board::add(int r, int c, char p, bool move) {
	if(0 <= r && r < 8 && 0 <= c && c < 8) {
		if(theBoard[r][c]) {
			remove(r, c);
		}
		if(p == 'r' || p == 'R') {
			theBoard[r][c] = new Rook(r, c, p, move);
			updatePiece(r, c);
			updateGrid(r, c);
		}
		if(p == 'n' || p == 'N') {
			theBoard[r][c] = new Knight(r, c, p, move);	
			updatePiece(r, c);
			updateGrid(r, c);
		}
		if(p == 'b' || p == 'B') {
			theBoard[r][c] = new Bishop(r, c, p, move);
			updatePiece(r, c);
			updateGrid(r, c);
		}
		if(p == 'q' || p == 'Q') {
			theBoard[r][c] = new Queen(r, c, p, move);
			updatePiece(r, c);
			updateGrid(r, c);
		}
		if(p == 'k' || p == 'K') {
			theBoard[r][c] = new King(r, c, p, move);
			updatePiece(r, c);
			updateGrid(r, c);
		}
		if(p == 'p' || p == 'P') {
			theBoard[r][c] = new Pawn(r, c, p, move);
			updatePiece(r, c);
			updateGrid(r, c);
		}
		td->notify(r, c, p);
		if(graphmode) gd->notify(r, c, p);
	}
	else std::cout << "not valid add" << std::endl;
}

Pieces* Board::getPiece(int r, int c) { return theBoard[r][c]; }

std::vector <Pieces *> Board::getAttack(int r, int c) { return attackBoard[r][c]; }


void Board::removeRange(int r, int c) {
	if(theBoard[r][c] == NULL) return;
	Pieces* current = theBoard[r][c];
	std::vector < std::pair <int ,int> > range = theBoard[r][c]->getRange();
	for(std::vector < std::pair <int, int> >::iterator it = range.begin(); it != range.end(); it ++) {
		int newr = it->first;
		int newc = it->second;
		std::vector <Pieces*> attack = attackBoard[newr][newc];
		if(attack.size() != 0) {
			for( std::vector < Pieces* >::iterator ait = attackBoard[newr][newc].begin(); ait < attackBoard[newr][newc].end(); ait ++) {
				if(*ait == current) attackBoard[newr][newc].erase(ait);
			}
		}
	}
}


void Board::updatePiece(int r, int c) {
	if(theBoard[r][c] == NULL) return;
	removeRange(r, c);
	std::vector < std::pair <int ,int> > range = theBoard[r][c]->getRange();
	for(std::vector < std::pair <int, int> >::iterator it = range.begin(); it != range.end(); it ++) {
		int newr = (*it).first;
		int newc = (*it).second;
		if(preCheck(r, c, newr, newc)) {
			attackBoard[newr][newc].push_back(theBoard[r][c]);
		}
	}
}

void Board::updateGrid(int r, int c) {
	std::vector < Pieces *> attack = attackBoard[r][c];
	if(attack.size() == 0) {
		return ;
	}
	else {
		int size = attackBoard[r][c].size();
		std::vector < std::pair <int, int> > total;
		for(int i = 0; i < size; i ++) {
			std::pair <int, int> tmp;
			tmp.first = attackBoard[r][c][i]->getr();
			tmp.second = attackBoard[r][c][i]->getc();
			total.push_back(tmp);
		}
		int bsize = total.size();
		for(int i = 0; i < bsize; i ++) {
			updatePiece(total[i].first, total[i].second);
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
	char n = tmp->getName();
	int diff_row = std::abs(row - new_row);
	int diff_col = std::abs(col - new_col);
	int dir_row;
	int dir_col;
	if (diff_row != 0) dir_row = diff_row / (new_row - row);
	else dir_row = 0;
	if (diff_col != 0) dir_col = diff_col / (new_col - col);
	else dir_col = 0;
	if (tmp->moveCheck(row,col,new_row,new_col) == false) return false;
	else if (n == 'N' || n == 'n' || n == 'K' || n == 'k') return true;
	else if (n == 'R' || n == 'r' || n == 'Q' || n == 'q' || n == 'B' || n == 'b') {
		for (int i = 1; i < std::max(diff_row, diff_col); i++) {
			if (theBoard[row + dir_row * i][col + dir_col * i] != NULL) {
				return false;
			}
		}
		return true;
	}
	else if (n == 'p' && diff_col == 0) {
		if (diff_row == 2 && theBoard[row+1][col] != NULL) {
			return false;
		}
		else {
			return true;
		}
	}
	else if (n == 'P' && diff_col == 0) {
		if (diff_row == 2 && theBoard[row-1][col] != NULL) {
			return false;
		}
		else {
			return true;
		}
	}
	else if(n == 'p' || n == 'P') return true;
}

bool Board::stalemate(char team) {
	for(int i = 0; i < 8; i ++) {
		for(int j = 0; j < 8; j ++) {
			if(theBoard[i][j] != NULL && abs(theBoard[i][j]->getName() - team) < 25) {
				std::vector < std::pair <int, int> > range = theBoard[i][j]->getRange();
				for(std::vector < std::pair <int ,int> >::iterator it = range.begin(); it != range.end(); it ++) {
					int r = it->first;
					int c = it->second;
					if(ruleCheck(i, j, r, c)) {
						return false;
					}
				}
			}
		}
	}
	return true;
}
							
					


bool Board::castling(int r, int c, int nr, int nc, char k) {
	int col_diff = abs(nc - c);
	if((nc - c) == 0) return false;
	int dir = col_diff / (nc - c);
	std::vector < Pieces* > tmp;
	if(theBoard[r][c]->getStatus()) {
		std::cout << "king has been moved" << std::endl;
		return false;
	}
	if(check(k)) {
		std::cout << "king is in check" << std::endl;
		return false;
	}
	else if (dir > 0) {
		if(theBoard[r][c + 3] == NULL) return false;
		if(theBoard[r][c + 3] != NULL && theBoard[r][c + 3]->getStatus()) return false;
		for(int i = 1; i < 3; i ++) {
			if(theBoard[r][c + i * dir] != NULL) return false;
			tmp = attackBoard[r][c + i * dir];
			for(std::vector < Pieces* >::iterator it = tmp.begin(); it != tmp.end(); it ++) {
				if(std::abs((*it)->getName() - k) > 22) return false;
			}
		}
		return true;
	}
	else if (dir < 0) {
		if(theBoard[r][c - 4] == NULL) {
			std::cout << "no rook" << std::endl;
			return false;
		}
		if(theBoard[r][c - 4] != NULL && theBoard[r][c - 4]->getStatus()) {
			std::cout << "rook has been moved" << std::endl;
			return false;
		}
		for(int i = 1; i < 4; i ++) {
			if(theBoard[r][c + i * dir] != NULL) {
				return false;
			}
			tmp = attackBoard[r][c + i * dir];
			if(i < 3) {
				for(std::vector < Pieces* >::iterator it = tmp.begin(); it != tmp.end(); it ++) {
					if(std::abs((*it)->getName() - k) > 22) {
						std::cout << "maybe check on the half way" << std::endl;
						return false;
					}
				}
			}
		}
		return true;
	}
}

bool Board::ruleCheck(int row, int col, int new_row, int new_col) {
	char name = '_';
	bool status1 = false;
	bool status2 = theBoard[row][col]->getStatus();
	int col_diff, row_diff;
	row_diff = abs(new_row - row);
	col_diff = abs(new_col - col);
	bool isMove = false;
	Pieces* tmp = theBoard[row][col];
	for(std::vector <Pieces*>::iterator it = attackBoard[new_row][new_col].begin(); it != attackBoard[new_row][new_col].end(); it ++) {
		if((*it) == tmp) {
			isMove = true;
		}
	}
	if(tmp->getName() == 'p' || tmp->getName() == 'P') {
		if(col_diff == 1) {
			if(theBoard[new_row][new_col] != NULL || (static_cast< Pawn* >(theBoard[row][new_col]) == enpassant && enpassant != NULL)) {
				if(static_cast< Pawn* >(theBoard[row][new_col]) == enpassant && enpassant != NULL) name = 'p';
				isMove = true;
			}
			else {
				return false;
			}
		}
		else if((tmp->getName() == 'p' && theBoard[row + 1][col] != NULL) || (tmp->getName() == 'P' && theBoard[row - 1][col] != NULL)) {
			return false;
		}
		else if(row_diff == 2 && ((tmp->getName() == 'p' && theBoard[row + 2][col] != NULL) || (tmp->getName() == 'P' && theBoard[row - 2][col] != NULL)))  return false;
	}
	if(isMove == false) {
		return false;
	}
	if((tmp->getName() == 'K' || tmp->getName() == 'k') && (col_diff == 2)) {
		if(castling(row, col, new_row, new_col, tmp->getName())) {
			return true;
		}
		else {
			if(!Istesting) std::cout << "castling fail" << std::endl;
			return false;
		}
	}
	if(theBoard[new_row][new_col] != NULL && abs(tmp->getName() - theBoard[new_row][new_col]->getName()) < 25) {
		if(!Istesting) std::cout << "you cannot eat allies " << std::endl;
		return false;
	}
	if(theBoard[new_row][new_col] != NULL) {
		status1 = theBoard[new_row][new_col]->getStatus();
		name = theBoard[new_row][new_col]->getName();
	}
	move(row, col, new_row, new_col);
	if((turn == 0 && check('K')) || (turn == 1 && check('k'))) {
		if(!Istesting)std::cout << "this move will put you king in check" << std::endl;
		preundo();
		return false;
	}
	else{
		preundo();
	}
	if(isMove) {
		return true;
	}
	else {
		return false;
	}

}


void Board::notify(std::string move, char team) {
	if(move == "resign") {
		if(turn == 0) {
			std::cout << "black wins!" << std::endl;
			p2Score ++;
			turn = 0;
			playing = false;
		}
		else {
			std::cout << "white wins!" << std::endl;
			p1Score ++;
			playing = false;
			turn = 0;
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
		if(oldr < 0 || oldr > 7 || oldc < 0 || oldc > 7 || newr < 0 || newr > 7 || newc < 0 || newc > 7) {
			std::cout << "out of range please enter again" << std::endl;
			if(turn == 0) p1->makeMove();
			else p2->makeMove();
			return;
		}
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
				int col_diff = abs(oldc - newc);
				char name = theBoard[oldr][oldc]->getName();
				if((name == 'k' || name == 'K') && col_diff == 2) {
					int dir = col_diff / (newc - oldc);
					this->move(oldr, oldc, newr, newc);
					std::pair < std::vector <int>, std::string > tmp;
					if(dir > 0) {
						this->move(oldr, oldc + 3, oldr, oldc + 1);
						if(name == 'k') tmp.second = "ck+";// "c" represents the castling "k"("K") represents the king(white or black) and "+" represent castling with the right rook, "-" represents castling with the left rook
						else tmp.second = "cK+";
					}
					else {
						this->move(oldr, oldc - 4, oldr, oldc - 1);
						if(name == 'k') tmp.second = "ck-";
						else tmp.second = "cK-";
					}
					stack.pop_back();
					stack.pop_back();
					stack.push_back(tmp);
					return ;
				}
				Istesting = false;
				this->move(oldr, oldc, newr, newc);
				if(((newr == 0) && (theBoard[newr][newc]->getName() == 'P')) || ((newr == 7) && (theBoard[newr][newc]->getName() == 'p'))) {
					char promote;
					ss >> promote;
					while((team == 'A' && promote != 'N' && promote != 'B' && promote != 'R' && promote != 'Q') || (team == 'z' && promote != 'n' && promote != 'b' && promote != 'r' && promote != 'q')) {
						std::cout << "invalid promotion please enter again(just the promotion char)" << std::endl;
						std::cin >> promote;
					}	
					remove(newr, newc);
					add(newr, newc, promote, true);
				}
			}
		}
	}
}





bool Board::check(char king) {
	int row, col;
	for(int i = 0; i < 8; i ++) 
		for(int j = 0; j < 8; j ++) 
			if(theBoard[i][j] != NULL) 
				if(theBoard[i][j]->getName() == king) {
					row = i;
					col = j;
				}
	std::vector< Pieces* > tmp = attackBoard[row][col];
	for(std::vector< Pieces* >::iterator it = tmp.begin(); it != tmp.end(); it ++) {
		bool ischeck = true;
		if(abs((*it)->getName() - king) > 22) {
			if(((*it)->getName() == 'P' || (*it)->getName() == 'p') && abs((*it)->getc() - col) == 0) ischeck = false;
			if(ischeck) return true;
		}
	}
	return false;
}

bool Board::checkMate(char king) {
	int r, c, checkr, checkc;
	char name;
	for(int i = 0; i < 8; i ++) 
		for(int j = 0; j < 8; j ++) 
			if(theBoard[i][j] != NULL) 
				if(theBoard[i][j]->getName() == king) {
					r = i;
					c = j;
				}
	std::vector< std::pair <int, int> > range = theBoard[r][c]->getRange();
	for(std::vector < std::pair <int, int> >::iterator it = range.begin(); it != range.end(); it ++) {
		int nr = it->first;
		int nc = it->second;
		if(ruleCheck(r, c, nr, nc)) {
			return false;
		}
	}
	int count = 0;
	std::vector <Pieces *> attack = attackBoard[r][c];
	for(std::vector <Pieces *>::iterator it = attack.begin(); it != attack.end(); it ++) {
		name = (*it)->getName();
		if(abs(name - king) > 22) {
			checkr = (*it)->getr();
			checkc = (*it)->getc();
			count ++;
		}
	}
	if(count > 1) return true;
	else {
		attack = attackBoard[checkr][checkc];
		for(std::vector <Pieces *>::iterator it = attack.begin(); it != attack.end(); it ++) {
			name = (*it)->getName();
			int olr = (*it)->getr();
			int olc = (*it)->getc();
			if((abs(name - king) < 22 && abs(name - king) != 0) && ruleCheck(olr, olc, checkr, checkc)) {
				return false;
			}
		}
		if(theBoard[checkr][checkc]->getName() == 'n' || theBoard[checkr][checkc]->getName() == 'N') return true;	
		else {
			int row_dir, col_dir;
			int row_diff = abs(checkr - r);
			int col_diff = abs(checkc - c);
			if(row_diff == 0) row_dir = 0;
			else row_dir = row_diff / (checkr - r);
			if(col_diff == 0) col_dir = 0;	
			else col_dir = col_diff / (checkc - c);
			for(int i = 1; i < std::max(row_diff, col_diff); i ++) {
				checkr = r + row_dir * i;
				checkc = c + col_dir * i;
				attack = attackBoard[checkr][checkc];
				for(std::vector <Pieces *>::iterator it = attack.begin(); it != attack.end(); it ++) {
					name = (*it)->getName();
					int olr = (*it)->getr();
					int olc = (*it)->getc();
					if((abs(name - king) < 22) && ruleCheck(olr, olc, checkr, checkc)) {
						return false;
					}
				}
			}
			return true;
		}
	}
}

void Board::undo() {
	if(stack.size() == 0) {
		std::cout << "you cannot undo anymore" << std::endl;
		return;
	}
	preundo();
	turn = !turn;
	td->print();
	if(turn == 0) {
		std::cout << "white's turn to move" << std::endl;
		p1->makeMove();
	}
	else {
		std::cout << "black's turn to move" << std::endl;
		p2->makeMove();
	}
}

void Board::preundo() {
	std::vector <std::pair <std::vector<int>, std::string> >::iterator it = stack.end() - 1;
	std::pair <std::vector <int>, std::string> move = *it;
	if(move.second[0] == 'c') {
		std::cout << move.second << std::endl;
		char king_name = move.second[1];
		char dir = move.second[2];
		if(dir == '-' && king_name == 'k') {
			theBoard[0][4] = theBoard[0][2]; theBoard[0][2] = NULL; theBoard[0][0] = theBoard[0][3]; 
			theBoard[0][3] = NULL; theBoard[0][4]->setr(0); theBoard[0][4]->setc(4); theBoard[0][4]->setRange();
			theBoard[0][4]->setMove(false); theBoard[0][0]->setr(0); theBoard[0][0]->setc(0); theBoard[0][0]->setRange(); 
			theBoard[0][0]->setMove(false); updatePiece(0,4); updatePiece(0,0); updateGrid(0,0); updateGrid(0,4); td->notify(0,2); 
			td->notify(0, 3); td->notify(0, 4, 'k'); 
			if(graphmode && !Istesting) {
				gd->notify(0,2); 
				gd->notify(0, 3); 
				gd->notify(0, 4, 'k'); 
				gd->notify(0, 0, 'r'); 
			}
		}
		if(dir == '+' && king_name == 'k') {
			theBoard[0][4] = theBoard[0][6]; theBoard[0][6] = NULL; theBoard[0][7] = theBoard[0][5]; 
			theBoard[0][5] = NULL;  theBoard[0][4]->setr(0); theBoard[0][4]->setc(4); theBoard[0][4]->setRange();
			theBoard[0][4]->setMove(false); theBoard[0][7]->setr(0); theBoard[0][7]->setc(7); theBoard[0][7]->setRange(); 
			theBoard[0][7]->setMove(false); updatePiece(0,4);updatePiece(0,7); updateGrid(0,7); updateGrid(0,4); td->notify(0,6); 
			td->notify(0, 5); td->notify(0, 4, 'k'); td->notify(0, 7, 'r'); 
			if(graphmode && !Istesting) {
				gd->notify(0,6); 
				gd->notify(0, 5); 
				gd->notify(0, 4, 'k'); 
				gd->notify(0, 7, 'r');
			}
		}
		if(dir == '-' && king_name == 'K') {
			theBoard[7][4] = theBoard[7][2]; theBoard[7][2] = NULL;  theBoard[7][0] = theBoard[7][3]; 
			theBoard[7][3] = NULL;  theBoard[7][4]->setr(7); theBoard[7][4]->setc(4); theBoard[7][4]->setRange();
			theBoard[7][4]->setMove(false); theBoard[7][0]->setr(7); theBoard[7][0]->setc(0); theBoard[7][0]->setRange(); 
			theBoard[7][0]->setMove(false); updatePiece(7,4); updatePiece(7,0); updateGrid(7,0); updateGrid(7,4); td->notify(7 ,2); 
			td->notify(7, 3); td->notify(7, 4, 'K'); td->notify(7, 0, 'R'); 
			if(graphmode && !Istesting) {
				gd->notify(7 ,2); 
				gd->notify(7, 3); 
				gd->notify(7, 4, 'K'); 
				gd->notify(7, 0, 'R');
			}
		}
		if(dir == '+' && king_name == 'K') {
			theBoard[7][4] = theBoard[7][6]; theBoard[7][6] = NULL;  theBoard[7][7] = theBoard[7][5]; 
			theBoard[7][5] = NULL;  theBoard[7][4]->setr(7); theBoard[7][4]->setc(4); theBoard[7][4]->setRange();
			theBoard[7][4]->setMove(false); theBoard[7][7]->setr(7); theBoard[7][7]->setc(7); theBoard[7][7]->setRange(); 
			theBoard[7][7]->setMove(false); updatePiece(7,4);updatePiece(7,7); updateGrid(7,7); updateGrid(7,4); td->notify(7, 6); td->notify(7, 5); 
			td->notify(7, 4, 'K'); td->notify(7, 7, 'R'); 
			if(graphmode && !Istesting) {
				gd->notify(7, 6); 
				gd->notify(7, 5); 
				gd->notify(7, 4, 'K'); 
				gd->notify(7, 7, 'R');
			}
		}
	}
	else {
		int r, c, newr, newc;
		newr = move.first[2];
		newc = move.first[3];
		r = move.first[0];
		c = move.first[1];
		char name = move.second[0];
		char enpass_name = move.second[3];
		char promote = move.second[4];
		char prename = move.second[5];
		bool status1 = (move.second[1] == 0) ? false : true;
		bool status2 = (move.second[2] == 0) ? false : true;
		if(promote == 'o') {
			remove(newr, newc);
			add(newr, newc, prename, true);
		}	
		removeRange(newr, newc);
		theBoard[r][c] = theBoard[newr][newc];
		theBoard[newr][newc] = NULL;
		td->notify(newr, newc);
		if(graphmode && !Istesting) gd->notify(newr, newc);
		theBoard[r][c]->setr(r);
		theBoard[r][c]->setc(c);
		theBoard[r][c]->setRange();
		if(enpass_name == 'e') {
			add(r, newc, name, status2);
			enpassant = static_cast<Pawn*>(theBoard[r][newc]);
			updateEnpassant = true;
			td->notify(r, newc, name);
			if(graphmode && !Istesting)gd->notify(r, newc, name);
		}
		else if(name != '_') {
			add(newr, newc, name, status2);
			td->notify(newr, newc, name);
			if(graphmode && !Istesting)gd->notify(newr, newc, name);
		}
		updatePiece(newr, newc);
		updatePiece(r, c);
		updateGrid(r, c);
		updateGrid(newr, newc);
		theBoard[r][c]->setMove(status1);
		td->notify(r, c, theBoard[r][c]->getName());
		if(graphmode && !Istesting)gd->notify(r, c, theBoard[r][c]->getName());
		td->notify(r, c, theBoard[r][c]->getName());
		if(graphmode && !Istesting)gd->notify(r, c, theBoard[r][c]->getName());
	}
	stack.pop_back();
}



void Board::move(int oldr, int oldc, int newr, int newc) {
	std::string capture_name = "_";//this is the default name for captured piece, if no piece is captured the capture_name is "_"
	std::string enpass_name = "_";//this is a mark for enpassant, if off then it is "_" else it is "e"
	std::string promote = "_"; //this is a mark for promotion if promotion has been made
	bool status1 = theBoard[oldr][oldc]->getStatus(); //this records the status of the moving pieces
	bool status2; //this records the status of the captured pieces if any
	if(theBoard[newr][newc] != NULL) {
		status2 = theBoard[newr][newc]->getStatus();
		capture_name = theBoard[newr][newc]->getName();
	}
	else status2 = false;
	char name = theBoard[oldr][oldc]->getName();
	if((name == 'p' || name == 'P') && abs(newr - oldr) == 2) {
		enpassant = static_cast<Pawn* >(theBoard[oldr][oldc]);
		updateEnpassant = true;
	}
	if((name == 'p'|| name == 'P') && (theBoard[newr][newc] == NULL) && (abs(newc - oldc) == 1)) {
		capture_name = theBoard[oldr][newc]->getName(); // this is the unique name for the pawn captured by enpassant
		enpass_name = "e";
		status2 = theBoard[oldr][newc]->getStatus();
		remove(oldr, newc);
	}
	if((name == 'p' && newr == 7) || (name == 'P' || newr == 0)) promote = "o";
	std::string s1, s2;
	s1 = (status1) ? "1" : "0";
	s2 = (status2) ? "1" : "0";
	std::vector <int> moves;
	moves.push_back(oldr);
	moves.push_back(oldc);	
	moves.push_back(newr);
	moves.push_back(newc);
	std::pair <std::vector <int>, std::string> a_move;
	a_move.first = moves;
	a_move.second = capture_name + s1 + s2 + enpass_name + promote + theBoard[oldr][oldc]->getName();
	stack.push_back(a_move);	
	removeRange(oldr, oldc);
	remove(newr, newc);
	theBoard[newr][newc] = theBoard[oldr][oldc];
	theBoard[oldr][oldc] = NULL;
	theBoard[newr][newc]->setr(newr);
	theBoard[newr][newc]->setc(newc);
	theBoard[newr][newc]->setRange();
	updatePiece(newr, newc);
	updateGrid(oldr, oldc);
	updateGrid(newr, newc);
	theBoard[newr][newc]->setMove(true);
	if((name != 'p' && name != 'P') || abs(newr - oldr) != 2) updateEnpassant = false;
	td->notify(oldr, oldc);
	if(graphmode && !Istesting) gd->notify(oldr, oldc);
	td->notify(newr, newc, name);
	if(graphmode && !Istesting) gd->notify(newr, newc, name);
}

void Board::setPlaying(bool play) { playing = play; }


void Board::play(int graph, std::string file) {
	if(graph == 1) {
		graphmode = true;
		std::cout << "graph mode " << std::endl;
		delete gd;
		gd = new GraphicDisplay();
	}
	delete td;
	td = new TextDisplay();
	if(file != "") {
		std::string line;
		std::ifstream myfile(file.c_str());
		int row = 0;
		while (std::getline(myfile, line)) {
			std::stringstream ss(line);
			char c;
			int col = 0;
			while(ss >> c) {
				if(c == 'W') turn = 0;
				else if( c == 'B') turn = 1;
				else if(c == '_') col ++;
				else if('A' <= c && c <= 'z') {
					add(row, col, c, false);
					col ++;
				}
			}
			row ++;
		}
		file = "";
		td->print();
	}
	std::string command;
	while(std::cin >> command) {
		if(command == "setup" && file == "") {
			clearGame();
			delete td;
			td = new TextDisplay();
			if(graph == 1) {
				graphmode = true;
				std::cout << "graph mode " << std::endl;
				delete gd;
				gd = new GraphicDisplay();
			}
			td->print();
			std::string opt;
			while(std::cin >> opt) {
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
					if(piece == 'r' || piece == 'R' ||piece == 'B' ||piece == 'b' ||piece == 'N' ||piece == 'n' ||piece == 'Q' ||piece == 'q' ||piece == 'K' ||piece == 'k' ||piece == 'P' ||piece == 'p') {
						add(convert(pos)[0], convert(pos)[1], piece, false);
						td->print();
					}
					else std::cout << "not valid piece" << std::endl;
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
						add(1, i, 'p', false);
						add(6, i, 'P', false);
					}
					add(0, 0, 'r', false);
					add(0, 7, 'r', false);
					add(0, 1, 'n', false);
					add(0, 6, 'n', false);
					add(0, 2, 'b', false);
					add(0, 5, 'b', false);
					add(0, 3, 'q', false);
					add(0, 4, 'k', false);
					add(7, 0, 'R', false);
					add(7, 7, 'R', false);
					add(7, 1, 'N', false);
					add(7, 6, 'N', false);
					add(7, 2, 'B', false);
					add(7, 5, 'B', false);
					add(7, 3, 'Q', false);
					add(7, 4, 'K', false);
					td->print();
				}
				else if(opt == "grid") {
					int r = 0, c = 0;
					std::cin >> r >> c;
					std::cout << "the pieces in grid " << r << " " << c << " are(is)" << std::endl;
					int size = attackBoard[r][c].size();
					for(int i = 0; i < size; i++) {
						std::cout << attackBoard[r][c][i]->getName() << std::endl;
					}
					if(theBoard[r][c] == NULL) std::cout << "nothing is on this grid" << std::endl;
					else std::cout << theBoard[r][c]->getName() << " is on this grid" << std::endl;
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
			else if(player1 == "computer1") p1 = new Computer1(this, 'A');
			else if(player1 == "computer2") p1 = new Computer2(this, 'A');
			else if(player1 == "computer3") p1 = new Computer3(this, 'A');
			else if(player1 == "computer4") p1 = new Computer4(this, 'A');
			if(player2 == "human") p2 = new Human(this, 'z');
			else if(player2 == "computer1") p2 = new Computer1(this, 'z');
			else if(player2 == "computer2") p2 = new Computer2(this, 'z');
			else if(player2 == "computer3") p2 = new Computer3(this, 'z');
			else if(player2 == "computer4") p2 = new Computer4(this, 'z');
			td->print();
			std::cout << "the battle begins!" << std::endl;
			while(true) {
				if(!updateEnpassant) {
					enpassant = NULL;
				}
				if(turn == 0 && playing) {
					Istesting = true;
					if(check('K')) {
						std::cout << "White is in check!" << std::endl;
						if(checkMate('K')) {
							std::cout << "Checkmate! Black wins!" << std::endl;
							playing = false;
							p2Score ++;
							break;
						}
					}
					if(stalemate('A')) {
						p1Score += 0.5;
						p2Score += 0.5;
						std::cout << "Stalemate!" << std::endl;
						break;
					}
					std::cout << "white's turn to move" << std::endl;
					p1->makeMove();
					td->print();
				}
				else if(turn == 1 && playing) {
					Istesting = true;
					if(check('k')) {
						std::cout << "Black is in check!" << std::endl;
						if(checkMate('k')) {
							std::cout << "Checkmate! White wins!" << std::endl;
							playing = false;
							p1Score ++;
							break;
						}
					}
					if(stalemate('z')) {
						p1Score += 0.5;
						p2Score += 0.5;
						std::cout << "Stalemate!" << std::endl;
						break;
					}
					std::cout << "black's turn to move" << std::endl;
					p2->makeMove();
					td->print();
				}
				turn = !turn;
				if(!playing) break;
			}
			std::cout << "White: " << p1Score << std::endl;
			std::cout << "Black: " << p2Score << std::endl;
		}
	}
	std::cout << "Final Score: " << std::endl;
	std::cout << "White: " << p1Score << std::endl;
	std::cout << "Black: " << p2Score << std::endl;
}


