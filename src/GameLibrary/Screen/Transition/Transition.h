
#include "../../Types.h"
#include "../ScreenElement.h"

#pragma once

namespace GameLibrary
{
	class Transition
	{
	public:
		static const unsigned long long defaultDuration;

		Transition();
		virtual ~Transition();

		virtual void draw(ApplicationData appData, Graphics graphics, float progress, ScreenElement*element1, ScreenElement*element2) const;
	};
}