#ifndef __TEXTDISPLAY_H__
#define __TEXTDISPLAY_H__

#include "view.h"

class TextDisplay: public View {
		char **theDisplay; //the text visualization of the board
	public:
		notify(char opt, int r, int c);
		print();
};
#endif
