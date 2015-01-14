
#pragma once

#include "BaseMenuScreen.h"
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
			MainMenu(AssetManager*assetManager);
			virtual ~MainMenu();
			
			virtual void onItemSelect(unsigned int index);
		};
	}
}
