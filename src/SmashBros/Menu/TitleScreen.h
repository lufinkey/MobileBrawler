
#pragma once

#include "Base/BaseMenuScreen.h"
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
			TitleScreen(const SmashData&smashData);
			virtual ~TitleScreen();
			
			virtual void onItemSelect(unsigned int index);
		};
	}
}
