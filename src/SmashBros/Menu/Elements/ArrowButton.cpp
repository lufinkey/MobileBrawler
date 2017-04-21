
#include "ArrowButton.hpp"

namespace SmashBros
{
	namespace Menu
	{
		ArrowButton::ArrowButton(fgl::AssetManager* assetManager, ArrowButton::Direction direction)
			: MenuButton(assetManager, getDirectionImagePath(direction)),
			direction(direction)
		{
			setHoverPulsingEnabled(false);
		}
		
		ArrowButton::Direction ArrowButton::getDirection() const
		{
			return direction;
		}
		
		fgl::String ArrowButton::getDirectionImagePath(ArrowButton::Direction direction)
		{
			switch(direction)
			{
				case DIRECTION_UP:
					return "elements/button_arrow_up.png";
					
				case DIRECTION_DOWN:
					return "elements/button_arrow_down.png";
					
				case DIRECTION_LEFT:
					return "elements/button_arrow_left.png";
					
				case DIRECTION_RIGHT:
					return "elements/button_arrow_right.png";
			}
			return "";
		}
	}
}
