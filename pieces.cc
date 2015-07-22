#include "pieces.h"

Pieces::~Pieces() {
	r = -1;
	c = -1;
	Move = false;
}

bool Pieces::getStatus() {
	return Move;
}

void Pieces::setMove(bool move) {
	Move = move;
}

char Pieces::getName() { return name; }

int Pieces::getr() { return r; }

int Pieces::getc() { return c; }

void Pieces::setr(int row) { r = row; }

void Pieces::setc(int col) { c = col; }
