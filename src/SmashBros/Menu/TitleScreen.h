
#pragma once

#include "BaseMenuScreen.h"

namespace SmashBros
{
	namespace Menu
	{
		class TitleScreen : public SmashBros::Menu::BaseMenuScreen
		{
		private:
			//
		public:
			TitleScreen(AssetManager*assetManager);
			virtual ~TitleScreen();
			
			virtual void onItemSelect(unsigned int index);
		};
	}
}
