
#pragma once

namespace GameLibrary
{
	class Circle
	{
	public:
		int x;
		int y;
		int radius;

		Circle();
		Circle(int x, int y, int radius);
	};

	class CircleF
	{
	public:
		float x;
		float y;
		float radius;

		CircleF();
		CircleF(float x, float y, float radius);
	};
}