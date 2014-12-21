
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

		bool contains(const Vector2i&point);
		bool intersects(const Rectangle&rect);
		void combine(const Rectangle&rect);
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

		bool contains(const Vector2f&point);
		bool intersects(const RectangleF&rect);
		void combine(const RectangleF&rect);
	};
}
