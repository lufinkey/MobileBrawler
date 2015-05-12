
#pragma once

#include "../String.h"

namespace GameLibrary
{
	template<typename T>
	/*! Contains data about a circle*/
	class Circle
	{
	public:
		/*! The x coordinate for the center of the circle*/
		T x;
		/*! The y coordinate for the center of the circle*/
		T y;
		/*! The radius of the circle*/
		T radius;
		
		/*! default constructor*/
		Circle()
		{
			//
		}
		
		/*! Constructs a circle with a center point and a radius.
			\param x the x coordinate for the center point
			\param y the y coordinate for the center point
			\param radius the radius*/
		Circle(const T&x, const T&y, const T&radius) : x(x), y(y), radius(radius)
		{
			//
		}
		
		String toString() const
		{
			Stringifier<T> stringifier;
			return "Circle(x:" + stringifier.convertToString(&x) + ", y:" + stringifier.convertToString(&y) + ", radius:" + stringifier.convertToString(&radius) + ")";
		}
	};
	
	typedef Circle<int> CircleI;
	typedef Circle<unsigned int> CircleU;
	typedef Circle<float> CircleF;
	typedef Circle<double> CircleD;
}