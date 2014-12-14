
#include "Transition.h"

#pragma once

namespace GameLibrary
{
	class FadeZoomTransition : public Transition
	{
	protected:
		float startZoom;
		float endZoom;

	public:
		FadeZoomTransition(float startZoom);
		virtual ~FadeZoomTransition();

		virtual void draw(ApplicationData appData, Graphics graphics, float progress, Drawable*element1, Drawable*element2) const;
	};
}