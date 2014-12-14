
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

		virtual void draw(ApplicationData appData, Graphics graphics, float progress, Drawable*element1, Drawable*element2) const;
	};
}