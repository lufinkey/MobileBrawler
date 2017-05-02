
#include "MenuLoadScreen.hpp"

namespace SmashBros
{
	MenuLoadScreen::MenuLoadScreen(fgl::AssetManager* assetManager)
	{
		getElement()->setBackgroundColor(fgl::Color::BLACK);
	}

	MenuLoadScreen::~MenuLoadScreen()
	{
		//
	}

	void MenuLoadScreen::onUpdate(const fgl::ApplicationData& appData)
	{
		Screen::onUpdate(appData);
	}
}
