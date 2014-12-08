
#include "Circle.h"

namespace GameLibrary
{
	Circle::Circle()
	{
		x = 0;
		y = 0;
		radius = 0;
	}

	Circle::Circle(int x1, int y1, int r)
	{
		x = x1;
		y = y1;
		radius = r;
	}

	CircleF::CircleF()
	{
		x = 0;
		y = 0;
		radius = 0;
	}

	CircleF::CircleF(float x1, float y1, float r)
	{
		x = x1;
		y = y1;
		radius = r;
	}
}