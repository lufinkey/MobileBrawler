
#include "../../Types.h"
#include "Transition.h"

#pragma once

namespace GameLibrary
{
	class SlideTransition : public Transition
	{
	public:
		typedef enum
		{
			SLIDE_UP,
			SLIDE_RIGHT,
			SLIDE_DOWN,
			SLIDE_LEFT
		} SlideDirection;
		
		SlideTransition(SlideDirection direction);
		virtual ~SlideTransition();
		
		virtual void draw(ApplicationData appData, Graphics graphics, float progress, Drawable*element1, Drawable*element2) const;
		
	protected:
		SlideDirection direction;
	};
}