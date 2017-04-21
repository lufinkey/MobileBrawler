
#include "MenuButton.hpp"

namespace SmashBros
{
#define PULSE_UPPERBOUND 1.1
#define PULSE_LOWERBOUND 0.98
#define PULSE_SPEED 0.3
	
	MenuButton::MenuButton()
		: MenuButton(nullptr, "")
	{
		//
	}
	
	MenuButton::MenuButton(fgl::AssetManager* assetManager, const fgl::String& imagePath)
		: hoverPulsingEnabled(true)
	{
		if(imagePath.length() > 0)
		{
			if(assetManager==nullptr)
			{
				throw fgl::IllegalArgumentException("assetManager", "cannot be null when specifying an image path");
			}
			if(assetManager->loadTexture(imagePath))
			{
				setImage(assetManager->getTexture(imagePath), BUTTONSTATE_NORMAL);
			}
		}
		setTintColor(fgl::Color::LIGHTBLUE, BUTTONSTATE_HOVERED);
		setTintColor(fgl::Color::BLUE, BUTTONSTATE_PRESSED);
		setTintColor(fgl::Color::LIGHTGRAY, BUTTONSTATE_DISABLED);
		
		getImageElement()->setDisplayMode(fgl::ImageElement::DISPLAY_FIT_CENTER);
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
			auto center = getFrame().getCenter();
			graphics.scale((double)hoverPulseScale, (double)hoverPulseScale, center.x, center.y);
		}
		ButtonElement::draw(appData, graphics);
	}
	
	void MenuButton::setHoverPulsingEnabled(bool enabled)
	{
		hoverPulsingEnabled = enabled;
	}
	
	bool MenuButton::isHoverPulsingEnabled() const
	{
		return hoverPulsingEnabled;
	}
}
