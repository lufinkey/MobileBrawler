
#include "Game.h"

using namespace GameLibrary;

int main(int argc, char *argv[])
{
	DateTime datetime;
	Any any(datetime);
	Console::writeLine(any.toString());
	SmashBros::Game* game = new SmashBros::Game();
	int returnVal = game->run(Window::getDefaultSettings(), Application::ORIENTATION_LANDSCAPE);
	delete game;
	return returnVal;
}
