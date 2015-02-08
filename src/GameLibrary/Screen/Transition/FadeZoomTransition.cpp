
#include "FadeZoomTransition.h"

namespace GameLibrary
{
	FadeZoomTransition::FadeZoomTransition(float start, float end)
	{
		startZoom = start;
		endZoom = end;
	}

	FadeZoomTransition::~FadeZoomTransition()
	{
		//
	}

	void FadeZoomTransition::draw(ApplicationData appData, Graphics graphics, float progress, Drawable*element1, Drawable*element2) const
	{
		float zoom = startZoom + ((float)progress * (endZoom - startZoom));

		RectangleF e2rect = element2->getFrame();
		Vector2f e2center = Vector2f(e2rect.x+(e2rect.width/2), e2rect.y+(e2rect.height/2));

		float xOffset = (e2rect.width - (e2rect.width * zoom)) / (float)(2 * zoom);
		float yOffset = (e2rect.height - (e2rect.height * zoom)) / (float)(2 * zoom);
		byte alpha = (byte)(progress*255);

		element1->draw(appData, graphics);

		graphics.translate(xOffset+(e2center.x*zoom), yOffset+(e2center.y*zoom));
		graphics.scale(zoom, zoom);
		graphics.setAlpha(alpha);

		element2->draw(appData, graphics);
	}
}