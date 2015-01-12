
#pragma once

#include "../ArrayList.h"
#include "Vector2.h"

namespace GameLibrary
{
	class Polygon
	{
	private:
		ArrayList<Vector2f> points;
		
	public:
		Polygon();
		Polygon(const Polygon&);
		Polygon(const float*xpoints, const float*ypoints, unsigned int numpoints);
		Polygon(const ArrayList<Vector2f>& points);
		Polygon(const Vector2f* points, unsigned int numpoints);
		~Polygon();
		
		Polygon& operator=(const Polygon&);
		
		void addPoint(float x, float y);
		void addPoint(const Vector2f&point);
		const ArrayList<Vector2f>& getPoints() const;
		
		bool contains(float x, float y) const;
		bool contains(const Vector2f&point) const;
		
		void clear();
		
		void translate(float x, float y);
		void translate(const Vector2f&delta);
		void scale(float x, float y);
		void scale(const Vector2f&factors);
		void rotate(float degrees);
		void rotate(float degrees, float x, float y);
		void rotate(float degrees, const Vector2f&center);
	};
}