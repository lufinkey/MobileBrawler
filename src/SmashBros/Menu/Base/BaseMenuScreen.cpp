
#include "BaseMenuScreen.hpp"

namespace SmashBros
{
	namespace Menu
	{
#define PULSE_UPPERBOUND 1.1
#define PULSE_LOWERBOUND 0.98
#define PULSE_SPEED 0.3
#define PULSE_HOVERCOLOR fgl::Color::LIGHTBLUE
#define PULSE_PRESSCOLOR fgl::Color::BLUE
		
		BaseMenuScreen::BaseMenuScreen(MenuData* menuData)
			: menuData(menuData)
		{
			auto assetManager = menuData->getAssetManager();
			
			img_headerbar_small = assetManager->loadTexture("elements/headerbar_small.png");
			img_headerbar_full = assetManager->loadTexture("elements/headerbar_full.png");
			
			auto element = getElement();
			
			backgroundElement = new fgl::ImageElement(assetManager->loadTexture("backgrounds/main.png"), fgl::ImageElement::DISPLAY_FILL);
			backgroundElement->setLayoutRule(fgl::LAYOUTRULE_LEFT,   0, fgl::LAYOUTVALUE_RATIO);
			backgroundElement->setLayoutRule(fgl::LAYOUTRULE_TOP,    0, fgl::LAYOUTVALUE_RATIO);
			backgroundElement->setLayoutRule(fgl::LAYOUTRULE_RIGHT,  0, fgl::LAYOUTVALUE_RATIO);
			backgroundElement->setLayoutRule(fgl::LAYOUTRULE_BOTTOM, 0, fgl::LAYOUTVALUE_RATIO);
			element->addChildElement(backgroundElement);
			
			headerbarElement = new fgl::ImageElement(img_headerbar_full, fgl::ImageElement::DISPLAY_FILL);
			headerbarElement->setLayoutRule(fgl::LAYOUTRULE_LEFT,   0.0,	fgl::LAYOUTVALUE_RATIO);
			headerbarElement->setLayoutRule(fgl::LAYOUTRULE_TOP,    0.0,	fgl::LAYOUTVALUE_RATIO);
			headerbarElement->setLayoutRule(fgl::LAYOUTRULE_RIGHT,  0.0,	fgl::LAYOUTVALUE_RATIO);
			headerbarElement->setLayoutRule(fgl::LAYOUTRULE_HEIGHT, 0.134,	fgl::LAYOUTVALUE_RATIO);
			element->addChildElement(headerbarElement);
			
			element->sendChildElementToBack(headerbarElement);
			element->sendChildElementToBack(backgroundElement);
			
			backButton = new MenuButton(assetManager, "buttons/back.png");
			backButton->setTapHandler([=]{
				getScreenManager()->popScreen();
			});
			backButton->setLayoutRule(fgl::LAYOUTRULE_LEFT,	 0,		fgl::LAYOUTVALUE_RATIO);
			backButton->setLayoutRule(fgl::LAYOUTRULE_TOP,	 0,		fgl::LAYOUTVALUE_RATIO);
			backButton->setLayoutRule(fgl::LAYOUTRULE_WIDTH, 0.145,	fgl::LAYOUTVALUE_RATIO);
			backButton->setLayoutRule(fgl::LAYOUTRULE_HEIGHT,0.145,	fgl::LAYOUTVALUE_RATIO);
			element->addChildElement(backButton);
		}
		
		BaseMenuScreen::~BaseMenuScreen()
		{
			for(auto& screenPair : screens)
			{
				delete screenPair.second;
			}

			delete backgroundElement;
			delete headerbarElement;
			delete backButton;
		}

		void BaseMenuScreen::setState(const fgl::Dictionary& state)
		{
			//Open for implementation
		}

		fgl::Dictionary BaseMenuScreen::getState() const
		{
			//Open for implementation
			return {};
		}

		void BaseMenuScreen::addScreen(const fgl::String& name, BaseMenuScreen* screen)
		{
			if(screens.has(name))
			{
				throw fgl::IllegalArgumentException("name", "another screen already exists with that name");
			}
			screens[name] = screen;
		}

		void BaseMenuScreen::removeScreen(const fgl::String& name)
		{
			if(auto screen = screens.get(name, nullptr))
			{
				screens.remove(name);
				delete screen;
			}
		}

		BaseMenuScreen* BaseMenuScreen::getScreen(const fgl::String& name) const
		{
			return screens.get(name, nullptr);
		}

		const fgl::BasicDictionary<fgl::String, BaseMenuScreen*>& BaseMenuScreen::getScreens() const
		{
			return screens;
		}

		void BaseMenuScreen::goToScreen(const fgl::String& name, const fgl::Transition* transition, unsigned long long duration)
		{
			if(auto screen = screens.get(name, nullptr))
			{
				getScreenManager()->pushScreen(screen, transition, duration);
			}
			else
			{
				throw fgl::IllegalArgumentException("name", "no screen exists with that name");
			}
		}

		void BaseMenuScreen::goBack()
		{
			if(auto screenManager = getScreenManager())
			{
				auto& screens = screenManager->getScreens();
				size_t screenIndex = screens.indexOf(this);
				if(screenIndex==-1)
				{
					throw fgl::IllegalStateException("cannot call goBack on a Screen that is not on the navigation stack");
				}
				else if(screenIndex==0)
				{
					throw fgl::IllegalStateException("cannot call goBack on the first Screen in the navigation stack");
				}
				auto previousScreen = screens.get(screenIndex-1);
				screenManager->popToScreen(previousScreen);
			}
			else
			{
				throw fgl::IllegalStateException("cannot call goBack on a Screen that is not on the navigation stack");
			}
		}
		
		fgl::ImageElement* BaseMenuScreen::getBackgroundElement() const
		{
			return backgroundElement;
		}
		
		fgl::ImageElement* BaseMenuScreen::getHeaderbarElement() const
		{
			return headerbarElement;
		}
		
		MenuButton* BaseMenuScreen::getBackButton() const
		{
			return backButton;
		}
		
		void BaseMenuScreen::setHeaderbarMode(const HeaderbarMode&mode)
		{
			if(mode == HEADERBAR_FULL)
			{
				headerbarElement->setImage(img_headerbar_full);
			}
			else if(mode == HEADERBAR_SMALL)
			{
				headerbarElement->setImage(img_headerbar_small);
			}
		}

		MenuData* BaseMenuScreen::getMenuData() const
		{
			return menuData;
		}
	}
}
