
#pragma once

#include "../../Types.h"
#include "Transition.h"

namespace GameLibrary
{
	/*! A custom Transition that slides and pushes one Drawable out of the way of the other.*/
	class SlideTransition : public Transition
	{
	public:
		/*! The direction to slide*/
		typedef enum
		{
			/*! The Drawable objects slide upward*/
			SLIDE_UP,
			/*! The Drawable objects slide to the right*/
			SLIDE_RIGHT,
			/*! The Drawable objects slide downward*/
			SLIDE_DOWN,
			/*! The Drawable objects slide to the left*/
			SLIDE_LEFT
		} SlideDirection;
		
		/*! Constructs a transition that slides in a given direction
			\param direction the direction where the Drawable objects slide*/
		SlideTransition(SlideDirection direction);
		/*! virtual destructor*/
		virtual ~SlideTransition();
		
		/*! \copydoc GameLibrary::Transition::draw(ApplicationData,Graphics,double,Drawable*,Drawable*)const*/
		virtual void draw(ApplicationData appData, Graphics graphics, double progress, Drawable*element1, Drawable*element2) const override;
		
	protected:
		/*! The direction where the Drawable objects slide*/
		SlideDirection direction;
	};
}