
#include "../../Types.h"
#include "Transition.h"

#pragma once

namespace GameLibrary
{
	class SlideTransition : public Transition
	{
	protected:
		byte direction;
		
	public:
		enum SlideDirection : byte
		{
			SLIDE_UP,
			SLIDE_RIGHT,
			SLIDE_DOWN,
			SLIDE_LEFT
		};
		
		SlideTransition(byte direction);
		virtual ~SlideTransition();
		
		virtual void draw(ApplicationData appData, Graphics graphics, float progress, ScreenElement*element1, ScreenElement*element2) const;
	};
}