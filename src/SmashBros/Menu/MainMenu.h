
#pragma once

#include "Base/BaseMenuScreen.h"
#include "GroupMenu/GroupMenu.h"
#include "SoloMenu/SoloMenu.h"

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
