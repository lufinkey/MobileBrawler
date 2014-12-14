
#include "../../Types.h"
#include "../Drawable.h"

#pragma once

namespace GameLibrary
{
	class Transition
	{
	public:
		static const unsigned long long defaultDuration;
		
		Transition();
		virtual ~Transition();
		
		virtual void draw(ApplicationData appData, Graphics graphics, float progress, Drawable*element1, Drawable*element2) const;
	};
}