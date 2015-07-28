#include "graphicdisplay.h"
#include <string>



GraphicDisplay::GraphicDisplay() {
	std::cout << "in constructor" << std::endl;
	display = new Xwindow();
	for(int i = 0; i < 8; i ++) {
		for(int j = 0; j < 8; j ++) {
			if((i + j) % 2 == 0) display->fillRectangle(i*50, j*50, 50, 50, 0);
			else display->fillRectangle(i*50, j*50, 50, 50, 1);
		}
	}
	for(int i = 0; i < 8; i ++) {
		display->drawString(25 + i * 50, 425, convert("a", i) , 1);
		display->drawString(425, 25 + i * 50, convert("8", (0 - i)), 1);
	}
}

void GraphicDisplay::notify(int r, int c, char ch) {
	std::string name = "";
	name += ch;
	if(ch == '-' && ((r + c) % 2 == 0)) display->fillRectangle(c * 50, r * 50, 50, 50, 0);
	else if (ch == '-' && ((r + c) % 2 == 1)) display->fillRectangle(c * 50, r * 50, 50, 50, 1);
	else if((r + c) % 2 == 0) display->drawBigString(20 + c * 50, 30 + r * 50, name, 1);
	else {
		std::cout << "drawing" << std::endl;
		display->drawBigString(20 + c * 50, 30 + r * 50, name, 0);
	}
}

void GraphicDisplay::print() {}


std::string convert(std::string s, int i) {
	s[0] = s[0] + ('b' - 'a') * i;
	return s;
}


