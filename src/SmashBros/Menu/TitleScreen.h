
#pragma once

#include "BaseMenuScreen.h"

namespace SmashBros
{
	namespace Menu
	{
		class TitleScreen : public SmashBros::Menu::BaseMenuScreen
		{
		public:
			TitleScreen(AssetManager*assetManager);
			virtual ~TitleScreen();
			
			virtual void onItemSelect(unsigned int index);
		};
	}
}
