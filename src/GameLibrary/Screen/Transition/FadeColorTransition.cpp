
#include "FadeColorTransition.h"

namespace GameLibrary
{
	FadeColorTransition::FadeColorTransition(const Color&c)
	{
		color = c;
	}

	FadeColorTransition::~FadeColorTransition()
	{
		//
	}

	void FadeColorTransition::draw(ApplicationData appData, Graphics graphics, float progress, Drawable*element1, Drawable*element2) const
	{
		if (progress < 0.5)
		{
			float alpha = ((float)progress / 0.5f);

			RectangleF e1rect = element1->getFrame();
			Vector2f e1center = Vector2f(e1rect.x+(e1rect.width/2), e1rect.y+(e1rect.height/2));

			element1->draw(appData, graphics);

			graphics.setColor(color);
			graphics.compositeAlpha((byte)(alpha*255));
			graphics.fillRect(e1center.x-(e1rect.width/2), e1center.y-(e1rect.height/2), e1rect.width, e1rect.height);
		}
		else
		{
			float alpha = 1 - (((float)progress - 0.5f) / 0.5f);

			RectangleF e2rect = element2->getFrame();
			Vector2f e2center = Vector2f(e2rect.x+(e2rect.width/2), e2rect.y+(e2rect.height/2));

			element2->draw(appData, graphics);

			graphics.setColor(color);
			graphics.compositeAlpha((byte)(alpha*255));
			graphics.fillRect(e2center.x-(e2rect.width/2), e2center.y-(e2rect.height/2), e2rect.width, e2rect.height);
		}
	}
}