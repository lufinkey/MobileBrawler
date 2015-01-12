
#pragma once

#include "Transition.h"

namespace GameLibrary
{
	class FadeColorTransition : public Transition
	{
	protected:
		Color color;
		float frozenPortion;

	public:
		FadeColorTransition(const Color& color, float frozenPortion = 0);
		virtual ~FadeColorTransition();

		virtual void draw(ApplicationData appData, Graphics graphics, float progress, Drawable*element1, Drawable*element2) const;
	};
}