
#include <GameLibraryImport.hpp>

#pragma once

namespace SmashBros
{
	namespace Menu
	{
		class SmashBrosMenuScreen : public GameLibrary::MenuScreen
		{
		public:
			SmashBrosMenuScreen();
			virtual ~SmashBrosMenuScreen();
			
			virtual void onItemHover(unsigned int index);
			virtual void onItemHoverFinish(unsigned int index);
			virtual void onItemPress(unsigned int index);
			virtual void onItemPressCancel(unsigned int index);
			virtual void onItemRelease(unsigned int index);
			
		protected:
			virtual void updateItems(ApplicationData appData);
			virtual void drawItem(ApplicationData appData, Graphics graphics, unsigned int itemIndex) const;
			
		private:
			float hoverPulseScale;
			bool hoverPulseGrowing;
			bool hoverPressed;
		};
	}
}
