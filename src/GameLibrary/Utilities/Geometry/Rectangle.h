
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
	};
}
