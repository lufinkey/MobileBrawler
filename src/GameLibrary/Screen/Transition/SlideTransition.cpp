
#include "SlideTransition.h"

namespace GameLibrary
{
	SlideTransition::SlideTransition(byte dir)
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
	
	void SlideTransition::draw(ApplicationData appData, Graphics graphics, float progress, ScreenElement*element1, ScreenElement*element2) const
	{
		Graphics element1Graphics(graphics);
		Graphics element2Graphics(graphics);

		float h1 = 0;
		float h2 = 0;
		float w1 = 0;
		float w2 = 0;

		Vector2f e1size = element1->getSize();
		Vector2f e2size = element2->getSize();
		Vector2f mainSize;
		if(e1size.x > e2size.x)
		{
			mainSize.x = e1size.x;
		}
		else
		{
			mainSize.x = e2size.x;
		}
		if(e1size.y > e2size.y)
		{
			mainSize.y = e1size.y;
		}
		else
		{
			mainSize.y = e2size.y;
		}

		switch (direction)
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
