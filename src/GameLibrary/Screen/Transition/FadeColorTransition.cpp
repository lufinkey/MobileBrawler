
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

	void FadeColorTransition::draw(ApplicationData appData, Graphics graphics, float progress, ScreenElement*element1, ScreenElement*element2) const
	{
		if (progress < 0.5)
		{
			float alpha = ((float)progress / 0.5f);

			Vector2f center = element1->getCenter();
			Vector2f size = element1->getSize();

			element1->draw(appData, graphics);

			graphics.compositeColor(color);
			graphics.compositeAlpha((byte)(alpha*255));
			graphics.fillRect(center.x-(size.x/2), center.y-(size.y/2), size.x, size.y);
		}
		else
		{
			float alpha = 1 - (((float)progress - 0.5f) / 0.5f);

			Vector2f center = element2->getCenter();
			Vector2f size = element2->getSize();

			element2->draw(appData, graphics);

			graphics.compositeColor(color);
			graphics.compositeAlpha((byte)(alpha*255));
			graphics.fillRect(center.x-(size.x/2), center.y-(size.y/2), size.x, size.y);
		}
	}
}