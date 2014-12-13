
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

		virtual void draw(ApplicationData appData, Graphics graphics, float progress, ScreenElement*element1, ScreenElement*element2) const;
	};
}