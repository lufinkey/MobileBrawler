
#pragma once

#include "../../Types.h"

namespace GameLibrary
{
	template<typename T>
	class Vector2
	{
	public:
		T x;
		T y;

		Vector2() : x(0), y(0)
		{
			//
		}

		Vector2(const T&X, const T&Y)
		{
			x = X;
			y = Y;
		}

		Vector2(const Vector2<T>&vect)
		{
			x = vect.x;
			y = vect.y;
		}

		void operator=(const Vector2<T>&vect)
		{
			x = vect.x;
			y = vect.y;
		}

		Vector2<T> operator+(const Vector2<T>&vect) const
		{
			return Vector2<T>(x+vect.x, y+vect.y);
		}

		Vector2<T> operator-(const Vector2<T>&vect) const
		{
			return Vector2<T>(x-vect.x, y-vect.y);
		}

		Vector2<T> operator*(const Vector2<T>&vect) const
		{
			return Vector2<T>(x*vect.x, y*vect.y);
		}

		Vector2<T> operator/(const Vector2<T>&vect) const
		{
			return Vector2<T>(x/vect.x, y/vect.y);
		}

		Vector2<T>& operator+=(const Vector2<T>&vect)
		{
			x+=vect.x;
			y+=vect.y;
			return *this;
		}

		Vector2<T>& operator-=(const Vector2<T>&vect)
		{
			x-=vect.x;
			y-=vect.y;
			return *this;
		}

		Vector2<T>& operator*=(const Vector2<T>&vect)
		{
			x*=vect.x;
			y*=vect.y;
			return *this;
		}

		Vector2<T>& operator/=(const Vector2<T>&vect)
		{
			x/=vect.x;
			y/=vect.y;
			return *this;
		}

		bool operator==(const Vector2<T>&vect) const
		{
			if (x == vect.x && y == vect.y)
			{
				return true;
			}
			return false;
		}

		bool operator!=(const Vector2<T>&vect) const
		{
			if (x == vect.x && y == vect.y)
			{
				return false;
			}
			return true;
		}

		bool equals(const Vector2<T>&vect) const
		{
			if (x == vect.x && y == vect.y)
			{
				return true;
			}
			return false;
		}
	};

	typedef Vector2<byte> Vector2b;
	typedef Vector2<int> Vector2i;
	typedef Vector2<float> Vector2f;
	typedef Vector2<double> Vector2d;
	typedef Vector2<unsigned int> Vector2u;
	typedef Vector2<long> Vector2l;
	typedef Vector2<long long> Vector2ll;
	typedef Vector2<unsigned long long> Vector2ull;
	typedef Vector2<long double> Vector2ld;
}