
#include "Polygon.h"
#include "Transform.h"

namespace GameLibrary
{
	Polygon::Polygon()
	{
		//
	}

	Polygon::Polygon(const Polygon&polygon)
	{
		points = polygon.points;
	}

	Polygon::Polygon(const float*xpoints, const float*ypoints, unsigned int numpoints)
	{
		for (unsigned int i=0; i<numpoints; i++)
		{
			points.add(Vector2f(xpoints[i], ypoints[i]));
		}
	}

	Polygon::Polygon(const ArrayList<Vector2f>&pnts)
	{
		points = pnts;
	}

	Polygon::Polygon(const Vector2f*pnts, unsigned int numpoints)
	{
		for(unsigned int i=0; i<numpoints; i++)
		{
			points.add(pnts[i]);
		}
	}

	Polygon::~Polygon()
	{
		//
	}

	Polygon& Polygon::operator=(const Polygon&polygon)
	{
		points = polygon.points;
		return *this;
	}

	void Polygon::addPoint(float x, float y)
	{
		points.add(Vector2f(x,y));
	}

	void Polygon::addPoint(const Vector2f&point)
	{
		points.add(point);
	}

	const ArrayList<Vector2f>& Polygon::getPoints() const
	{
		return points;
	}

	bool Polygon::contains(float x, float y) const
	{
		if(points.size() == 0)
		{
			return false;
		}
		unsigned int length = points.size();
		unsigned int i = 0;
		unsigned int j = 0;
		bool c = false;
		for (i = 0, j = (length - 1); i < length; j = i, i++)
		{
			if (((points[i].y > y) != (points[j].y > y)) &&
				(x < (points[j].x - points[i].x) * (y - points[i].y) / (points[j].y - points[i].y) + points[i].x))
			{
				c = !c;
			}
		}
		return c;
	}

	bool Polygon::contains(const Vector2f&point) const
	{
		return contains(point.x, point.y);
	}

	void Polygon::clear()
	{
		points.clear();
	}

	void Polygon::translate(float x, float y)
	{
		for(unsigned int i=0; i<points.size(); i++)
		{
			Vector2f point = points.get(i);
			point.x += x;
			point.y += y;
			points.set(i, point);
		}
	}

	void Polygon::translate(const Vector2f&delta)
	{
		translate(delta.x, delta.y);
	}

	void Polygon::scale(float x, float y)
	{
		for(unsigned int i=0; i<points.size(); i++)
		{
			Vector2f point = points.get(i);
			point.x *= x;
			point.y *= y;
			points.set(i, point);
		}
	}

	void Polygon::scale(const Vector2f&factors)
	{
		scale(factors.x, factors.y);
	}

	void Polygon::rotate(float degrees)
	{
		rotate(degrees, 0, 0);
	}

	void Polygon::rotate(float degrees, float x, float y)
	{
		Transform transform;
		transform.rotate(degrees, x, y);
		
		for(unsigned int i=0; i<points.size(); i++)
		{
			points.set(i, transform.transform(points.get(i)));
		}
	}

	void Polygon::rotate(float degrees, const Vector2f&center)
	{
		rotate(degrees, center.x, center.y);
	}
}