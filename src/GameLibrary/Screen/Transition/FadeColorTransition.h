
#include "Transition.h"

#pragma once

namespace GameLibrary
{
	class FadeColorTransition : public Transition
	{
	protected:
		Color color;

	public:
		FadeColorTransition(const Color& color);
		virtual ~FadeColorTransition();

		virtual void draw(ApplicationData appData, Graphics graphics, float progress, ScreenElement*element1, ScreenElement*element2) const;
	};
}