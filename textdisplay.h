#include <vector>
#ifndef __TEXTDISPLAY_H__
#define __TEXTDISPLAY_H__

#include "view.h"

class TextDisplay: public View {
	std::vector <std::vector <char> > display; //the text visualization of the board
	public:
		TextDisplay();
		void notify(int r, int c, char pieces = '-');
		void print();
};
#endif
