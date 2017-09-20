
#include "Game.hpp"

using namespace fgl;

int main(int argc, char *argv[])
{
	auto game = new SmashBros::Game();
	int returnVal = game->run(Window::getDefaultSettings(), Application::ORIENTATION_LANDSCAPE);
	delete game;
	return returnVal;
}
