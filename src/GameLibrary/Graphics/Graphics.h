
#include "Color.h"
#include "../Types.h"
#include "../Utilities/Geometry/Rectangle.h"
#include "../Utilities/Geometry/Transform.h"

#pragma once

namespace GameLibrary
{
	class Graphics
	{
		friend class Application;
		friend class Font;
		friend class TextureImage;
		friend class Window;
	private:
		Window*window;
		void*renderer;

		Color color;
		Color tintColor;
		byte alpha;
		
		Font*font;
		static Font*defaultFont;

		TextureImage*pixel;
		
		RectangleF clipRect;
		Vector2f clipOffset;

		float rotation;
		Vector2f scaling;
		
		Transform transform;

		bool derived;

	protected:
		void reset(const Color&clearColor = Color::WHITE);

		Graphics(Window&window);

		void beginDraw();
		void endDraw();
		
	public:
		Graphics(const Graphics&);
		virtual ~Graphics();

		Graphics& operator=(const Graphics&);

		static Font*getDefaultFont();
		
		virtual void rotate(float degrees);
		virtual void rotate(float degrees, float x, float y);
		virtual void rotate(float degrees, const Vector2f&center);
		
		virtual void scale(float scaleX, float scaleY);
		virtual void scale(const Vector2f& factors);
		
		virtual void translate(float x, float y);
		virtual void translate(const Vector2f&delta);
		
		virtual void setAlpha(byte);
		virtual void compositeAlpha(byte);
		virtual byte getAlpha();
		
		virtual void setColor(const Color&);
		virtual void compositeColor(const Color&);
		virtual const Color& getColor();
		
		virtual void setTintColor(const Color&);
		virtual void compositeTintColor(const Color&);
		virtual const Color& getTintColor();

		virtual void setFont(Font*);
		virtual Font*getFont();
		
		virtual void setClipRect(float x, float y, float width, float height);
		virtual void setClipRect(const RectangleF&);
		virtual const RectangleF& getClipRect();

		void drawString(const String&text, float x1, float y1);
		void drawString(const String&text, const Vector2f& point);

		void drawLine(float x1,float y1,float x2,float y2);
		void drawLine(const Vector2f& point1, const Vector2f& point2);

		void drawRect(float x,float y,float width,float height);
		void drawRect(const RectangleF& rect);

		void fillRect(float x,float y,float width,float height);
		void fillRect(const RectangleF& rect);

		//void drawOval(float x1,float y1,float w,float h);
		//void drawOval(const RectangleF& rect);

		//void fillOval(float x1,float y1,float w,float h);
		//void fillOval(const RectangleF& rect);

		void drawImage(TextureImage*img, float x, float y);
		void drawImage(TextureImage*img, const Vector2f& point);
		void drawImage(TextureImage*img, float x, float y, float width, float height);
		void drawImage(TextureImage*img, const RectangleF& rect);
		void drawImage(TextureImage*img, float dx1, float dy1, float dx2, float dy2, unsigned int sx1, unsigned int sy1, unsigned int sx2, unsigned int sy2);
		void drawImage(TextureImage*img, const RectangleF& dst, const Rectangle& src);
	};
}
