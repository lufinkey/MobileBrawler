
#include "Transition.h"

#pragma once

namespace GameLibrary
{
	class PopoverTransition : public Transition
	{
	protected:
		byte direction;
		bool fade;
		
	public:
		enum PopoverDirection : byte
		{
			POPOVER_UP,
			POPOVER_RIGHT,
			POPOVER_DOWN,
			POPOVER_LEFT
		};
		
		PopoverTransition(byte direction, bool fade=false);
		virtual ~PopoverTransition();
		
		virtual void draw(ApplicationData appData, Graphics graphics, float progress, Drawable*element1, Drawable*element2) const;
	};
}