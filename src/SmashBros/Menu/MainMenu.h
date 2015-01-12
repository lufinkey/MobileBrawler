
#include "SmashBrosMenuScreen.h"

#pragma once

namespace SmashBros
{
	namespace Menu
	{
		class MainMenu : public SmashBrosMenuScreen
		{
		public:
			MainMenu(AssetManager*assetManager);
			virtual ~MainMenu();
			
			virtual void onItemSelect(unsigned int index);
		};
	}
}
