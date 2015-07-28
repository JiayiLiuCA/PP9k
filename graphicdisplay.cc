#include "graphicdisplay.h"
#include <string>



GraphicDisplay::GraphicDisplay() {
	display = new Xwindow();
	display->fillRectangle(0, 0, 500, 500, 9);
	for(int i = 0; i < 8; i ++) {
		for(int j = 0; j < 8; j ++) {
			if((i + j) % 2 == 0) display->fillRectangle(i*50, j*50, 50, 50, 0);
			else display->fillRectangle(i*50, j*50, 50, 50, 1);
		}
	}
	for(int i = 0; i < 8; i ++) {
		display->drawBigString(30 + i * 50, 425, convert("a", i) , 5);
		display->drawBigString(430, 25 + i * 50, convert("8", (0 - i)), 5);
	}
}

void GraphicDisplay::notify(int r, int c, char ch) {
	std::string name = "";
	name += ch;
	if(ch == '-' && ((r + c) % 2 == 0)) display->fillRectangle(c * 50, r * 50, 50, 50, 0);
	else if (ch == '-' && ((r + c) % 2 == 1)) display->fillRectangle(c * 50, r * 50, 50, 50, 1);
	else if((r + c) % 2 == 0) display->drawBigString(20 + c * 50, 30 + r * 50, name, 1);
	else {
		display->drawBigString(20 + c * 50, 30 + r * 50, name, 0);
	}
}

void GraphicDisplay::print() {}


std::string convert(std::string s, int i) {
	s[0] = s[0] + ('b' - 'a') * i;
	return s;
}


