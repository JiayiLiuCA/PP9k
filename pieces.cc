#include "pieces.h"

Pieces::~Pieces() {}

bool Pieces::getStatus() {
	return doubleMove;
}

void Pieces::setMove(bool move) {
	doubleMove = move;
}

char Pieces::getName() { return name; }
