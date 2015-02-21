
#pragma once

#include "Vector2.h"
#include "Rectangle.h"
#include "Polygon.h"
#include "../Math.h"

// all credit to SFML library for original Transform code
// SFML - Simple and Fast Multimedia Library
// Copyright (C) 2007-2014 Laurent Gomila (laurent.gom@gmail.com)

namespace GameLibrary
{
	template<typename T>
	class TransformType
	{
	public:
		TransformType()
		{
			reset();
		}
		
		TransformType(const TransformType<T>&transform)
		{
			for(unsigned int i=0; i<16; i++)
			{
				m_matrix[i] = transform.m_matrix[i];
			}
		}
		
		TransformType(const T&a00, const T&a01, const T&a02, const T&a10, const T&a11, const T&a12, const T&a20, const T&a21, const T&a22)
		{
			m_matrix[0] = a00; m_matrix[4] = a01; m_matrix[8]  = 0; m_matrix[12] = a02;
			m_matrix[1] = a10; m_matrix[5] = a11; m_matrix[9]  = 0; m_matrix[13] = a12;
			m_matrix[2] = 0;   m_matrix[6] = 0;   m_matrix[10] = 1; m_matrix[14] = 0;
			m_matrix[3] = a20; m_matrix[7] = a21; m_matrix[11] = 0; m_matrix[15] = a22;
		}
		
		TransformType& operator=(const TransformType<T>&transform)
		{
			for(unsigned int i = 0; i < 16; i++)
			{
				m_matrix[i] = transform.m_matrix[i];
			}
			return *this;
		}
		
		void reset()
		{
			// Identity m_matrix
			m_matrix[0] = 1.f; m_matrix[4] = 0.f; m_matrix[8]  = 0.f; m_matrix[12] = 0.f;
			m_matrix[1] = 0.f; m_matrix[5] = 1.f; m_matrix[9]  = 0.f; m_matrix[13] = 0.f;
			m_matrix[2] = 0.f; m_matrix[6] = 0.f; m_matrix[10] = 1.f; m_matrix[14] = 0.f;
			m_matrix[3] = 0.f; m_matrix[7] = 0.f; m_matrix[11] = 0.f; m_matrix[15] = 1.f;
		}
		
		const T* getMatrix() const
		{
			return m_matrix;
		}
		
		TransformType<T> getInverse() const
		{
			// Compute the determinant
			T det = m_matrix[0] * (m_matrix[15] * m_matrix[5] - m_matrix[7] * m_matrix[13]) -
					m_matrix[1] * (m_matrix[15] * m_matrix[4] - m_matrix[7] * m_matrix[12]) +
					m_matrix[3] * (m_matrix[13] * m_matrix[4] - m_matrix[5] * m_matrix[12]);
			
			// Compute the inverse if the determinant is not zero
			// (don't use an epsilon because the determinant may *really* be tiny)
			if (det != 0.f)
			{
				return TransformType<T>( (m_matrix[15] * m_matrix[5] - m_matrix[7] * m_matrix[13]) / det,
									-(m_matrix[15] * m_matrix[4] - m_matrix[7] * m_matrix[12]) / det,
									 (m_matrix[13] * m_matrix[4] - m_matrix[5] * m_matrix[12]) / det,
									-(m_matrix[15] * m_matrix[1] - m_matrix[3] * m_matrix[13]) / det,
									 (m_matrix[15] * m_matrix[0] - m_matrix[3] * m_matrix[12]) / det,
									-(m_matrix[13] * m_matrix[0] - m_matrix[1] * m_matrix[12]) / det,
									 (m_matrix[7]  * m_matrix[1] - m_matrix[3] * m_matrix[5])  / det,
									-(m_matrix[7]  * m_matrix[0] - m_matrix[3] * m_matrix[4])  / det,
									 (m_matrix[5]  * m_matrix[0] - m_matrix[1] * m_matrix[4])  / det);
			}
			else
			{
				return TransformType<T>();
			}
		}
		
		Vector2<T> transform(const T&x, const T&y) const
		{
			return Vector2<T>(  m_matrix[0] * x + m_matrix[4] * y + m_matrix[12],
								m_matrix[1] * x + m_matrix[5] * y + m_matrix[13]);
		}
		
		Vector2<T> transform(const Vector2<T>& point) const
		{
			return Vector2<T>(  m_matrix[0] * point.x + m_matrix[4] * point.y + m_matrix[12],
								m_matrix[1] * point.x + m_matrix[5] * point.y + m_matrix[13]);
		}
		
		RectangleType<T> transform(const RectangleType<T>& rectangle) const
		{
			// Transform the 4 corners of the rectangle
			const Vector2d points[] =
			{
				transform(rectangle.x, rectangle.y),
				transform(rectangle.x, rectangle.y + rectangle.height),
				transform(rectangle.x + rectangle.width, rectangle.y),
				transform(rectangle.x + rectangle.width, rectangle.y + rectangle.height)
			};
			
			// Compute the bounding rectangle of the transformed points
			T left = points[0].x;
			T top = points[0].y;
			T right = points[0].x;
			T bottom = points[0].y;
			for(unsigned int i=1; i<4; ++i)
			{
				if (points[i].x < left)
				{
					left = points[i].x;
				}
				else if (points[i].x > right)
				{
					right = points[i].x;
				}
				if (points[i].y < top)
				{
					top = points[i].y;
				}
				else if (points[i].y > bottom)
				{
					bottom = points[i].y;
				}
			}
			return RectangleType<T>(left, top, right - left, bottom - top);
		}
		
		PolygonType<T> transform(const PolygonType<T>& polygon) const
		{
			PolygonType<T> newPoly;
			const ArrayList<Vector2<T> >& points = polygon.getPoints();
			for(unsigned int i=0; i<points.size(); i++)
			{
				newPoly.addPoint(transform(points.get(i)));
			}
			return newPoly;
		}
		
		TransformType<T>& combine(const TransformType<T>& transform)
		{
			const T* a = m_matrix;
			const T* b = transform.m_matrix;
			
			*this = TransformType<T>(a[0] * b[0]  + a[4] * b[1]  + a[12] * b[3],
								 a[0] * b[4]  + a[4] * b[5]  + a[12] * b[7],
								 a[0] * b[12] + a[4] * b[13] + a[12] * b[15],
								 a[1] * b[0]  + a[5] * b[1]  + a[13] * b[3],
								 a[1] * b[4]  + a[5] * b[5]  + a[13] * b[7],
								 a[1] * b[12] + a[5] * b[13] + a[13] * b[15],
								 a[3] * b[0]  + a[7] * b[1]  + a[15] * b[3],
								 a[3] * b[4]  + a[7] * b[5]  + a[15] * b[7],
								 a[3] * b[12] + a[7] * b[13] + a[15] * b[15]);
			
			return *this;
		}
		
		TransformType<T>& translate(const T&x, const T&y)
		{
			TransformType<T> translation(1, 0, x,
									 0, 1, y,
									 0, 0, 1);
			return combine(translation);
		}
		
		TransformType<T>& translate(const Vector2<T>& offset)
		{
			TransformType<T> translation(1, 0, offset.x,
									 0, 1, offset.y,
									 0, 0, 1);
			return combine(translation);
		}
		
		TransformType<T>& rotate(const T& degrees)
		{
			T rad = Math::degtorad(degrees);
			T cos = (T)Math::cos(rad);
			T sin = (T)Math::sin(rad);
			
			TransformType<T> rotation(  cos, -sin, 0,
									sin,  cos, 0,
									0,	  0,   1);
			
			return combine(rotation);
		}
		
		TransformType<T>& rotate(const T& degrees, const T& centerX, const T& centerY)
		{
			T rad = Math::degtorad(degrees);
			T cos = (T)Math::cos(rad);
			T sin = (T)Math::sin(rad);
			
			TransformType<T> rotation(  cos, -sin, centerX*(1-cos)+centerY*sin,
									sin,  cos, centerY*(1-cos)-centerX*sin,
									0,	  0,   1);
			
			return combine(rotation);
		}
		
		TransformType<T>& rotate(const T& degrees, const Vector2<T>&center)
		{
			T rad = Math::degtorad(degrees);
			T cos = (T)Math::cos(rad);
			T sin = (T)Math::sin(rad);
			
			TransformType<T> rotation(  cos, -sin, center.x*(1-cos)+center.y*sin,
									sin,  cos, center.y*(1-cos)-center.x*sin,
									0,	  0,   1);
			
			return combine(rotation);
		}
		
		TransformType<T>& scale(const T&scaleX, const T&scaleY)
		{
			TransformType<T> scaling(scaleX, 0,		 0,
								 0,		 scaleY, 0,
								 0,		 0,		 1);
			
			return combine(scaling);
		}
		
		TransformType<T>& scale(const T& scaleX, const T& scaleY, const T& centerX, const T& centerY)
		{
			TransformType<T> scaling(scaleX, 0,		 centerX*(1-scaleX),
								 0,		 scaleY, centerY*(1-scaleY),
								 0,		 0,		 1);
			
			return combine(scaling);
		}
		
		TransformType<T>& scale(const Vector2<T>& factors)
		{
			TransformType<T> scaling(factors.x, 0,			0,
								 0,			factors.y,	0,
								 0,			0,			1);
			
			return combine(scaling);
		}
		
		TransformType<T>& scale(const Vector2<T>& factors, const Vector2<T>& center)
		{
			TransformType<T> scaling(factors.x, 0,			center.x*(1-factors.x),
								 0,			factors.y,	center.y*(1-factors.y),
								 0,			0,			1);
			
			return combine(scaling);
		}
		
	private:
		T m_matrix[16];
	};
	
	typedef TransformType<float> TransformF;
	typedef TransformType<double> TransformD;
	typedef TransformType<long double> TransformLD;
}