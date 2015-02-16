
#pragma once

#include "Vector2.h"
#include "Polygon.h"

namespace GameLibrary
{
	template<typename T>
	/*! Contains data about a rectangle*/
	class RectangleType
	{
	public:
		/*! The x coordinate of the top left of the rectangle*/
		T x;
		/*! The y coordinate of the top left of the rectangle*/
		T y;
		/*! The width of the rectangle*/
		T width;
		/*! The height of the rectangle*/
		T height;
		
		/*! default constructor*/
		RectangleType() : x(0), y(0), width(0), height(0)
		{
			//
		}
		
		/*! Constructs a rectangle with a given top left coordinate and size.
			\param x the x coordinate of the top left of the rectangle
			\param y the y coordinate of the top left of the rectangle
			\param width the width of the rectangle
			\param height the height of the rectangle*/
		RectangleType(const T&x, const T&t, const T&width, const T&height) : x(x), y(y), width(width), height(height)
		{
			//
		}
		
		/*! Calculates whether a given point is inside the bounds of the rectangle.
			\param point the point to check
			\returns true if the given point is inside the rectangle's bounds, or false if otherwise*/
		bool contains(const Vector2<T>&point) const
		{
			if(point.x>=x && point.y>=y && point.x<=(x+width) && point.y<=(y+height))
			{
				return true;
			}
			return false;
		}
		
		/*! Calculates whether a given rectangle is inside the bounds of this rectangle.
			\param rect the rectangle to check
			\returns true if the given rectangle is inside this rectangle's bounds, or false if otherwise*/
		bool contains(const RectangleType<T>&rect) const
		{
			if(x <= rect.x &&y <= rect.y && x >= (rect.x+rect.width) && y >= (rect.y+rect.height))
			{
				return true;
			}
			return false;
		}
		
		/*! Calculates whether a given rectangle is intersecting the bounds of this rectangle.
			\param rect the rectangle to check
			\param true if the given rectangle is intersecting this rectangle's bounds, or false if otherwise*/
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
		
		/*! Calculates the area of the rectangle (width*height).
			\returns a value representing the width multiplied by the height*/
		T getArea() const
		{
			return width*height;
		}
		
		/*! Gets a rectangle of the overlap between this rectangle and a given rectangle.
			\param rect the rectangle to check the overlap with
			\returns a rectangle representing the overlap, or a Rectangle containing a width and height of 0 if the rectangle is not overlapping*/
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
		
		/*! Resizes and moves this rectangle, maintaining its aspect ratio, to fit within a given containing rectangle.
			\param container a containing rectangle*/
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
		
		/*! Resizes and moves this rectangle, maintaining its aspect ratio, to exactly fill a given containing rectangle.
			\param container a containing rectangle*/
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
		
		/*void scale(double scaleX, double scaleY, const T&originX, const T& originY)
		{
			Transform transform;
			transform.scale((float)scaleX, (float)scaleY, (float)originX, (float)originY);
			Polygon polygon = toPolygon();
			polygon = transform.transform(polygon);
			x = (T)(polygon.getPoints().get(0).x);
			y = (T)(polygon.getPoints().get(0).y);
			width = (T)(polygon.getPoints().get(2).x - polygon.getPoints().get(0).x);
			height = (T)(polygon.getPoints().get(2).y - polygon.getPoints().get(0).y);
		}*/
		
		/*! Creates a polygon with the coordinates of the 4 corners of this rectangle.
			\returns a Polygon object*/
		PolygonType<T> toPolygon() const
		{
			PolygonType<T> polygon;
			polygon.addPoint((float)x, (float)y);
			polygon.addPoint((float)(x+width), (float)y);
			polygon.addPoint((float)(x+width), (float)(y+height));
			polygon.addPoint((float)x, (float)(y+height));
			return polygon;
		}
	};
	
	typedef RectangleType<int> RectangleI;
	typedef RectangleType<unsigned int> RectangleU;
	typedef RectangleType<float> RectangleF;
	typedef RectangleType<double> RectangleD;
	
	template<typename T>
	/*! */
	class RectType
	{
	public:
		T left;
		T top;
		T right;
		T bottom;
		
		RectType() : left(0), top(0), right(0), bottom(0)
		{
			//
		}
		
		RectType(const T&left, const T&top, const T&right, const T&bottom) : left(left), top(top), right(right), bottom(bottom)
		{
			//
		}
		
		RectType(const RectType<T>&rect) : left(rect.left), top(rect.top), right(rect.right), bottom(rect.bottom)
		{
			//
		}
		
		RectType(const RectangleType<T>&rect) : left(rect.x), top(rect.y), right(rect.x+rect.width), bottom(rect.y+rect.height)
		{
			//
		}
		
		RectType<T>& operator=(const RectType<T>&rect)
		{
			left = rect.left;
			top = rect.top;
			right = rect.right;
			bottom = rect.bottom;
			return *this;
		}
		
		RectangleType<T>& toRectangle() const
		{
			return RectangleType<T>(left,top,right-left,bottom-top);
		}
		
		operator RectangleType<T>() const
		{
			return RectangleType<T>(left,top,right-left,bottom-top);
		}
	};
	
	typedef RectType<int> RectI;
	typedef RectType<unsigned int> RectU;
	typedef RectType<float> RectF;
	typedef RectType<double> RectD;
}
