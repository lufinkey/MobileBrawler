
#pragma once

#include "../MenuData/SmashData.hpp"
#include "../Elements/MenuButton.hpp"

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
			
			explicit BaseMenuScreen(const SmashData& smashData);
			virtual ~BaseMenuScreen();
			
			virtual void onWillDisappear(const Transition* transition) override;
			
			virtual void onItemHover(size_t index) override;
			virtual void onItemHoverFinish(size_t index) override;
			virtual void onItemPress(size_t index) override;
			virtual void onItemPressCancel(size_t index) override;
			virtual void onItemRelease(size_t index) override;
			virtual void onItemSelect(size_t index) override;

			void addScreen(const fgl::String& name, BaseMenuScreen* screen);
			void removeScreen(const fgl::String& name);
			BaseMenuScreen* getScreen(const fgl::String& name) const;
			const fgl::BasicDictionary<fgl::String, BaseMenuScreen*>& getScreens() const;
			void goToScreen(const fgl::String& name, const fgl::Transition* transition=fgl::ScreenManager::defaultPushTransition);
			void goBack();

			virtual fgl::Dictionary getState() const;
			virtual void setState(const fgl::Dictionary& state);
			
			ImageElement* getBackgroundElement() const;
			ImageElement* getHeaderbarElement() const;
			MenuButton* getBackButton() const;
			
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
			ImageElement* headerbarElement;
			MenuButton* backButton;

			fgl::BasicDictionary<fgl::String, BaseMenuScreen*> screens;
		};
	}
}
