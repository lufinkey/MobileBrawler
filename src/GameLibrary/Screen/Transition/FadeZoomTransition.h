
#pragma once

#include "Transition.h"

namespace GameLibrary
{
	/*! A custom Transition that fades and zooms between two Drawable objects*/
	class FadeZoomTransition : public Transition
	{
	public:
		/*! Constructs a transition that fades and zooms between two Drawable objects
			\param startZoom the zoom ratio at the beginning of the transition
			\param endZoom the zoom ratio at the end of the transition; Default value is 1*/
		FadeZoomTransition(float startZoom, float endZoom=1.0f);
		/*! virtual destructor*/
		virtual ~FadeZoomTransition();
		
		/*! \copydoc GameLibrary::Transition::draw(ApplicationData,Graphics,float,Drawable*,Drawable*)const*/
		virtual void draw(ApplicationData appData, Graphics graphics, float progress, Drawable*element1, Drawable*element2) const override;
		
	protected:
		/*! the zoom ratio at the beginning of the transition*/
		float startZoom;
		/*! the zoom ratio at the end of the transition; Default value is 1*/
		float endZoom;
	};
}