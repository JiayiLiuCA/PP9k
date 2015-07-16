#ifndef __VIEW_H__
#define __VIEW_H__

class View {
	public:
		virtual notify(char opt, int r, int c); //this notifies the display of the changes of the board
		virtual print() = 0;
		virtual ~View() = 0;
};
#endif
