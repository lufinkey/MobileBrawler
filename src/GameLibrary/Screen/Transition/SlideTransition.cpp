
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
	
	void SlideTransition::draw(ApplicationData appData, Graphics graphics, double progress, Drawable*element1, Drawable*element2) const
	{
		Graphics element1Graphics(graphics);
		Graphics element2Graphics(graphics);
		
		double h1 = 0;
		double h2 = 0;
		double w1 = 0;
		double w2 = 0;

		RectangleD e1rect = element1->getFrame();
		RectangleD e2rect = element2->getFrame();

		Vector2d mainSize;
		if(e1rect.x > e2rect.x)
		{
			mainSize.x = e1rect.width;
		}
		else
		{
			mainSize.x = e2rect.width;
		}
		if(e1rect.y > e2rect.y)
		{
			mainSize.y = e1rect.height;
		}
		else
		{
			mainSize.y = e2rect.height;
		}
		
		switch(direction)
		{
			case SLIDE_UP:
			{
				h1 = -((double)(progress * mainSize.y));
				h2 = mainSize.y + h1;
			}
			break;
			
			case SLIDE_RIGHT:
			{
				w1 = (double)(progress * mainSize.x);
				w2 = -mainSize.x + w1;
			}
			break;
			
			case SLIDE_DOWN:
			{
				h1 = (double)(progress * mainSize.y);
				h2 = -mainSize.y + h1;
			}
			break;
			
			case SLIDE_LEFT:
			{
				w1 = -((double)(progress * mainSize.x));
				w2 = mainSize.x + w1;
			}
			break;
		}
		
		element1Graphics.translate((double)w1, (double)h1);
		element2Graphics.translate((double)w2, (double)h2);
		
		element1->draw(appData, element1Graphics);
		element2->draw(appData, element2Graphics);
	}
}
