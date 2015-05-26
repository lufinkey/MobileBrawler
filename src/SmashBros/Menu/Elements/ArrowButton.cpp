
#include "ArrowButton.h"

namespace SmashBros
{
	namespace Menu
	{
		ArrowButton::ArrowButton(Number*val, const Number&minimum, const Number&maximum, const Number&increment, const ArrowButton::Direction&direction, AssetManager*assetManager, const Color&hover, const Color&press)
			: ArrowButton(0, 0, val, minimum, maximum, increment, direction, assetManager, hover, press)
		{
			//
		}
		
		ArrowButton::ArrowButton(double x, double y, Number*val, const Number&minimum, const Number&maximum, const Number&increment, const ArrowButton::Direction&direction, AssetManager*assetManager, const Color&hover, const Color&press) : SpriteActor(x, y)
		{
			selecting = false;
			value = val;
			min = minimum;
			max = maximum;
			incr = increment;
			dir = direction;
			hoverColor = hover;
			pressColor = press;
			listener = nullptr;
			
			addAnimation("up", new Animation(1, assetManager, "elements/button_arrow_up.png"));
			addAnimation("down", new Animation(1, assetManager, "elements/button_arrow_down.png"));
			addAnimation("left", new Animation(1, assetManager, "elements/button_arrow_left.png"));
			addAnimation("right", new Animation(1, assetManager, "elements/button_arrow_right.png"));
			setDirection(direction);
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
		
		void ArrowButton::onMousePress(const ActorMouseEvent& evt)
		{
			selecting = true;
		}
		
		void ArrowButton::onMouseRelease(const ActorMouseEvent& evt)
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
					if(listener != nullptr)
					{
						listener->onArrowButtonValueChange(this);
					}
					onValueChange();
				}
			}
		}
		
		void ArrowButton::onValueChange()
		{
			//Open for implementation
		}
		
		void ArrowButton::setEventListener(ArrowButtonEventListener*eventListener)
		{
			listener = eventListener;
		}
		
		void ArrowButton::setDirection(const ArrowButton::Direction&direction)
		{
			dir = direction;
			switch(direction)
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
		
		void ArrowButton::setValueProperties(Number*value_arg, const Number&minimum, const Number&maximum, const Number&increment)
		{
			value = value_arg;
			min = minimum;
			max = maximum;
			incr = increment;
		}
		
		ArrowButtonEventListener* ArrowButton::getEventListener() const
		{
			return listener;
		}
		
		const ArrowButton::Direction& ArrowButton::getDirection() const
		{
			return dir;
		}
	}
}
