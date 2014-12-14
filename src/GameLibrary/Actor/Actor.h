
#include "BaseActor.h"

#pragma once

namespace GameLibrary
{
	class Actor : public BaseActor
	{
	public:
		Actor();
		Actor(float x, float y);
		virtual ~Actor();

		virtual void update(ApplicationData appData);
		virtual void draw(ApplicationData appData, Graphics graphics) const;

		virtual RectangleF getFrame() const;
	};
}
