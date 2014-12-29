
#include "SlideTransition.h"

namespace GameLibrary
{
	SlideTransition::SlideTransition(SlideDirection dir)
	{
		if(dir == SLIDE_UP || dir == SLIDE_RIGHT || dir == SLIDE_DOWN || dir == SLIDE_LEFT)
		{
			direction = dir;
		}
		else
		{
			direction = SLIDE_LEFT;
		}
	}
	
	SlideTransition::~SlideTransition()
	{
		//
	}
	
	void SlideTransition::draw(ApplicationData appData, Graphics graphics, float progress, Drawable*element1, Drawable*element2) const
	{
		Graphics element1Graphics(graphics);
		Graphics element2Graphics(graphics);
		
		float h1 = 0;
		float h2 = 0;
		float w1 = 0;
		float w2 = 0;

		RectangleF e1rect = element1->getFrame();
		RectangleF e2rect = element2->getFrame();

		Vector2f mainSize;
		if(e1rect.x > e2rect.x)
		{
			mainSize.x = e1rect.x;
		}
		else
		{
			mainSize.x = e2rect.x;
		}
		if(e1rect.y > e2rect.y)
		{
			mainSize.y = e1rect.y;
		}
		else
		{
			mainSize.y = e2rect.y;
		}
		
		switch(direction)
		{
			case SLIDE_UP:
			{
				h1 = -((float)(progress * mainSize.y));
				h2 = mainSize.y + h1;
			}
			break;
			
			case SLIDE_RIGHT:
			{
				w1 = (float)(progress * mainSize.x);
				w2 = -mainSize.x + w1;
			}
			break;
			
			case SLIDE_DOWN:
			{
				h1 = (float)(progress * mainSize.y);
				h2 = -mainSize.y + h1;
			}
			break;
			
			case SLIDE_LEFT:
			{
				w1 = -((float)(progress * mainSize.x));
				w2 = mainSize.x + w1;
			}
			break;
		}
		
		element1Graphics.translate((float)w1, (float)h1);
		element2Graphics.translate((float)w2, (float)h2);
		
		element1->draw(appData, element1Graphics);
		element2->draw(appData, element2Graphics);
	}
}
