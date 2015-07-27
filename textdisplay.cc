#include <iostream>
#include "textdisplay.h"

TextDisplay::TextDisplay(): View() {
	std::vector <char> tmp (10, '*');
	display.assign(10,tmp);
	for (int i = 0; i < 10; i++) {
		if (i == 9) {
			for (int x = 0; x < 10; x++) {
				if (x < 2) {
					display[i][x] = ' ';
				}
				else {
					display[i][x] = 'a' - 2 + x;
				}
			}
		}
		else if (i == 8) {
			for (int XD = 0; XD < 10; XD++) {
				display[i][XD] = ' ';
			}
		}
		else {
			for (int y = 0; y < 10; y++) {
				if (y == 0) {
					display[i][y] = '8' - i;
				}
				else if (y == 1) {
					display[i][y] = ' ';
				}
				else if ((i + y)%2 == 0) {
					display[i][y] = ' ';
				}
				else {
					display[i][y] = '-';
				}
			}
		}
	}
}

void TextDisplay::notify(int r, int c, char piece) {
	if((piece == '-') && ((r + c) % 2 == 0)) piece = ' ';
	display[r][c + 2] = piece;
}

void TextDisplay::print() {
	for (std::vector<std::vector <char> >::iterator i = display.begin();
			i != display.end(); i++) {
		for (std::vector <char>::iterator j = i->begin();
				j != i->end(); j++) {
			std::cout << *j;
			if (j == i->end() - 1) {
				std::cout << std::endl;
			}
		}
	}
}
