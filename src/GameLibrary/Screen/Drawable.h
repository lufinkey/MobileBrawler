
#pragma once

#include "../Application/ApplicationData.h"
#include "../Graphics/Graphics.h"

namespace GameLibrary
{
	class Drawable
	{
	public:
		virtual ~Drawable() {};

		virtual void update(ApplicationData appData) = 0;
		virtual void draw(ApplicationData appData, Graphics graphics) const = 0;

		virtual RectangleF getFrame() const = 0;
	};
}
