
#include "Graphics.h"
#include "../IO/Console.h"
#include "../Utilities/Font/Font.h"
#include "../Window/Window.h"
#include <SDL.h>

namespace GameLibrary
{
	Font* Graphics::defaultFont = nullptr;

	void Graphics::reset()
	{
		color = Color::BLACK;
		tintColor = Color::WHITE;
		alpha = 255;

		font = defaultFont;

		if(window->view == nullptr || window->view->matchWindow)
		{
			const Vector2u& winSize = window->getSize();
			clipRect = RectangleF(0, 0, (float)winSize.x, (float)winSize.y);
		}

		transform.reset();
	}

	Graphics::Graphics(Window&win)
	{
		if(win.windowdata == nullptr)
		{
			//TODO replace with more specific exception type
			throw Exception("Cannot create Graphics object for window that is not created");
		}
		window = &win;
		renderer = SDL_CreateRenderer((SDL_Window*)win.windowdata,-1,SDL_RENDERER_ACCELERATED);

		color = Color::BLACK;
		tintColor = Color::WHITE;
		alpha = 255;

		if(defaultFont == nullptr)
		{
			defaultFont = new Font();
			String error;
			bool success = defaultFont->loadFromFile("fonts/arial.ttf", 24, error);
			if(!success)
			{
				Console::writeLine(error);
			}
		}
		font = defaultFont;

		if(win.view == nullptr || win.view->matchWindow)
		{
			const Vector2u& winSize = win.getSize();
			clipRect = RectangleF(0, 0, (float)winSize.x, (float)winSize.y);
		}

		transform = Transform();

		derived = false;
	}

	Graphics::Graphics(const Graphics&g)
	{
		derived = true;
		window = g.window;
		renderer = g.renderer;
		color = g.color;
		tintColor = g.tintColor;
		alpha = g.alpha;
		font = g.font;
		clipRect = g.clipRect;
		transform = g.transform;
	}

	Graphics::~Graphics()
	{
		if(!derived)
		{
			SDL_DestroyRenderer((SDL_Renderer*)renderer);
			delete font;
		}
	}
	
	void Graphics::rotate(float degrees)
	{
		transform.rotate(degrees);
	}

	void Graphics::rotate(float degrees, float x, float y)
	{
		transform.rotate(degrees,x,y);
	}

	void Graphics::rotate(float degrees, const Vector2f&center)
	{
		rotate(degrees, center.x, center.y);
	}
		
	void Graphics::scale(float scaleX, float scaleY)
	{
		transform.scale(scaleX,scaleY);
	}

	void Graphics::scale(const Vector2f& factors)
	{
		scale(factors.x, factors.y);
	}
		
	void Graphics::translate(float x, float y)
	{
		transform.translate(x, y);
	}

	void Graphics::translate(const Vector2f&delta)
	{
		translate(delta.x, delta.y);
	}
		
	void Graphics::setAlpha(byte a)
	{
		alpha = a;
	}

	void Graphics::compositeAlpha(byte a)
	{
		float mult = ((float)a)/255;
		alpha = (byte)(((float)alpha)*mult);
	}

	byte Graphics::getAlpha()
	{
		return alpha;
	}
	
	void Graphics::setColor(const Color& c)
	{
		color = c;
	}

	void Graphics::compositeColor(const Color& c)
	{
		color = color.composite(c);
	}

	const Color& Graphics::getColor()
	{
		return color;
	}
	
	void Graphics::setTintColor(const Color& c)
	{
		tintColor = c;
	}

	void Graphics::compositeTintColor(const Color& c)
	{
		tintColor = tintColor.composite(c);
	}

	const Color& Graphics::getTintColor()
	{
		return color;
	}
	
	void Graphics::setClipRect(const RectangleF&cr)
	{
		clipRect = cr;
	}

	const RectangleF& Graphics::getClipRect()
	{
		return clipRect;
	}

	void Graphics::drawString(const String&text, float x1, float y1)
	{
		ArrayList<RenderedGlyphContainer::RenderedGlyph> glyphs = font->getRenderedGlyphs(text,renderer);
		Vector2u dimensions = font->measureString(text);
		unsigned int fontSize = font->getSize();
		Color compColor = color.composite(tintColor);
		float alphaMult = (float)alpha / 255;

		//TODO load opengl transform

		float y1_top = y1 - (float)fontSize;
		float x_offset = 0;
		for(unsigned int i = 0; i < glyphs.size(); i++)
		{
			RenderedGlyphContainer::RenderedGlyph& glyph = glyphs.get(i);
			float mult = (float)fontSize/(float)glyph.size;
			SDL_Texture*texture = (SDL_Texture*)glyph.texture;
			unsigned int format = 0;
			int access = 0;
			int w = 0;
			int h = 0;
			SDL_QueryTexture(texture, &format, &access, &w, &h);
			float realWidth = (float)w*mult;
			float realHeight = (float)h*mult;

			SDL_Rect rect;
			rect.x = (int)(x1 + x_offset);
			rect.y = (int)(y1_top);
			rect.w = (int)realWidth;
			rect.h = (int)realHeight;

			SDL_SetTextureColorMod(texture, compColor.r, compColor.g, compColor.b);
			SDL_SetTextureAlphaMod(texture, (byte)(color.a * alphaMult));

			SDL_RenderCopy((SDL_Renderer*)renderer, (SDL_Texture*)glyph.texture, NULL, &rect);

			SDL_SetTextureColorMod(texture, 255,255,255);
			SDL_SetTextureAlphaMod(texture, 255);

			x_offset += realWidth;
		}

		//TODO pop opengl transform
	}

	void Graphics::drawString(const String&text, const Vector2f& point)
	{
		drawString(text, point.x, point.y);
	}

	void Graphics::drawLine(float x1, float y1, float x2, float y2)
	{
		//
	}

	void Graphics::drawLine(const Vector2f& point1, const Vector2f& point2)
	{
		drawLine(point1.x, point1.y, point2.x, point2.y);
	}

	void Graphics::drawRect(float x1, float y1, float w, float h)
	{
		//
	}

	void Graphics::drawRect(const RectangleF& rect)
	{
		drawRect(rect.x, rect.y, rect.width, rect.height);
	}

	void Graphics::fillRect(float x1, float y1, float w, float h)
	{
		//
	}

	void Graphics::fillRect(const RectangleF& rect)
	{
		fillRect(rect.x, rect.y, rect.width, rect.height);
	}

	/*void Graphics::drawOval(float x1,float y1,float w,float h)
	{
		//
	}

	void Graphics::drawOval(const RectangleF& rect)
	{
		drawOval(rect.x, rect.y, rect.width, rect.height);
	}

	void Graphics::fillOval(float x1,float y1,float w,float h)
	{
		//
	}

	void Graphics::fillOval(const RectangleF& rect)
	{
		fillOval(rect.x, rect.y, rect.width, rect.height);
	}*/

	void Graphics::drawImage(BufferedImage*img, float x1, float y1)
	{
		//
	}

	void Graphics::drawImage(BufferedImage*img, const Vector2f& point)
	{
		drawImage(img, point.x, point.y);
	}

	void Graphics::drawImage(BufferedImage*img, float x1, float y1, float width, float height)
	{
		//
	}

	void Graphics::drawImage(BufferedImage*img, const RectangleF& rect)
	{
		drawImage(img, rect.x, rect.y, rect.width, rect.height);
	}

	void Graphics::drawImage(BufferedImage*img, float dx1, float dy1, float dx2, float dy2, int sx1, int sy1, int sx2, int sy2)
	{
		//
	}

	void Graphics::drawImage(BufferedImage*img, const RectangleF& dst, const Rectangle& src)
	{
		drawImage(img, dst.x, dst.y, dst.x+dst.width, dst.y+dst.height, src.x, src.y, src.x+src.width, src.y+src.height);
	}
}
