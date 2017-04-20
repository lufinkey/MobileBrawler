
#pragma once

#include "../MenuData/SmashData.hpp"

namespace SmashBros
{
	namespace Menu
	{
		class BaseMenuScreen : public fgl::MenuScreen
		{
		public:
			typedef enum
			{
				HEADERBAR_SMALL,
				HEADERBAR_FULL
			} HeaderbarMode;
			
			explicit BaseMenuScreen(const SmashData&smashData);
			virtual ~BaseMenuScreen();
			
			virtual void onWillDisappear(const Transition*transition) override;
			
			virtual void onItemHover(size_t index) override;
			virtual void onItemHoverFinish(size_t index) override;
			virtual void onItemPress(size_t index) override;
			virtual void onItemPressCancel(size_t index) override;
			virtual void onItemRelease(size_t index) override;
			virtual void onItemSelect(size_t index) override;
			
			ImageElement* getBackgroundElement() const;
			SpriteActor* getBackButton() const;
			ImageElement* getHeaderbarElement() const;
			
			void setHeaderbarMode(const HeaderbarMode&mode);
			
			void enableHoverPulse(bool);
			
		protected:
			virtual void onUpdate(const ApplicationData& appData) override;
			
			virtual void drawItem(ApplicationData appData, Graphics graphics, Actor*item) const override;
			
		private:
			double hoverPulseScale;
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
