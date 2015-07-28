#include "board.h"
#include <iostream>

int main(int argc, char* argv[]) {
	std::string file = "";
	std::string graphic = "-graphic";
	int graph = 0;
	for(int i = 1; i < argc; i ++) {
		std::string tmp(argv[i]);
		if(tmp == graphic) 	graph = 1;
		else {
			std::cout << "capturing a file" << std::endl;
			file = argv[i];
		}
	}
	Board *b = Board::getInstance();
	b->play(graph, file);
}
