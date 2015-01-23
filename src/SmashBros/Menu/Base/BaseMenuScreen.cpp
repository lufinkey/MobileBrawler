
#include "BaseMenuScreen.h"

namespace SmashBros
{
	namespace Menu
	{
#define PULSE_UPPERBOUND 1.1f
#define PULSE_LOWERBOUND 0.98f
#define PULSE_SPEED 0.3f
#define PULSE_HOVERCOLOR Color::LIGHTBLUE
#define PULSE_PRESSCOLOR Color::BLUE
		
		BaseMenuScreen::BaseMenuScreen(const SmashData&smashData)
		{
			AssetManager* assetManager = smashData.getMenuData().getAssetManager();
			
			img_headerbar_small = assetManager->getTexture("elements/headerbar_small.png");
			img_headerbar_full = assetManager->getTexture("elements/headerbar_full.png");
			
			hoverPulseScale = 1;
			hoverPulseGrowing = true;
			hoverPulseEnabled = false;
			hoverPressed = false;
			
			ScreenElement* element = getElement();
			
			Vector2f screenSize = smashData.getScreenCoords(1.0f, 1.0f);
			
			backgroundElement = new ImageElement(RectangleF(0,0,screenSize.x,screenSize.y), assetManager->getTexture("backgrounds/main.png"));
			backgroundElement->setDisplayMode(ImageElement::DISPLAY_ZOOM);
			element->addChildElement(backgroundElement);
			
			float headerbarImgWidth = (float)img_headerbar_full->getWidth();
			float headerbarImgHeight = (float)img_headerbar_full->getHeight();
			float ratX = screenSize.x/headerbarImgWidth;
			
			headerbarElement = new ImageElement(RectangleF(0,0,screenSize.x, headerbarImgHeight*ratX), img_headerbar_full);
			headerbarElement->setDisplayMode(ImageElement::DISPLAY_ZOOM);
			element->addChildElement(headerbarElement);
			
			element->sendChildElementToBack(headerbarElement);
			element->sendChildElementToBack(backgroundElement);
			
			backButton = (SpriteActor*)getItem(addItem(smashData.getScreenCoords(0.07f,0.08f), new Animation(assetManager, 1, "buttons/back.png")));
			backButton->Actor::scaleToFit(smashData.getScreenCoords(0.175f,0.175f));
		}
		
		BaseMenuScreen::~BaseMenuScreen()
		{
			backgroundElement->removeFromParentElement();
			delete backgroundElement;
			headerbarElement->removeFromParentElement();
			delete headerbarElement;
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
				//RectangleF frame = actor->getFrame();
				if(hoverPulseEnabled)
				{
					graphics.scale(hoverPulseScale, hoverPulseScale, actor->x, actor->y);
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
			MenuScreen::drawItem(appData, graphics, itemIndex);
		}
		
		void BaseMenuScreen::onItemHover(unsigned int index)
		{
			if(!Multitouch::isEnabled())
			{
				enableHoverPulse(true);
			}
		}
		
		void BaseMenuScreen::onItemHoverFinish(unsigned int index)
		{
			if(!Multitouch::isEnabled())
			{
				enableHoverPulse(false);
			}
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
		
		ImageElement* BaseMenuScreen::getHeaderbarElement() const
		{
			return headerbarElement;
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
