
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
			
			TextInputElement* textInput;
			
		public:
			explicit TitleScreen(const SmashData&smashData);
			virtual ~TitleScreen();

			virtual void onFrameChange() override;
			virtual void onItemSelect(size_t index) override;
			
		protected:
			virtual void onUpdate(ApplicationData appData) override;
		};
	}
}
