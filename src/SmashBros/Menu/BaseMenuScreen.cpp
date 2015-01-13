
#include "BaseMenuScreen.h"
#include "../Global.h"

namespace SmashBros
{
	namespace Menu
	{
#define PULSE_UPPERBOUND 1.1f
#define PULSE_LOWERBOUND 0.98f
#define PULSE_SPEED 0.3f
#define PULSE_HOVERCOLOR Color::LIGHTBLUE
#define PULSE_PRESSCOLOR Color::BLUE
		
		BaseMenuScreen::BaseMenuScreen(AssetManager*assetManager)
		{
			hoverPulseScale = 1;
			hoverPulseGrowing = true;
			hoverPulseEnabled = false;
			hoverPressed = false;
			assetManager->loadTexture("images/menu/backgrounds/circles.png");
			ScreenElement* element = getElement();
			backgroundElement = new ImageElement(getElement()->getFrame(), assetManager->getTexture("images/menu/backgrounds/circles.png"));
			backgroundElement->setDisplayMode(ImageElement::DISPLAY_ZOOM);
			element->addChildElement(backgroundElement);
			element->sendChildElementToBack(backgroundElement);
			
			backButton = (SpriteActor*)getItem(addItem(getScreenCoords(0.08f,0.1f), new Animation(assetManager, 1, "images/menu/buttons/back.png")));
		}
		
		BaseMenuScreen::~BaseMenuScreen()
		{
			backgroundElement->removeFromParentElement();
			delete backgroundElement;
		}
		
		void BaseMenuScreen::onWillAppear(const Transition*transition)
		{
			MenuScreen::onWillAppear(transition);
			
			RectangleF screenFrame = getFrame();
			backgroundElement->setFrame(RectangleF(0,0,screenFrame.width,screenFrame.height));
		}
		
		void BaseMenuScreen::updateItems(ApplicationData appData)
		{
			if(getSelectedIndex() != MENUSCREEN_NOSELECTION)
			{
				if(hoverPulseEnabled)
				{
					float scaleIncrement = PULSE_SPEED * appData.getFrameSpeedMultiplier();
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
			MenuScreen::updateItems(appData);
		}
		
		void BaseMenuScreen::drawItem(ApplicationData appData, Graphics graphics, unsigned int itemIndex) const
		{
			if(itemIndex == getSelectedIndex())
			{
				Actor* actor = getItem(itemIndex);
				RectangleF frame = actor->getFrame();
				graphics.scale(hoverPulseScale, hoverPulseScale, actor->x, actor->y);
				if(hoverPressed)
				{
					graphics.compositeTintColor(PULSE_PRESSCOLOR);
				}
				else
				{
					graphics.compositeTintColor(PULSE_HOVERCOLOR);
				}
			}
			MenuScreen::drawItem(appData, graphics, itemIndex);
		}
		
		void BaseMenuScreen::onItemHover(unsigned int index)
		{
			#if defined(TARGETPLATFORM_DESKTOP)
				enableHoverPulse(true);
			#endif
		}
		
		void BaseMenuScreen::onItemHoverFinish(unsigned int index)
		{
			#if defined(TARGETPLATFORM_DESKTOP)
				enableHoverPulse(false);
			#endif
		}
		
		void BaseMenuScreen::onItemPress(unsigned int index)
		{
			hoverPressed = true;
		}
		
		void BaseMenuScreen::onItemPressCancel(unsigned int index)
		{
			hoverPressed = false;
		}
		
		void BaseMenuScreen::onItemRelease(unsigned int index)
		{
			hoverPressed = false;
		}
		
		void BaseMenuScreen::onItemSelect(unsigned int index)
		{
			ScreenManager* screenMgr = getScreenManager();
			if(screenMgr != nullptr)
			{
				if(getItem(index) == backButton)
				{
					screenMgr->pop();
				}
			}
		}
		
		ImageElement* BaseMenuScreen::getBackgroundElement() const
		{
			return backgroundElement;
		}
		
		SpriteActor* BaseMenuScreen::getBackButton() const
		{
			return backButton;
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
