
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
			explicit MainMenu(MenuData* menuData);
			virtual ~MainMenu();
			
		private:
			MenuButton* groupButton;
			MenuButton* soloButton;

			fgl::FadeColorTransition* backTransition;
		};
	}
}
