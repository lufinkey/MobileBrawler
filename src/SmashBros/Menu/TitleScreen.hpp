
#pragma once

#include "Base/BaseMenuScreen.hpp"
#include "MainMenu.hpp"

namespace SmashBros
{
	namespace Menu
	{
		class TitleScreen : public SmashBros::Menu::BaseMenuScreen
		{
		public:
			explicit TitleScreen(MenuData* menuData);
			virtual ~TitleScreen();

		private:
			fgl::FadeColorTransition* transition;
			fgl::ImageElement* logo;
			fgl::ButtonElement* tapRegion;
		};
	}
}
