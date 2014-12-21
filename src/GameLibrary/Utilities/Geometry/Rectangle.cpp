
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

	void Rectangle::combine(const Rectangle&rect)
	{
		int rect_left = rect.x;
		int rect_top = rect.y;
		int rect_right = rect.x + rect.width;
		int rect_bottom = rect.y + rect.height;

		int left = x;
		int top = y;
		int right = x + width;
		int bottom = y + height;

		if(rect_left < left)
		{
			left = rect_left;
		}
		if(rect_top < top)
		{
			top = rect_top;
		}
		if(rect_right > right)
		{
			right = rect_right;
		}
		if(rect_bottom > bottom)
		{
			bottom = rect_bottom;
		}

		x = left;
		y = top;
		width = right-left;
		height = bottom-top;
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
	
	void RectangleF::combine(const RectangleF&rect)
	{
		float rect_left = rect.x;
		float rect_top = rect.y;
		float rect_right = rect.x + rect.width;
		float rect_bottom = rect.y + rect.height;

		float left = x;
		float top = y;
		float right = x + width;
		float bottom = y + height;

		if(rect_left < left)
		{
			left = rect_left;
		}
		if(rect_top < top)
		{
			top = rect_top;
		}
		if(rect_right > right)
		{
			right = rect_right;
		}
		if(rect_bottom > bottom)
		{
			bottom = rect_bottom;
		}

		x = left;
		y = top;
		width = right-left;
		height = bottom-top;
	}
}
