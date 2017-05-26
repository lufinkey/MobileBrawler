
#pragma once

#include "../MenuData/MenuData.hpp"
#include "../Elements/MenuButton.hpp"

namespace SmashBros
{
	namespace Menu
	{
		class BaseMenuScreen : public fgl::Screen
		{
		public:
			typedef enum
			{
				HEADERBAR_SMALL,
				HEADERBAR_FULL
			} HeaderbarMode;
			
			explicit BaseMenuScreen(MenuData* menuData);
			virtual ~BaseMenuScreen();

			void addScreen(const fgl::String& name, BaseMenuScreen* screen);
			void removeScreen(const fgl::String& name);
			BaseMenuScreen* getScreen(const fgl::String& name) const;
			const fgl::BasicDictionary<fgl::String, BaseMenuScreen*>& getScreens() const;
			void goToScreen(const fgl::String& name, const fgl::Transition* transition=fgl::ScreenManager::defaultPushTransition, unsigned long long duration=fgl::Transition::defaultDuration);
			void goBack();

			virtual fgl::Dictionary getState() const;
			virtual void setState(const fgl::Dictionary& state);
			
			fgl::ImageElement* getBackgroundElement() const;
			fgl::ImageElement* getHeaderbarElement() const;
			MenuButton* getBackButton() const;
			
			void setHeaderbarMode(const HeaderbarMode& mode);
			
		protected:
			MenuData* getMenuData() const;
			
		private:
			MenuData* menuData;
			
			fgl::TextureImage* img_headerbar_small;
			fgl::TextureImage* img_headerbar_full;
			
			fgl::ImageElement* backgroundElement;
			fgl::ImageElement* headerbarElement;
			MenuButton* backButton;

			fgl::BasicDictionary<fgl::String, BaseMenuScreen*> screens;
		};
	}
}
