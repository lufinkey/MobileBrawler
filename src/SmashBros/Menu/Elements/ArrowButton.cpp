
#include "ArrowButton.h"

namespace SmashBros
{
	namespace Menu
	{
		ArrowButton::ArrowButton(float x, float y, Number*val, const Number&minimum, const Number&maximum, const Number&increment, const ArrowButton::Direction&direction, AssetManager*assetManager, const Color&hover, const Color&press) : SpriteActor(x, y)
		{
			selecting = false;
			value = val;
			min = minimum;
			max = maximum;
			incr = increment;
			dir = direction;
			hoverColor = hover;
			pressColor = press;
			
			addAnimation("up", new Animation(1, assetManager, "elements/button_arrow_up.png"));
			addAnimation("down", new Animation(1, assetManager, "elements/button_arrow_down.png"));
			addAnimation("left", new Animation(1, assetManager, "elements/button_arrow_left.png"));
			addAnimation("right", new Animation(1, assetManager, "elements/button_arrow_right.png"));
			
			switch(dir)
			{
				case DIRECTION_UP:
				changeAnimation("up", Animation::FORWARD);
				break;
				
				case DIRECTION_DOWN:
				changeAnimation("down", Animation::FORWARD);
				break;
				
				case DIRECTION_LEFT:
				changeAnimation("left", Animation::FORWARD);
				break;
				
				case DIRECTION_RIGHT:
				changeAnimation("right", Animation::FORWARD);
				break;
			}
		}
		
		ArrowButton::~ArrowButton()
		{
			//
		}
		
		void ArrowButton::update(ApplicationData appData)
		{
			SpriteActor::update(appData);
			
			if(isMouseOver())
			{
				if(selecting)
				{
					setColor(pressColor);
				}
				else
				{
					setColor(hoverColor);
				}
			}
			else
			{
				setColor(Color::WHITE);
				selecting = false;
			}
		}
		
		void ArrowButton::onMousePress(ApplicationData appData, unsigned int touchID)
		{
			selecting = true;
		}
		
		void ArrowButton::onMouseRelease(ApplicationData appData, unsigned int touchID)
		{
			if(selecting)
			{
				selecting = false;
				//inrement value
				if(value != nullptr)
				{
					*value += incr;
					if(*value > max)
					{
						*value = min;
					}
					else if(*value < min)
					{
						*value = max;
					}
					onValueChange();
				}
			}
		}
		
		void ArrowButton::onValueChange()
		{
			//Open for implementation
		}
	}
}
