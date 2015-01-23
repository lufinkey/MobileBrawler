
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
            FadeZoomTransition* fzTransition;
            
            // Can't find a way to access the pop directions so
            // I'm assuming it will crash if accessed without it
            //PopoverTransition* popTransition;
			
			//GroupMenu* groupMenu;
			SoloMenu* soloMenu;
			
		public:
			MainMenu(const SmashData&smashData);
			virtual ~MainMenu();
			
			virtual void onItemSelect(unsigned int index);
		};
	}
}
