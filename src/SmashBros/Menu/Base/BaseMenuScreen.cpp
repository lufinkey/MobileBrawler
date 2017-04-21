
#include "BaseMenuScreen.hpp"

namespace SmashBros
{
	namespace Menu
	{
#define PULSE_UPPERBOUND 1.1
#define PULSE_LOWERBOUND 0.98
#define PULSE_SPEED 0.3
#define PULSE_HOVERCOLOR Color::LIGHTBLUE
#define PULSE_PRESSCOLOR Color::BLUE
		
		BaseMenuScreen::BaseMenuScreen(const SmashData&smashData)
		{
			AssetManager* assetManager = smashData.getMenuData()->getAssetManager();
			
			img_headerbar_small = assetManager->getTexture("elements/headerbar_small.png");
			img_headerbar_full = assetManager->getTexture("elements/headerbar_full.png");
			
			hoverPulseScale = 1;
			hoverPulseGrowing = true;
			hoverPulseEnabled = false;
			hoverPressed = false;
			
			ScreenElement* element = getElement();
			
			backgroundElement = new ImageElement(assetManager->getTexture("backgrounds/main.png"), ImageElement::DISPLAY_FILL);
			backgroundElement->setLayoutRule(LAYOUTRULE_LEFT,   0, LAYOUTVALUE_RATIO);
			backgroundElement->setLayoutRule(LAYOUTRULE_TOP,    0, LAYOUTVALUE_RATIO);
			backgroundElement->setLayoutRule(LAYOUTRULE_RIGHT,  0, LAYOUTVALUE_RATIO);
			backgroundElement->setLayoutRule(LAYOUTRULE_BOTTOM, 0, LAYOUTVALUE_RATIO);
			element->addChildElement(backgroundElement);
			
			headerbarElement = new ImageElement(img_headerbar_full, ImageElement::DISPLAY_FILL);
			headerbarElement->setLayoutRule(LAYOUTRULE_LEFT,   0.0,   LAYOUTVALUE_RATIO);
			headerbarElement->setLayoutRule(LAYOUTRULE_TOP,    0.0,   LAYOUTVALUE_RATIO);
			headerbarElement->setLayoutRule(LAYOUTRULE_RIGHT,  0.0,   LAYOUTVALUE_RATIO);
			headerbarElement->setLayoutRule(LAYOUTRULE_HEIGHT, 0.134, LAYOUTVALUE_RATIO);
			element->addChildElement(headerbarElement);
			
			element->sendChildElementToBack(headerbarElement);
			element->sendChildElementToBack(backgroundElement);
			
			backButton = new MenuButton();
			assetManager->loadTexture("buttons/back.png");
			backButton->setImage(assetManager->getTexture("buttons/back.png"), ButtonElement::BUTTONSTATE_NORMAL);
			backButton->setTapHandler([=]{
				getScreenManager()->pop();
			});
			backButton->setLayoutRule(LAYOUTRULE_LEFT,	0,		LAYOUTVALUE_RATIO);
			backButton->setLayoutRule(LAYOUTRULE_TOP,	0,		LAYOUTVALUE_RATIO);
			backButton->setLayoutRule(LAYOUTRULE_WIDTH,	0.145,	LAYOUTVALUE_RATIO);
			backButton->setLayoutRule(LAYOUTRULE_HEIGHT, 0.145,	LAYOUTVALUE_RATIO);
			element->addChildElement(backButton);
		}
		
		BaseMenuScreen::~BaseMenuScreen()
		{
			delete backgroundElement;
			delete headerbarElement;
			delete backButton;
		}
		
		void BaseMenuScreen::onWillDisappear(const Transition*transition)
		{
			MenuScreen::onWillDisappear(transition);
			clearMouseStates();
		}
		
		void BaseMenuScreen::onUpdate(const ApplicationData& appData)
		{
			if(getSelectedIndex() != MenuScreen::NO_SELECTION)
			{
				if(hoverPulseEnabled)
				{
					double scaleIncrement = PULSE_SPEED * appData.getFrameSpeedMultiplier();
					if(hoverPulseGrowing)
					{
						hoverPulseScale += scaleIncrement;
						if(hoverPulseScale >= PULSE_UPPERBOUND)
						{
							hoverPulseScale = PULSE_UPPERBOUND;
							hoverPulseGrowing = false;
						}
					}
					else
					{
						hoverPulseScale -= scaleIncrement;
						if(hoverPulseScale <= PULSE_LOWERBOUND)
						{
							hoverPulseScale = PULSE_LOWERBOUND;
							hoverPulseGrowing = true;
						}
					}
				}
			}
			MenuScreen::onUpdate(appData);
		}
		
		void BaseMenuScreen::drawItem(ApplicationData appData, Graphics graphics, Actor*item) const
		{
			size_t selectedIndex = getSelectedIndex();
			if(selectedIndex!=MenuScreen::NO_SELECTION && item == getItem(selectedIndex))
			{
				//RectangleD frame = actor->getFrame();
				if(hoverPulseEnabled)
				{
					graphics.scale(hoverPulseScale, hoverPulseScale, item->x, item->y);
				}
				if(hoverPressed)
				{
					graphics.compositeTintColor(PULSE_PRESSCOLOR);
				}
				else
				{
					graphics.compositeTintColor(PULSE_HOVERCOLOR);
				}
			}
			MenuScreen::drawItem(appData, graphics, item);
		}
		
		void BaseMenuScreen::onItemHover(size_t index)
		{
			if(!Multitouch::isAvailable())
			{
				enableHoverPulse(true);
			}
		}
		
		void BaseMenuScreen::onItemHoverFinish(size_t index)
		{
			if(!Multitouch::isAvailable())
			{
				enableHoverPulse(false);
			}
		}
		
		void BaseMenuScreen::onItemPress(size_t index)
		{
			hoverPressed = true;
		}
		
		void BaseMenuScreen::onItemPressCancel(size_t index)
		{
			hoverPressed = false;
		}
		
		void BaseMenuScreen::onItemRelease(size_t index)
		{
			hoverPressed = false;
		}
		
		void BaseMenuScreen::onItemSelect(size_t index)
		{
			//
		}
		
		ImageElement* BaseMenuScreen::getBackgroundElement() const
		{
			return backgroundElement;
		}
		
		ImageElement* BaseMenuScreen::getHeaderbarElement() const
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
		
		void BaseMenuScreen::enableHoverPulse(bool toggle)
		{
			if(toggle && !hoverPulseEnabled)
			{
				hoverPulseEnabled = true;
				hoverPulseScale = 1;
				hoverPulseGrowing = true;
			}
			else if(!toggle && hoverPulseEnabled)
			{
				hoverPulseEnabled = false;
				hoverPulseScale = 1;
				hoverPulseGrowing = true;
			}
		}
	}
}
