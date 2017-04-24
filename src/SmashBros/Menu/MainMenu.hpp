
#pragma once

#include "Base/BaseMenuScreen.hpp"
#include "GroupMenu/GroupMenu.hpp"
#include "SoloMenu/SoloMenu.hpp"

namespace SmashBros
{
	namespace Menu
	{
		class MainMenu : public SmashBros::Menu::BaseMenuScreen
		{
		public:
			explicit MainMenu(const SmashData&smashData);
			virtual ~MainMenu();
			
		private:
			MenuButton* groupButton;
			MenuButton* soloButton;

			FadeColorTransition* backTransition;

			GroupMenu* groupMenu;
			SoloMenu* soloMenu;
		};
	}
}
