
#pragma once

#include <GameLibraryImport.hpp>

namespace SmashBros
{
	namespace Menu
	{
		class BaseMenuScreen : public GameLibrary::MenuScreen
		{
		public:
			BaseMenuScreen(AssetManager*assetManager);
			virtual ~BaseMenuScreen();
			
			virtual void onWillAppear(const Transition*transition);
			
			virtual void onItemHover(unsigned int index);
			virtual void onItemHoverFinish(unsigned int index);
			virtual void onItemPress(unsigned int index);
			virtual void onItemPressCancel(unsigned int index);
			virtual void onItemRelease(unsigned int index);
			virtual void onItemSelect(unsigned int index);
			
			ImageElement* getBackgroundElement() const;
			SpriteActor* getBackButton() const;
			ImageElement* getHeaderbarElement() const;
			
			void enableHoverPulse(bool);
			
		protected:
			virtual void updateItems(ApplicationData appData);
			virtual void drawItem(ApplicationData appData, Graphics graphics, unsigned int itemIndex) const;
			
		private:
			float hoverPulseScale;
			bool hoverPulseGrowing;
			bool hoverPulseEnabled;
			
			bool hoverPressed;
			ImageElement* backgroundElement;
			SpriteActor* backButton;
			ImageElement* headerbarElement;
		};
	}
}
