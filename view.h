#ifndef __VIEW_H__
#define __VIEW_H__

class View {
	public:
		void virtual notify(int r, int c, char pieces = '-') = 0; //this notifies the display of the changes of the board
		void virtual print() = 0;
		virtual ~View() = 0;
};
#endif
