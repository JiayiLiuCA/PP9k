#include "view.h"
#include "window.h"


class GraphicDisplay:public View {
	Xwindow *display;
	public:
		GraphicDisplay();
		void notify(int r, int c, char pieces = '-');
		void print();
};


std::string convert(std::string s, int i);
