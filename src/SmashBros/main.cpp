
#include "Game.h"

int main(int argc, char *argv[])
{
	SmashBros::Game* game = new SmashBros::Game();
	int returnVal = game->run();
	delete game;
	system("PAUSE");
	return returnVal;
}
