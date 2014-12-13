
#include "FadeZoomTransition.h"

namespace GameLibrary
{
	FadeZoomTransition::FadeZoomTransition(float start)
	{
		startZoom = start;
		endZoom = 1.0f;
	}

	FadeZoomTransition::~FadeZoomTransition()
	{
		//
	}

	void FadeZoomTransition::draw(ApplicationData appData, Graphics graphics, float progress, ScreenElement*element1, ScreenElement*element2) const
	{
		float zoom = startZoom + ((float)progress * (endZoom - startZoom));

		Vector2f e2size = element2->getSize();
		Vector2f e2center = element2->getSize();

		float xOffset = (e2size.x - (e2size.y * zoom)) / (float)(2 * zoom);
		float yOffset = (e2size.y - (e2size.y * zoom)) / (float)(2 * zoom);
		byte alpha = (byte)(progress*255);

		element1->draw(appData, graphics);

		graphics.translate(xOffset+(e2center.x*zoom), yOffset+(e2center.y*zoom));
		graphics.scale(zoom, zoom);
		graphics.setAlpha(alpha);

		element2->draw(appData, graphics);
	}
}