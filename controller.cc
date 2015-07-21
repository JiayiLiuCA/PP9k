#include "controller.h"


Controller::~Controller() {
	game = NULL;
}


char Controller::getTeam() {
	return team;
}
