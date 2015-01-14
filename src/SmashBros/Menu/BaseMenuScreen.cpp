
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
		
		BaseMenuScreen::BaseMenuScreen(const MenuData&menuData)
		{
			AssetManager* assetManager = menuData.getAssetManager();
			
			assetManager->loadTexture("assets/menu/backgrounds/circles.png");
			assetManager->loadTexture("assets/menu/elements/headerbar_full.png");
			assetManager->loadTexture("assets/menu/elements/headerbar_small.png");
			
			img_headerbar_small = assetManager->getTexture("assets/menu/elements/headerbar_small.png");
			img_headerbar_full = assetManager->getTexture("assets/menu/elements/headerbar_full.png");

			hoverPulseScale = 1;
			hoverPulseGrowing = true;
			hoverPulseEnabled = false;
			hoverPressed = false;
			
			ScreenElement* element = getElement();

			RectangleF frame = element->getFrame();
			
			backgroundElement = new ImageElement(RectangleF(0,0,frame.width, frame.height), assetManager->getTexture("assets/menu/backgrounds/circles.png"));
			backgroundElement->setDisplayMode(ImageElement::DISPLAY_ZOOM);
			element->addChildElement(backgroundElement);
			
			headerbarElement = new ImageElement(RectangleF(0,0,frame.width, 50), img_headerbar_full);
			headerbarElement->setDisplayMode(ImageElement::DISPLAY_ZOOM);
			element->addChildElement(headerbarElement);
			
			element->sendChildElementToBack(headerbarElement);
			element->sendChildElementToBack(backgroundElement);
			
			backButton = (SpriteActor*)getItem(addItem(Global::getScreenCoords(0.07f,0.08f), new Animation(assetManager, 1, "assets/menu/buttons/back.png")));
			backButton->Actor::scaleToFit(Global::getScreenCoords(0.175f,0.175f));
		}
		
		BaseMenuScreen::~BaseMenuScreen()
		{
			backgroundElement->removeFromParentElement();
			delete backgroundElement;
			headerbarElement->removeFromParentElement();
			delete headerbarElement;
		}
		
		void BaseMenuScreen::onWillAppear(const Transition*transition)
		{
			MenuScreen::onWillAppear(transition);
			
			RectangleF frame = getFrame();
			
			backgroundElement->setFrame(RectangleF(0,0,frame.width,frame.height));
			
			TextureImage* headerbarImage = headerbarElement->getImage();
			float headerbarImgWidth = (float)headerbarImage->getWidth();
			float headerbarImgHeight = (float)headerbarImage->getHeight();
			float ratX = frame.width/headerbarImgWidth;
			headerbarElement->setFrame(RectangleF(0,0,frame.width, headerbarImgHeight*ratX));
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
