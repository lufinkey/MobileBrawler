
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
			explicit TitleScreen(const SmashData&smashData);
			virtual ~TitleScreen();

		private:
			FadeColorTransition* transition;
			ImageElement* logo;
			ButtonElement* tapRegion;
		};
	}
}
