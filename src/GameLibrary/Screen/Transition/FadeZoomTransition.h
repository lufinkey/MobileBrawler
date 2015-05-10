
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
		explicit FadeZoomTransition(double startZoom, double endZoom=1.0f);
		/*! virtual destructor*/
		virtual ~FadeZoomTransition();
		
		/*! \copydoc GameLibrary::Transition::draw(ApplicationData,Graphics,double,Drawable*,Drawable*)const*/
		virtual void draw(ApplicationData appData, Graphics graphics, double progress, Drawable*element1, Drawable*element2) const override;
		
	protected:
		/*! the zoom ratio at the beginning of the transition*/
		double startZoom;
		/*! the zoom ratio at the end of the transition; Default value is 1*/
		double endZoom;
	};
}