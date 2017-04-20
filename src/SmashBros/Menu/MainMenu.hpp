
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
		private:
			Actor* groupButton;
			Actor* soloButton;
			
			FadeColorTransition* backTransition;
			
			GroupMenu* groupMenu;
			SoloMenu* soloMenu;
			
		public:
			explicit MainMenu(const SmashData&smashData);
			virtual ~MainMenu();
			
			virtual void onItemSelect(size_t index) override;
		};
	}
}
