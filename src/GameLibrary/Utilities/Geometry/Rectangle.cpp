
#include "Rectangle.h"

namespace GameLibrary
{
	Rectangle::Rectangle()
	{
		x=0;
		y=0;
		width=0;
		height=0;
	}

	Rectangle::Rectangle(int xpnt, int ypnt, int w, int h)
	{
		x = xpnt;
		y = ypnt;
		width = w;
		height = h;
	}

	RectangleF::RectangleF()
	{
		x=0;
		y=0;
		width=0;
		height=0;
	}

	RectangleF::RectangleF(float xpnt, float ypnt, float w, float h)
	{
		x = xpnt; 
		y = ypnt;
		width = w;
		height = h;
	}
}
