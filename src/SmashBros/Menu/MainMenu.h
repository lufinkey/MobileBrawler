
#pragma once

#include "BaseMenuScreen.h"

namespace SmashBros
{
	namespace Menu
	{
		class MainMenu : public SmashBros::Menu::BaseMenuScreen
		{
		public:
			MainMenu(AssetManager*assetManager);
			virtual ~MainMenu();
			
			virtual void onItemSelect(unsigned int index);
		};
	}
}
