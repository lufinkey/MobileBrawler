
#pragma once

#include "Transition.h"

namespace GameLibrary
{
	/*! A custom Transition that slides one Drawable on top of the other, with an optional fade*/
	class PopoverTransition : public Transition
	{
	public:
		/*! The direction of the popover*/
		typedef enum
		{
			/*! The second Drawable slides upward*/
			POPOVER_UP,
			/*! The second Drawable slides to the right*/
			POPOVER_RIGHT,
			/*! The second Drawable slides downward*/
			POPOVER_DOWN,
			/*! The second Drawable slides to the left*/
			POPOVER_LEFT
		} PopoverDirection;
		
		/*! Constructs a transition that slides one Drawable on top of the other Drawable, with an optional fade.
			\param direction the direction of the popover
			\param fade true to fade in as the Drawable slides in, or false to just have the Drawable slide in without fade*/
		explicit PopoverTransition(PopoverDirection direction, bool fade=false);
		/*! virtual destructor*/
		virtual ~PopoverTransition();
		
		/*! \copydoc GameLibrary::Transition::draw(ApplicationData,Graphics,double,Drawable*,Drawable*)const*/
		virtual void draw(ApplicationData appData, Graphics graphics, double progress, Drawable*element1, Drawable*element2) const override;
		
	protected:
		/*! the direction of the popover*/
		PopoverDirection direction;
		/*! Tells whether the transition should fade or not; Value is true to fade in as the Drawable slides in, or false to just have the Drawable slide in without fade*/
		bool fade;
	};
}