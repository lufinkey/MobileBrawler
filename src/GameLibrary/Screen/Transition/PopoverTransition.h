
#pragma once

#include "Transition.h"

namespace GameLibrary
{
	class PopoverTransition : public Transition
	{
	public:
		typedef enum
		{
			POPOVER_UP,
			POPOVER_RIGHT,
			POPOVER_DOWN,
			POPOVER_LEFT
		} PopoverDirection;
		
		PopoverTransition(PopoverDirection direction, bool fade=false);
		virtual ~PopoverTransition();
		
		virtual void draw(ApplicationData appData, Graphics graphics, float progress, Drawable*element1, Drawable*element2) const override;
		
	protected:
		PopoverDirection direction;
		bool fade;
	};
}