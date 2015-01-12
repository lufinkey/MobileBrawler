
#pragma once

#include "Vector2.h"
#include "Polygon.h"

namespace GameLibrary
{
	template<typename T>
	class RectangleType
	{
	public:
		T x;
		T y;
		T width;
		T height;

		RectangleType() : x(0), y(0), width(0), height(0)
		{
			//
		}
	
		RectangleType(const T&X, const T&Y, const T&W, const T&H) : x(X), y(Y), width(W), height(H)
		{
			//
		}

		bool contains(const Vector2<T>&point) const
		{
			if(point.x>=x && point.y>=y && point.x<=(x+width) && point.y<=(y+height))
			{
				return true;
			}
			return false;
		}
	
		bool intersects(const RectangleType<T>&rect) const
		{
			T left1, left2;
			T right1, right2;
			T top1, top2;
			T bottom1, bottom2;
		
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
	
		RectangleType getIntersect(const RectangleType<T>&rect) const
		{
			T overlapLeft = 0;
			T overlapTop = 0;
			T overlapRight = 0;
			T overlapBottom = 0;
		
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
			RectangleType<T> overlapRect;
			overlapRect.x = x + overlapLeft;
			overlapRect.y = y + overlapTop;
			overlapRect.width = overlapRight - overlapLeft;
			overlapRect.height = overlapBottom - overlapTop;
			return overlapRect;
		}
	
		void combine(const RectangleType<T>&rect)
		{
			T rect_left = rect.x;
			T rect_top = rect.y;
			T rect_right = rect.x + rect.width;
			T rect_bottom = rect.y + rect.height;
		
			T left = x;
			T top = y;
			T right = x + width;
			T bottom = y + height;
		
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
	
		void scaleToFit(const RectangleType<T>&container)
		{
			T fixedHeight = height;
			long double ratX = ((long double)container.width)/((long double)width);
			fixedHeight = (T)(((long double)height)*ratX);
			
			if(fixedHeight<=container.height)
			{
				width = container.width;
				height = fixedHeight;
				x = container.x + ((container.width - width)/2);
				y = container.y + ((container.height - height)/2);
				return;
			}
		
			T fixedWidth = width;
			long double ratY = ((long double)container.height)/((long double)height);
			fixedWidth = (T)(((long double)width)*ratY);

			width = fixedWidth;
			height = container.height;
			x = container.x + ((container.width - width)/2);
			y = container.y + ((container.height - height)/2);
		}
	
		void scaleToFill(const RectangleType<T>&container)
		{
			T fixedHeight = height;
			long double ratX = ((long double)container.width)/((long double)width);
			fixedHeight = (T)(((long double)height)*ratX);
			
			if(fixedHeight>=container.height)
			{
				width = container.width;
				height = fixedHeight;
				x = container.x + ((container.width - width)/2);
				y = container.y + ((container.height - height)/2);
				return;
			}
			
			T fixedWidth = width;
			double ratY = ((long double)container.height)/((long double)height);
			fixedWidth = (T)(((long double)width)*ratY);

			width = fixedWidth;
			height = container.height;
			x = container.x + ((container.width - width)/2);
			y = container.y + ((container.height - height)/2);
		}
		
		Polygon toPolygon() const
		{
			Polygon polygon;
			polygon.addPoint((float)x, (float)y);
			polygon.addPoint((float)(x+width), (float)y);
			polygon.addPoint((float)(x+width), (float)(y+height));
			polygon.addPoint((float)x, (float)(y+height));
		}
	};
	
	typedef RectangleType<int> RectangleI;
	typedef RectangleType<float> RectangleF;
	typedef RectangleType<double> RectangleD;
}
