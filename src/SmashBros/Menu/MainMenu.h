
#pragma once

#include "Base/BaseMenuScreen.h"
#include "GroupMenu.h"
#include "SoloMenu.h"

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
			MainMenu(const SmashData&smashData);
			virtual ~MainMenu();
			
			virtual void onItemSelect(unsigned int index);
		};
	}
}
