
#include "../../Types.h"
#include "../ScreenElement.h"

#pragma once

namespace GameLibrary
{
	class Transition
	{
	public:
		Transition();
		virtual ~Transition();

		virtual void draw(ApplicationData appData, Graphics graphics, double progress, ScreenElement*element1, ScreenElement*element2);
	};
}