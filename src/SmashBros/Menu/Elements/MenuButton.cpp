
#include "MenuButton.hpp"

namespace SmashBros
{
#define PULSE_UPPERBOUND 1.1
#define PULSE_LOWERBOUND 0.98
#define PULSE_SPEED 0.3
	
	MenuButton::MenuButton()
		: hoverPulsingEnabled(true)
	{
		setTintColor(fgl::Color::LIGHTBLUE, BUTTONSTATE_HOVERED);
		setTintColor(fgl::Color::BLUE, BUTTONSTATE_PRESSED);
		setTintColor(fgl::Color::LIGHTGRAY, BUTTONSTATE_DISABLED);
	}
	
	void MenuButton::update(fgl::ApplicationData appData)
	{
		if(getHoveredMouseIndexes().size() > 0 && hoverPulsingEnabled && isEnabled())
		{
			float scaleIncrement = (float)(PULSE_SPEED * appData.getFrameSpeedMultiplier());
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
		else
		{
			hoverPulseScale = 1;
		}
		ButtonElement::update(appData);
	}
	
	void MenuButton::draw(fgl::ApplicationData appData, fgl::Graphics graphics) const
	{
		if(getHoveredMouseIndexes().size() > 0 && hoverPulsingEnabled && isEnabled())
		{
			auto frame = getFrame();
			double centerX = frame.width/2;
			double centerY = frame.height/2;
			graphics.scale((double)hoverPulseScale, (double)hoverPulseScale, centerX, centerY);
		}
		ButtonElement::draw(appData, graphics);
	}
}
