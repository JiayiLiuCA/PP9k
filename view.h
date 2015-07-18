#ifndef __VIEW_H__
#define __VIEW_H__

class View {
	public:
		virtual notify(char opt, int r, int c, char pieces); //this notifies the display of the changes of the board
		virtual notify(char opt, int r, int c);
		virtual print() = 0;
		virtual ~View() = 0;
};
#endif
