
#include "Color.h"
#include "../Types.h"
#include "../Utilities/Geometry/Rectangle.h"
#include "../Utilities/Geometry/Transform.h"

#pragma once

namespace GameLibrary
{
	class Graphics
	{
		friend class BufferedImage;
		friend class Font;
	private:
		void*renderer;

		Color color;
		Color tintColor;
		float alpha;
		
		Font*font;
		static Font*defaultFont;
		
		RectangleF clipRect;
		
		Transform transform;
		
		Graphics(Window&window);
		
	public:
		Graphics(const Graphics&);
		virtual ~Graphics();
		
		virtual void rotate(float degrees);
		virtual void rotate(float degrees, float x, float y);
		virtual void rotate(float degrees, const Vector2f&center);
		
		virtual void scale(float scaleX, float scaleY);
		virtual void scale(const Vector2f& factors);
		
		virtual void translate(float x, float y);
		virtual void translate(const Vector2f&delta);
		
		virtual void setAlpha(float alpha);
		virtual void compositeAlpha(float alpha);
		virtual float getAlpha();
		
		virtual void setColor(const Color& color);
		virtual void compositeColor(const Color& color);
		virtual const Color& getColor();
		
		virtual void setTintColor(const Color& color);
		virtual void compositeTintColor(const Color& color);
		virtual const Color& getTintColor();
		
		virtual void setClipRect(const RectangleF&clipRect);
		virtual const RectangleF& getClipRect();
	};
}
