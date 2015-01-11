
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
	
	bool Rectangle::contains(const Vector2i&point) const
	{
		if(point.x>=x && point.y>=y && point.x<=(x+width) && point.y<=(y+height))
		{
			return true;
		}
		return false;
	}
	
	bool Rectangle::intersects(const Rectangle&rect) const
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
	
	Rectangle Rectangle::getIntersect(const Rectangle&rect) const
	{
		int overlapLeft = 0;
		int overlapTop = 0;
		int overlapRight = 0;
		int overlapBottom = 0;
		
		if(intersects(rect))
		{
			if(x <= rect.x)
			{
				if((x + width) <= (rect.x + rect.width))
				{
					overlapLeft = rect.x - x;
					overlapRight = width;
				}
				else
				{
					overlapLeft = rect.x - x;
					overlapRight = overlapLeft + rect.width;
				}
			}
			else
			{
				if((x + width) <= (rect.x + rect.width))
				{
					overlapLeft = 0;
					overlapRight = width;
				}
				else
				{
					overlapLeft = 0;
					overlapRight = (rect.x + rect.width) - x;
				}
			}
				
			if(y <= rect.y)
			{
				if((y + height) <= (rect.y + rect.height))
				{
					overlapTop = rect.y - y;
					overlapBottom = height;
				}
				else
				{
					overlapTop = rect.y - y;
					overlapBottom = overlapTop + rect.height;
				}
			}
			else
			{
				if((y + height)<= (rect.y + rect.height))
				{
					overlapTop = 0;
					overlapBottom = height;
				}
				else
				{
					overlapTop = 0;
					overlapBottom = (rect.y + rect.height) - y;
				}
			}
		}
		else
		{
			overlapLeft = 0;
			overlapTop = 0;
			overlapRight = 0;
			overlapBottom = 0;
		}
		Rectangle overlapRect;
		overlapRect.x = x + overlapLeft;
		overlapRect.y = y + overlapTop;
		overlapRect.width = overlapRight - overlapLeft;
		overlapRect.height = overlapBottom - overlapTop;
		return overlapRect;
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

	bool RectangleF::contains(const Vector2f&point) const
	{
		if(point.x>=x && point.y>=y && point.x<=(x+width) && point.y<=(y+height))
		{
			return true;
		}
		return false;
	}
	
	bool RectangleF::intersects(const RectangleF&rect) const
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
	
	RectangleF RectangleF::getIntersect(const RectangleF&rect) const
	{
		float overlapLeft = 0;
		float overlapTop = 0;
		float overlapRight = 0;
		float overlapBottom = 0;
		
		if(intersects(rect))
		{
			if(x <= rect.x)
			{
				if((x + width) <= (rect.x + rect.width))
				{
					overlapLeft = rect.x - x;
					overlapRight = width;
				}
				else
				{
					overlapLeft = rect.x - x;
					overlapRight = overlapLeft + rect.width;
				}
			}
			else
			{
				if((x + width) <= (rect.x + rect.width))
				{
					overlapLeft = 0;
					overlapRight = width;
				}
				else
				{
					overlapLeft = 0;
					overlapRight = (rect.x + rect.width) - x;
				}
			}
				
			if(y <= rect.y)
			{
				if((y + height) <= (rect.y + rect.height))
				{
					overlapTop = rect.y - y;
					overlapBottom = height;
				}
				else
				{
					overlapTop = rect.y - y;
					overlapBottom = overlapTop + rect.height;
				}
			}
			else
			{
				if((y + height)<= (rect.y + rect.height))
				{
					overlapTop = 0;
					overlapBottom = height;
				}
				else
				{
					overlapTop = 0;
					overlapBottom = (rect.y + rect.height) - y;
				}
			}
		}
		else
		{
			overlapLeft = 0;
			overlapTop = 0;
			overlapRight = 0;
			overlapBottom = 0;
		}
		RectangleF overlapRect;
		overlapRect.x = x + overlapLeft;
		overlapRect.y = y + overlapTop;
		overlapRect.width = overlapRight - overlapLeft;
		overlapRect.height = overlapBottom - overlapTop;
		return overlapRect;
	}
}
