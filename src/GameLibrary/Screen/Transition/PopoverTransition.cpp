
#include "PopoverTransition.h"

namespace GameLibrary
{
	PopoverTransition::PopoverTransition(byte dir, bool fades)
	{
		if(dir == POPOVER_UP || dir == POPOVER_RIGHT || dir == POPOVER_DOWN || dir == POPOVER_LEFT)
		{
			direction = dir;
		}
		else
		{
			direction = POPOVER_UP;
		}
		fade = fades;
	}
	
	PopoverTransition::~PopoverTransition()
	{
		//
	}
	
	void PopoverTransition::draw(ApplicationData appData, Graphics graphics, float progress, ScreenElement*element1, ScreenElement*element2) const
	{
		Vector2f e1size = element1->getSize();
		Vector2f e2size = element2->getSize();
		
		float xOff = (e2size.x - e1size.x)/2;
		float yOff = (e2size.y - e1size.y)/2;
		
		float translationX = xOff;
		float translationY = yOff;
		switch (direction)
		{
			case POPOVER_UP:
			translationY += (e1size.y*(1-progress));
			break;
			
			case POPOVER_DOWN:
			translationY += -(e1size.y + (e1size.y*progress));
			break;
			
			case POPOVER_LEFT:
			translationX += -(e1size.x - (e1size.x*progress));
			break;
			
			case POPOVER_RIGHT:
			translationX += (e1size.x * (1-progress));
			break;
		}
		
		element1->draw(appData, graphics);
		
		if(fade)
		{
			graphics.compositeAlpha((byte)(progress*255));
		}
		graphics.translate((float)translationX, (float)translationY);
		
		element2->draw(appData, graphics);
	}
}
