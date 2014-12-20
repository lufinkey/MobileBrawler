
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
	
	bool Rectangle::contains(const Vector2i&point)
	{
		if(point.x>=x && point.y>=y && point.x<=(x+width) && point.y<=(y+height))
		{
			return true;
		}
		return false;
	}
	
	bool Rectangle::intersects(const Rectangle&rect)
	{
		int left1, left2;
	    int right1, right2;
	    int top1, top2;
	    int bottom1, bottom2;
		
	    left1 = x;
	    left2 = rect.x;
	    right1 = x+width;
	    right2 = rect.x+rect.width;
	    top1 = y;
	    top2 = rect.y;
	    bottom1 = y+height;
	    bottom2 = rect.y+rect.height;
		
	    if (bottom1 < top2)
	    {
	        return false;
	    }
	    if (top1 > bottom2)
	    {
	        return false;
	    }
		
	    if (right1 < left2)
	    {
	        return false;
	    }
	    if (left1 > right2)
	    {
	        return false;
	    }
		
	    return true;
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

	bool RectangleF::contains(const Vector2f&point)
	{
		if(point.x>=x && point.y>=y && point.x<=(x+width) && point.y<=(y+height))
		{
			return true;
		}
		return false;
	}
	
	bool RectangleF::intersects(const RectangleF&rect)
	{
		float left1, left2;
	    float right1, right2;
	    float top1, top2;
	    float bottom1, bottom2;
		
	    left1 = x;
	    left2 = rect.x;
	    right1 = x+width;
	    right2 = rect.x+rect.width;
	    top1 = y;
	    top2 = rect.y;
	    bottom1 = y+height;
	    bottom2 = rect.y+rect.height;
		
	    if (bottom1 < top2)
	    {
	        return false;
	    }
	    if (top1 > bottom2)
	    {
	        return false;
	    }
		
	    if (right1 < left2)
	    {
	        return false;
	    }
	    if (left1 > right2)
	    {
	        return false;
	    }
		
	    return true;
	}
}
