
#include "Game.h"

using namespace fgl;

int main(int argc, char *argv[])
{
	SmashBros::Game* game = new SmashBros::Game();
	int returnVal = game->run(Window::getDefaultSettings(), Application::ORIENTATION_LANDSCAPE);
	delete game;
	return returnVal;
}
