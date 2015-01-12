
#include "SmashBrosMenuScreen.h"

namespace SmashBros
{
	namespace Menu
	{
#define PULSE_UPPERBOUND 1.4f
#define PULSE_LOWERBOUND 0.75f
#define PULSE_SPEED 1.4f
#define PULSE_HOVERCOLOR Color::LIGHTBLUE
#define PULSE_PRESSCOLOR Color::BLUE
		
		SmashBrosMenuScreen::SmashBrosMenuScreen()
		{
			hoverPulseScale = 1;
			hoverPulseGrowing = true;
			hoverPressed = false;
		}
		
		SmashBrosMenuScreen::~SmashBrosMenuScreen()
		{
			//
		}
		
		void SmashBrosMenuScreen::updateItems(ApplicationData appData)
		{
			if(getSelectedIndex() != MENUSCREEN_NOSELECTION)
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
			MenuScreen::updateItems(appData);
		}
		
		void SmashBrosMenuScreen::drawItem(ApplicationData appData, Graphics graphics, unsigned int itemIndex) const
		{
			if(itemIndex == getSelectedIndex())
			{
				BaseActor* actor = getItem(itemIndex);
				RectangleF frame = actor->getFrame();
				float difX = (frame.width - (frame.width*hoverPulseScale))/(2*hoverPulseScale);
				float difY = (frame.height - (frame.height*hoverPulseScale))/(2*hoverPulseScale);
				graphics.scale(hoverPulseScale, hoverPulseScale);
				graphics.translate(difX, difY);
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
		
		void SmashBrosMenuScreen::onItemHover(unsigned int index)
		{
			#if defined(TARGETPLATFORM_DESKTOP)
				hoverPulseScale = 1;
				hoverPulseGrowing = true;
			#endif
		}
		
		void SmashBrosMenuScreen::onItemHoverFinish(unsigned int index)
		{
			#if defined(TARGETPLATFORM_DESKTOP)
				hoverPulseScale = 1;
				hoverPulseGrowing = true;
			#endif
		}
		
		void SmashBrosMenuScreen::onItemPress(unsigned int index)
		{
			hoverPressed = true;
		}
		
		void SmashBrosMenuScreen::onItemPressCancel(unsigned int index)
		{
			hoverPressed = false;
		}
		
		void SmashBrosMenuScreen::onItemRelease(unsigned int index)
		{
			hoverPressed = false;
		}
	}
}
