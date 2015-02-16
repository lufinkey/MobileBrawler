
#pragma once

namespace GameLibrary
{
	template<typename T>
	/*! Contains data about a circle*/
	class CircleType
	{
	public:
		/*! The x coordinate for the center of the circle*/
		T x;
		/*! The y coordinate for the center of the circle*/
		T y;
		/*! The radius of the circle*/
		T radius;
		
		/*! default constructor*/
		CircleType()
		{
			//
		}
		
		/*! Constructs a circle with a center point and a radius.
			\param x the x coordinate for the center point
			\param y the y coordinate for the center point
			\param radius the radius*/
		CircleType(const T&x, const T&y, const T&radius) : x(x), y(y), radius(radius)
		{
			//
		}
	};
	
	typedef CircleType<int> CircleI;
	typedef CircleType<unsigned int> CircleU;
	typedef CircleType<float> CircleF;
	typedef CircleType<double> CircleD;
}