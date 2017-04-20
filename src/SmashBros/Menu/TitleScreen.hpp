
#pragma once

#include "Base/BaseMenuScreen.hpp"
#include "MainMenu.hpp"

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
			
		public:
			explicit TitleScreen(const SmashData&smashData);
			virtual ~TitleScreen();

			virtual void onSizeChange(const Vector2d& oldSize, const Vector2d& newSize) override;
			virtual void onItemSelect(size_t index) override;
			
		protected:
			virtual void onUpdate(const ApplicationData& appData) override;
		};
	}
}
