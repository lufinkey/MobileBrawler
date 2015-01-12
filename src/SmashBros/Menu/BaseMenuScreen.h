
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
			
			ImageElement* getBackgroundElement() const;
			
		protected:
			virtual void updateItems(ApplicationData appData);
			virtual void drawItem(ApplicationData appData, Graphics graphics, unsigned int itemIndex) const;
			
		private:
			float hoverPulseScale;
			bool hoverPulseGrowing;
			bool hoverPressed;
			ImageElement* backgroundElement;
		};
	}
}
