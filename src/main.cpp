
#include "Game.h"

int main(int argc, char *argv[])
{
	Game* game = new Game();
	int returnVal = game->run();
	delete game;
	return returnVal;
}
