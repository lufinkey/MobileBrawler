
#include "Vector2.h"

#pragma once

namespace GameLibrary
{
	class Rectangle
	{
	public:
		int x;
		int y;
		int width;
		int height;

		Rectangle();
		Rectangle(int x, int y, int width, int height);

		bool contains(const Vector2i&point) const;
		bool intersects(const Rectangle&rect) const;
		void combine(const Rectangle&rect);
		Rectangle getIntersect(const Rectangle&rect) const
	};

	class RectangleF
	{
	public:
		float x;
		float y;
		float width;
		float height;

		RectangleF();
		RectangleF(float x, float y, float width, float height);

		bool contains(const Vector2f&point) const;
		bool intersects(const RectangleF&rect) const;
		void combine(const RectangleF&rect);
		RectangleF getIntersect(const RectangleF&rect) const;
	};
}
