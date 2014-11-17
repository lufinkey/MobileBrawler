
#include "Vector2.h"

#pragma once

// all credit to SFML library for original Transform code
// SFML - Simple and Fast Multimedia Library
// Copyright (C) 2007-2014 Laurent Gomila (laurent.gom@gmail.com)

namespace GameLibrary
{
	class Transform
	{
	private:
		float m_matrix[16];

	public:
		static const Transform Identity;

		Transform();
		Transform(float a00, float a01, float a02, float a10, float a11, float a12, float a20, float a21, float a22);
		~Transform();

		const float* getMatrix() const;
		Transform getInverse() const;

		Vector2f transformPoint(float x, float y) const;
		Vector2f transformPoint(const Vector2f& point) const;
		//RectangleF transformRectangle(const RectangleF& rectangle) const;

		Transform& combine(const Transform& transform);
		Transform& translate(float x, float y);
		Transform& translate(const Vector2f& offset);
		Transform& rotate(float degrees);
		Transform& rotate(float degrees, float centerX, float centerY);
		Transform& rotate(float degrees, const Vector2f&center);
		Transform& scale(float scaleX, float scaleY);
		Transform& scale(float scaleX, float scaleY, float centerX, float centerY);
		Transform& scale(const Vector2f& factors);
		Transform& scale(const Vector2f& factors, const Vector2f& center);
	};
}