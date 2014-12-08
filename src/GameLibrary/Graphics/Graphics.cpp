
#include "Graphics.h"
#include "TextureImage.h"
#include "../IO/Console.h"
#include "../Utilities/Font/Font.h"
#include "../Utilities/Math.h"
#include "../Utilities/PlatformChecks.h"
#include "../Window/Window.h"
#include <SDL.h>

#if defined(TARGETPLATFORM_MOBILE)
	#include <SDL_opengles.h>
	#include <SDL_opengles2.h>
#else
	#include <SDL_opengl.h>
#endif

namespace GameLibrary
{
	typedef struct
	{
		SDL_GLContext context;
	} GameLibrary_ContextData;

	Font* Graphics::defaultFont = nullptr;

	void Graphics::reset()
	{
		setColor(Color::BLACK);
		setTintColor(Color::WHITE);
		setAlpha(255);

		setFont(defaultFont);

		transform.reset();

		clipOffset.x = 0;
		clipOffset.y = 0;

		SDL_SetRenderDrawColor((SDL_Renderer*)renderer, 255,255,255,255);
		SDL_RenderClear((SDL_Renderer*)renderer);
		SDL_SetRenderDrawColor((SDL_Renderer*)renderer, 0,0,0,255);

		if(window->view == nullptr || window->view->matchWindow)
		{
			const Vector2u& winSz = window->getSize();
			if(window->view != nullptr)
			{
				window->view->setSize((float)winSz.x, (float)winSz.y);
			}

			setClipRect(0, 0, (float)winSz.x, (float)winSz.y);

			setColor(Color::WHITE);
			fillRect(0, 0, (float)winSz.x, (float)winSz.y);
			setColor(Color::BLACK);
		}
		else if(window->view->letterboxed)
		{
			float zoom = 1;
			float multScale = 1;
			Vector2u winSz = window->getSize();
			Vector2f winSize = Vector2f((float)winSz.x, (float)winSz.y);
			Vector2f viewSize = window->view->getSize();
			setClipRect(0, 0, (float)winSz.x, (float)winSz.y);

			float ratX = winSize.x /viewSize.x;
			float ratY = winSize.y /viewSize.y;
			if(ratX<ratY)
			{
				multScale = ratX;
			}
			else
			{
				multScale = ratY;
			}

			float fixedWidth = viewSize.x*multScale;
			float fixedHeight = viewSize.y*multScale;

			float difX = ((winSize.x - (winSize.x*zoom))+(winSize.x - fixedWidth))/(2*zoom*multScale);
			float difY = ((winSize.y - (winSize.y*zoom))+(winSize.y - fixedHeight))/(2*zoom*multScale);

			float letterBoxW = Math::abs((winSize.x - fixedWidth)/2);
			float letterBoxH = Math::abs((winSize.y - fixedHeight)/2);

			setColor(Color::BLACK);
			if(letterBoxW>0)
			{
				fillRect(0,0,letterBoxW,winSize.y);
				fillRect(letterBoxW+fixedWidth,0,letterBoxW,winSize.y);
			}
			if(letterBoxH > 0)
			{
				fillRect(0,0,winSize.x,letterBoxH);
				fillRect(0,letterBoxH+fixedHeight,winSize.x,letterBoxH);
			}
			clipOffset.x = letterBoxW;
			clipOffset.y = letterBoxH;
			scale(zoom*multScale,zoom*multScale);
			translate(difX, difY);
		}
	}

	Graphics::Graphics(Window&win)
	{
		if(win.windowdata == nullptr)
		{
			//TODO replace with more specific exception type
			throw Exception("Cannot create Graphics object for window that is not created");
		}
		window = &win;
		renderer = (void*)SDL_CreateRenderer((SDL_Window*)win.windowdata,-1,SDL_RENDERER_ACCELERATED);
		if(renderer==nullptr)
		{
			//TODO replace with more specific exception type
			throw Exception(SDL_GetError());
		}

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
		clipOffset = Vector2f(0,0);

		transform = Transform();

		derived = false;

		//contextdata = (void*)(new GameLibrary_ContextData());
		//((GameLibrary_ContextData*)contextdata)->context = SDL_GL_CreateContext((SDL_Window*)win.windowdata);

		reset();
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
		clipOffset = g.clipOffset;
		transform = g.transform;
	}

	Graphics::~Graphics()
	{
		if(!derived)
		{
			delete font;
			//SDL_GL_DeleteContext(((GameLibrary_ContextData*)contextdata)->context);
			//delete ((GameLibrary_ContextData*)contextdata);
			SDL_DestroyRenderer((SDL_Renderer*)renderer);
		}
	}

	void Graphics::beginDraw()
	{
		SDL_Rect clip;
		clip.x = (int)(clipOffset.x + clipRect.x);
		clip.y = (int)(clipOffset.y + clipRect.y);
		clip.w = (int)clipRect.width;
		clip.h = (int)clipRect.height;

		Color colorComp = color.composite(tintColor);
		byte newAlpha = (byte)((float)colorComp.a * ((float)alpha/255));

		SDL_RenderSetClipRect((SDL_Renderer*)renderer, &clip);
		SDL_SetRenderDrawColor((SDL_Renderer*)renderer, colorComp.r, colorComp.g, colorComp.b, newAlpha);

		//SDL_GL_MakeCurrent((SDL_Window*)window->windowdata, ((GameLibrary_ContextData*)contextdata)->context);
		glPushMatrix();
		glLoadMatrixf(transform.getMatrix());
	}

	void Graphics::endDraw()
	{
		glPopMatrix();
		
		SDL_SetRenderDrawColor((SDL_Renderer*)renderer, 0,0,0,255);
		SDL_RenderSetClipRect((SDL_Renderer*)renderer, nullptr);
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

	void Graphics::setFont(Font*f)
	{
		font = f;
	}

	Font*Graphics::getFont()
	{
		return font;
	}

	void Graphics::setClipRect(float x, float y, float width, float height)
	{
		setClipRect(RectangleF(x,y,width,height));
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

		beginDraw();

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
			SDL_SetTextureAlphaMod(texture, (byte)(compColor.a * alphaMult));

			SDL_RenderCopy((SDL_Renderer*)renderer, (SDL_Texture*)glyph.texture, NULL, &rect);

			SDL_SetTextureColorMod(texture, 255,255,255);
			SDL_SetTextureAlphaMod(texture, 255);

			x_offset += realWidth;
		}

		endDraw();
	}

	void Graphics::drawString(const String&text, const Vector2f& point)
	{
		drawString(text, point.x, point.y);
	}

	void Graphics::drawLine(float x1, float y1, float x2, float y2)
	{
		beginDraw();

		SDL_RenderDrawLine((SDL_Renderer*)renderer, (int)x1, (int)y1, (int)x2, (int)y2);

		endDraw();
	}

	void Graphics::drawLine(const Vector2f& point1, const Vector2f& point2)
	{
		drawLine(point1.x, point1.y, point2.x, point2.y);
	}

	void Graphics::drawRect(float x, float y, float width, float height)
	{
		beginDraw();

		SDL_Rect rect;
		rect.x = (int)x;
		rect.y = (int)y;
		rect.w = (int)width;
		rect.h = (int)height;

		SDL_RenderDrawRect((SDL_Renderer*)renderer, &rect);

		endDraw();
	}

	void Graphics::drawRect(const RectangleF& rect)
	{
		drawRect(rect.x, rect.y, rect.width, rect.height);
	}

	void Graphics::fillRect(float x, float y, float width, float height)
	{
		beginDraw();

		SDL_Rect rect;
		rect.x = (int)x;
		rect.y = (int)y;
		rect.w = (int)width;
		rect.h = (int)height;

		SDL_RenderFillRect((SDL_Renderer*)renderer, &rect);

		endDraw();
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

	void Graphics::drawImage(TextureImage*img, float x, float y)
	{
		SDL_Texture*texture = (SDL_Texture*)img->texture;
		unsigned int texWidth = img->width;
		unsigned int texHeight = img->height;
		if(texWidth != 0 && texHeight != 0)
		{
			SDL_Rect srcrect;
			srcrect.x = 0;
			srcrect.y = 0;
			srcrect.w = texWidth;
			srcrect.h = texHeight;

			SDL_Rect dstrect;
			dstrect.x = (int)x;
			dstrect.y = (int)y;
			dstrect.w = (int)texWidth;
			dstrect.h = (int)texHeight;

			SDL_Point center;
			center.x = 0;
			center.y = 0;

			beginDraw();

			float alphaMult = (float)alpha/255;
			SDL_SetTextureColorMod(texture, tintColor.r, tintColor.g, tintColor.b);
			SDL_SetTextureAlphaMod(texture, (byte)(tintColor.a * alphaMult));

			SDL_RenderCopyEx((SDL_Renderer*)renderer, texture, &srcrect, &dstrect, 0, &center, SDL_FLIP_NONE);

			SDL_SetTextureColorMod(texture, 255,255,255);
			SDL_SetTextureAlphaMod(texture, 255);

			endDraw();
		}
	}

	void Graphics::drawImage(TextureImage*img, const Vector2f& point)
	{
		drawImage(img, point.x, point.y);
	}

	void Graphics::drawImage(TextureImage*img, float x, float y, float width, float height)
	{
		SDL_Texture*texture = (SDL_Texture*)img->texture;
		unsigned int texWidth = img->width;
		unsigned int texHeight = img->height;
		if(texWidth != 0 && texHeight != 0)
		{
			SDL_Rect srcrect;
			srcrect.x = 0;
			srcrect.y = 0;
			srcrect.w = (int)texWidth;
			srcrect.h = (int)texHeight;

			SDL_Rect dstrect;
			dstrect.x = (int)x;
			dstrect.y = (int)y;
			dstrect.w = (int)width;
			dstrect.h = (int)height;

			SDL_Point center;
			center.x = 0;
			center.y = 0;

			beginDraw();

			float alphaMult = (float)alpha/255;
			SDL_SetTextureColorMod(texture, tintColor.r, tintColor.g, tintColor.b);
			SDL_SetTextureAlphaMod(texture, (byte)(tintColor.a * alphaMult));

			SDL_RenderCopyEx((SDL_Renderer*)renderer, texture, &srcrect, &dstrect, 0, &center, SDL_FLIP_NONE);

			SDL_SetTextureColorMod(texture, 255,255,255);
			SDL_SetTextureAlphaMod(texture, 255);

			endDraw();
		}
	}

	void Graphics::drawImage(TextureImage*img, const RectangleF& rect)
	{
		drawImage(img, rect.x, rect.y, rect.width, rect.height);
	}

	void Graphics::drawImage(TextureImage*img, float dx1, float dy1, float dx2, float dy2, int sx1, int sy1, int sx2, int sy2)
	{
		SDL_Texture*texture = (SDL_Texture*)img->texture;
		unsigned int texWidth = img->width;
		unsigned int texHeight = img->height;
		if(texWidth != 0 && texHeight != 0)
		{
			SDL_Rect srcrect;
			srcrect.x = sx1;
			srcrect.y = sy1;
			srcrect.w = sx2 - sx1;
			srcrect.h = sy2 - sy1;

			float w = dx2 - dx1;
			float h = dy2 - dy1;

			SDL_Rect dstrect;
			dstrect.x = (int)dx1;
			dstrect.y = (int)dy1;
			dstrect.w = (int)w;
			dstrect.h = (int)h;

			SDL_Point center;
			center.x = 0;
			center.y = 0;

			beginDraw();

			float alphaMult = (float)alpha/255;
			SDL_SetTextureColorMod(texture, tintColor.r, tintColor.g, tintColor.b);
			SDL_SetTextureAlphaMod(texture, (byte)(tintColor.a * alphaMult));

			SDL_RenderCopyEx((SDL_Renderer*)renderer, texture, &srcrect, &dstrect, 0, &center, SDL_FLIP_NONE);

			SDL_SetTextureColorMod(texture, 255,255,255);
			SDL_SetTextureAlphaMod(texture, 255);

			endDraw();
		}
	}

	void Graphics::drawImage(TextureImage*img, const RectangleF& dst, const Rectangle& src)
	{
		drawImage(img, dst.x, dst.y, dst.x+dst.width, dst.y+dst.height, src.x, src.y, src.x+src.width, src.y+src.height);
	}
}
