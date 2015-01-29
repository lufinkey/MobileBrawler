
#pragma once

#include "../MenuData/SmashData.h"

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
			
			virtual void onUpdate(ApplicationData appData) override;
			
			virtual void onItemHover(unsigned int index) override;
			virtual void onItemHoverFinish(unsigned int index) override;
			virtual void onItemPress(unsigned int index) override;
			virtual void onItemPressCancel(unsigned int index) override;
			virtual void onItemRelease(unsigned int index) override;
			virtual void onItemSelect(unsigned int index) override;
			
			ImageElement* getBackgroundElement() const;
			SpriteActor* getBackButton() const;
			ImageElement* getHeaderbarElement() const;
			
			void setHeaderbarMode(const HeaderbarMode&mode);
			
			void enableHoverPulse(bool);
			
		protected:
			virtual void drawItem(ApplicationData appData, Graphics graphics, Actor*item) const override;
			
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
