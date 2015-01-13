
#pragma once

#include "MainMenu.h"

namespace SmashBros
{
	namespace Menu
	{
		class TitleScreen : public SmashBros::Menu::BaseMenuScreen
		{
		private:
			FadeColorTransition* transition;
			MainMenu* mainMenu;
			ImageElement* logo;
			WireframeActor* tapRegion;
			
		protected:
			virtual void updateItems(ApplicationData appData);
			
		public:
			TitleScreen(AssetManager*assetManager);
			virtual ~TitleScreen();
			
			virtual void onWillAppear(const Transition*transition);
			
			virtual void onItemSelect(unsigned int index);
		};
	}
}
