
#include "PopoverTransition.h"

namespace GameLibrary
{
	PopoverTransition::PopoverTransition(PopoverDirection dir, bool fades)
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
	
	void PopoverTransition::draw(ApplicationData appData, Graphics graphics, float progress, Drawable*element1, Drawable*element2) const
	{
		RectangleF e1rect = element1->getFrame();
		RectangleF e2rect = element2->getFrame();
		
		float xOff = (e2rect.width - e1rect.width)/2;
		float yOff = (e2rect.height - e1rect.height)/2;
		
		float translationX = xOff;
		float translationY = yOff;
		switch(direction)
		{
			case POPOVER_UP:
			translationY += (e1rect.height*(1-progress));
			break;
			
			case POPOVER_DOWN:
			translationY += -(e1rect.height + (e1rect.height*progress));
			break;
			
			case POPOVER_LEFT:
			translationX += -(e1rect.width - (e1rect.width*progress));
			break;
			
			case POPOVER_RIGHT:
			translationX += (e1rect.width * (1-progress));
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
