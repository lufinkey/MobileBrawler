
#pragma once

#include "Color.h"
#include "../Types.h"
#include "../Utilities/Geometry/Rectangle.h"
#include "../Utilities/Geometry/Transform.h"

namespace GameLibrary
{
	/*! Handles drawing to a Window object*/
	class Graphics
	{
		friend class Application;
		friend class Font;
		friend class TextureImage;
		friend class Window;
	public:
		/*! copy constructor; When a Graphics object is copied, all transformations are cloned, and the new Graphics object can be transformed independently*/
		Graphics(const Graphics&);
		/*! virtual destructor*/
		virtual ~Graphics();
		/*! assignment operator*/
		Graphics& operator=(const Graphics&);
		
		
		/*! Gets the default Graphics font.
			\returns a Font pointer*/
		static Font*getDefaultFont();
		/*! Sets the path to load the default Font. This function should be called before Application::initialize() is called. Otherwise, it will have no effect.*/
		static void setDefaultFontPath(const String&path);
		
		
		/*! Rotates the graphics by the given amount.
			\param degrees the amount, in degrees, to rotate the Graphics*/
		virtual void rotate(float degrees);
		/*! Rotates the graphics by the given amount at the given origin.
			\param degrees the amount, in degrees, to rotate the Graphics
			\param x the x coordinate of the origin of the rotation
			\param y the y coordinate of the origin of the rotation*/
		virtual void rotate(float degrees, float x, float y);
		/*! Rotates the graphics by the given amount at the given origin.
			\param degrees the amount, in degrees, to rotate the Graphics
			\param center the origin of the rotation*/
		virtual void rotate(float degrees, const Vector2f&center);
		

		/*! Scales the graphics by the given amount.
			\param scaleX the ratio to scale the graphics along the x axis
			\param scaleY the ratio to scale the graphics along the y axis*/
		virtual void scale(float scaleX, float scaleY);
		/*! Scales the graphics by the given amount.
			\param factors the ratio to scale the graphics along the x and y axis*/
		virtual void scale(const Vector2f& factors);
		/*! Scales the graphics by the given amount at the given origin.
			\param scaleX the ratio to scale the graphics along the x axis
			\param scaleY the ratio to scale the graphics along the y axis
			\param originX the x coordinate of the origin of the scaling
			\param originY the y coordinate of the origin of the scaling*/
		virtual void scale(float scaleX, float scaleY, float originX, float originY);
		/*! Scales the graphics by the given amount at the given origin.
			\param factors the ratio to scale the graphics along the x and y axis
			\param origin the origin of the scaling*/
		virtual void scale(const Vector2f& factors, const Vector2f& origin);
		
		
		/*! Translates the graphics by the given amount.
			\param x the amount, along the x axis, to translate
			\param y the amount, along the y axis, to translate*/
		virtual void translate(float x, float y);
		/*! Translates the graphics by the givem amount.
			\param delta the amount, along the x and y axis, to translate*/
		virtual void translate(const Vector2f&delta);
		
		
		/*! Gets the current transformation of the Graphics
			\returns a TransformF object*/
		virtual TransformF getTransform() const;
		
		
		/*! Sets the alpha (transparency) of the Graphics.
			\param alpha the alpha value, from 0 (fully transparent) to 255 (fully visible)*/
		virtual void setAlpha(byte alpha);
		/*! Composites the alpha (transparency) of the Graphics. this->alpha *= (alpha/255);
			\param alpha the alpha value to composite, from 0 (fully transparent) to 255 (fully visible)*/
		virtual void compositeAlpha(byte alpha);
		/*! Gets the current alpha value.
			\returns an unsigned byte value*/
		virtual byte getAlpha() const;
		
		
		/*! Sets the Color that the graphics draws with.
			\param color the drawing color for the graphics*/
		virtual void setColor(const Color&color);
		/*! Composites the current drawing Color. \see Color::composite(const Color&)const
			\param comp the color to composite on the current drawing color*/
		virtual void compositeColor(const Color&comp);
		/*! Gets the current drawing color.
			\returns a const Color reference*/
		virtual const Color& getColor() const;
		
		
		/*! Sets the tinting Color of the graphics.
		This value is independent from Graphics::compositeColor(const Color&) and creates a composited Color on each draw operation.
			\param tint the Color to use to tint drawing operations*/
		virtual void setTintColor(const Color&tint);
		/*! Composites the current tinting Color. \see Color::composite(const Color&)const
			\param compTint the color to composite on the current tinting color*/
		virtual void compositeTintColor(const Color&compTint);
		/*! Gets the current tinting color.
			\returns a const Color reference*/
		virtual const Color& getTintColor() const;
		
		
		/*! Sets the font used to draw strings.
			\param font the font to use for string drawing*/
		virtual void setFont(Font*font);
		/*! Gets the font being used to draw strings.
			\returns a Font pointer*/
		virtual Font* getFont() const;
		
		
		/*! Sets the clipping region for draw operations.
			\param x the x coordinate of the clipping rectangle
			\param y the x coordinate of the clipping rectangle
			\param width the width of the clipping rectangle
			\param height the height of the clipping rectangle*/
		virtual void setClipRect(float x, float y, float width, float height);
		/*! Sets the clipping region for draw operations.
			\param rect the clipping rectangle*/
		virtual void setClipRect(const RectangleF&rect);
		/*! Clips the current clipping region further using another clipping region.
			\param rect the clipping rectangle*/
		virtual void clip(const RectangleF&rect);
		/*! Gets the current clipping rectangle.
			\returns a const RectangleF reference*/
		virtual const RectangleF& getClipRect();
		
		
		/*! Draws a string to the Window.
			\param text the string of text to draw
			\param x the x coordinate of the bottom left of the string
			\param y the y coordinate of the bottom left of the string*/
		void drawString(const String&text, float x, float y);
		/*! Draws a string to the Window.
			\param text the string of text to draw
			\param point the coordinates of the bottom left of the string*/
		void drawString(const String&text, const Vector2f& point);
		
		
		/*! Draws a line to the Window.
			\param x1 the x coordinate of the starting point of the line
			\param y1 the y coordinate of the starting point of the line
			\param x2 the x coordinate of the ending point of the line
			\param y2 the y coordinate of the ending point of the line*/
		void drawLine(float x1,float y1,float x2,float y2);
		/*! Draws a line to the Window.
			\param point1 the coordinates of the starting point of the line
			\param point2 the coordinates of the ending point of the line*/
		void drawLine(const Vector2f& point1, const Vector2f& point2);
		
		
		/*! Draws a rectangle outline to the Window.
			\param x the x coordinate of the rectangle
			\param y the y coordinate of the rectangle
			\param width the width of the rectangle
			\param height the height of the rectangle*/
		void drawRect(float x,float y,float width,float height);
		/*! Draws a rectangle outline to the Window.
			\param rect the rectangle to draw*/
		void drawRect(const RectangleF& rect);
		
		
		/*! Draws a filled rectangle to the Window.
			\param x the x coordinate of the rectangle
			\param y the y coordinate of the rectangle
			\param width the width of the rectangle
			\param height the height of the rectangle*/
		void fillRect(float x,float y,float width,float height);
		/*! Draws a filled rectangle to the Window.
			\param rect the rectangle to draw*/
		void fillRect(const RectangleF& rect);
		
		
		//void drawOval(float x1,float y1,float w,float h);
		//void drawOval(const RectangleF& rect);

		//void fillOval(float x1,float y1,float w,float h);
		//void fillOval(const RectangleF& rect);
		
		void drawPolygon(const PolygonF&polygon);
		//void fillPolygon(const PolygonF&polygon);
		
		
		/*! Draws a TextureImage to the Window.
			\param img the TextureImage to draw
			\param x the x coordinate of the TextureImage
			\param y the y coordinate of the TextureImage*/
		void drawImage(TextureImage*img, float x, float y);
		/*! Draws a TextureImage to the Window.
			\param img the TextureImage to draw
			\param point the (x,y) coordinate to draw the TextureImage*/
		void drawImage(TextureImage*img, const Vector2f& point);
		/*! Draws a TextureImage to the Window.
			\param img the TextureImage to draw
			\param x the x coordinate of the TextureImage
			\param y the y coordinate of the TextureImage*/
		void drawImage(TextureImage*img, float x, float y, float width, float height);
		/*! Draws a TextureImage to the Window.
			\param img the TextureImage to draw
			\param rect the destination rectangle to draw the TextureImage*/
		void drawImage(TextureImage*img, const RectangleF& rect);
		/*! Draws a TextureImage to the Window.
			\param img the TextureImage to draw
			\param dx1 the x coordinate of the top left of the destination rectangle to draw the TextureImage
			\param dy1 the y coordinate of the top left of the destination rectangle to draw the TextureImage
			\param dx2 the x coordinate of the bottom right of the destination rectangle to draw the TextureImage
			\param dy2 the y coordinate of the bottom right of the destination rectangle to draw the TextureImage
			\param sx1 the x coordinate of the top left of the source rectangle inside the TextureImage
			\param sy1 the y coordinate of the top left of the source rectangle inside the TextureImage
			\param sx2 the x coordinate of the bottom right of the source rectangle inside the TextureImage
			\param sy2 the y coordinate of the bottom right of the source rectangle inside the TextureImage*/
		void drawImage(TextureImage*img, float dx1, float dy1, float dx2, float dy2, unsigned int sx1, unsigned int sy1, unsigned int sx2, unsigned int sy2);
		/*! Draws a TextureImage to the Window.
			\param img the TextureImage to draw
			\param dst the destination rectangle to draw the TextureImage
			\param src the source rectangle inside the TextureImage*/
		void drawImage(TextureImage*img, const RectangleF& dst, const RectangleI& src);
		
	protected:
		/*! Clears the Window render and resets all the properties of the Graphics*/
		void reset(const Color&clearColor = Color::WHITE);
		
		/*! Constructs a Graphics object to draw to a given Window*/
		Graphics(Window&window);
		
		/*! Called internally to begin a drawing operation.
		To create a custom drawing operation, beginDraw() should be called before the operation, and endDraw() should be called when the operation finishes.*/
		void beginDraw();
		/*! Called internally to end a drawing operation.
		To create a custom drawing operation, beginDraw() should be called before the operation, and endDraw() should be called when the operation finishes.*/
		void endDraw();
		
	private:
		Window*window;
		void*renderer;

		Color color;
		Color tintColor;
		byte alpha;
		
		Font*font;
		static Font*defaultFont;
		static String defaultFontPath;

		TextureImage*pixel;
		
		RectangleF cliprect;
		Vector2f clipoffset;

		float rotation;
		Vector2f scaling;
		
		TransformF transform;

		bool derived;
	};
}
