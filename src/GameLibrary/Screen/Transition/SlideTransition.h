
#pragma once

#include "../../Types.h"
#include "Transition.h"

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
		
		virtual void draw(ApplicationData appData, Graphics graphics, float progress, Drawable*element1, Drawable*element2) const override;
		
	protected:
		SlideDirection direction;
	};
}