
#pragma once

#include "../../SmashData.h"

namespace SmashBros
{
	namespace Menu
	{
		class BaseMenuScreen : public GameLibrary::MenuScreen
		{
		public:
			typedef enum
			{
				HEADERBAR_SMALL,
				HEADERBAR_FULL
			} HeaderbarMode;
			
			BaseMenuScreen(const SmashData&smashData);
			virtual ~BaseMenuScreen();
			
			virtual void onItemHover(unsigned int index);
			virtual void onItemHoverFinish(unsigned int index);
			virtual void onItemPress(unsigned int index);
			virtual void onItemPressCancel(unsigned int index);
			virtual void onItemRelease(unsigned int index);
			virtual void onItemSelect(unsigned int index);
			
			ImageElement* getBackgroundElement() const;
			SpriteActor* getBackButton() const;
			ImageElement* getHeaderbarElement() const;
			
			void setHeaderbarMode(const HeaderbarMode&mode);
			
			void enableHoverPulse(bool);
			
		protected:
			virtual void updateItems(ApplicationData appData);
			virtual void drawItem(ApplicationData appData, Graphics graphics, unsigned int itemIndex) const;
			
		private:
			float hoverPulseScale;
			bool hoverPulseGrowing;
			bool hoverPulseEnabled;
			
			TextureImage* img_headerbar_small;
			TextureImage* img_headerbar_full;
			
			bool hoverPressed;
			ImageElement* backgroundElement;
			SpriteActor* backButton;
			ImageElement* headerbarElement;
		};
	}
}
