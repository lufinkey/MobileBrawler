
#include "Graphics.h"
#include "TextureImage.h"
#include "../IO/Console.h"
#include "../Utilities/Font/Font.h"
#include "../Utilities/Math.h"
#include "../Utilities/PlatformChecks.h"
#include "../Window/Window.h"
#include <SDL.h>

namespace GameLibrary
{
	/*typedef struct
	{
		SDL_GLContext context;
	} GameLibrary_ContextData;*/
	
	Font* Graphics::defaultFont = nullptr;
	
	void Graphics::reset(const Color&clearColor)
	{
		setColor(Color::BLACK);
		setTintColor(Color::WHITE);
		setAlpha(255);
		
		setFont(defaultFont);
		
		transform.reset();
		rotation = 0;
		scaling.x = 1;
		scaling.y = 1;
		
		clipoffset.x = 0;
		clipoffset.y = 0;
		
		SDL_SetRenderDrawColor((SDL_Renderer*)renderer, clearColor.r,clearColor.g,clearColor.b,clearColor.a);
		SDL_RenderClear((SDL_Renderer*)renderer);
		SDL_SetRenderDrawColor((SDL_Renderer*)renderer, 0,0,0,255);
		
		float zoom = window->view->zoom;
		
		if(window->view == nullptr || window->view->matchWindow)
		{
			const Vector2u& winSz = window->getSize();
			Vector2f winSize = Vector2f((float)winSz.x, (float)winSz.y);
			if(window->view != nullptr)
			{
				window->view->setSize((float)winSz.x, (float)winSz.y);
			}
			
			setClipRect(0, 0, (float)winSz.x, (float)winSz.y);
			
			float difX = (winSize.x - (winSize.x*zoom))/(2*zoom);
			float difY = (winSize.y - (winSize.y*zoom))/(2*zoom);
			
			scale(zoom,zoom);
			translate(difY, difX);
		}
		else if(window->view->letterboxed)
		{
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
			
			float letterBoxW = (winSize.x - fixedWidth)/2;
			float letterBoxH = (winSize.y - fixedHeight)/2;
			
			setColor(Color::BLACK);
			if(letterBoxW>0)
			{
				fillRect(0,0,letterBoxW,winSize.y);
				fillRect(letterBoxW+fixedWidth,0,letterBoxW,winSize.y);
			}
			if(letterBoxH>0)
			{
				fillRect(0,0,winSize.x,letterBoxH);
				fillRect(0,letterBoxH+fixedHeight,winSize.x,letterBoxH);
			}
			clipoffset.x = letterBoxW;
			clipoffset.y = letterBoxH;
			setClipRect(0,0,fixedWidth, fixedHeight);

			float scaleVal = zoom*multScale;

			scale(scaleVal,scaleVal);
			translate(difX, difY);
		}
		else
		{
			Vector2u winSz = window->getSize();
			Vector2f winSize = Vector2f((float)winSz.x, (float)winSz.y);
			Vector2f viewSize = window->view->getSize();
			setClipRect(0, 0, (float)winSz.x, (float)winSz.y);

			float ratX = winSize.x /viewSize.x;
			float ratY = winSize.y /viewSize.y;

			float difX = (winSize.x - (winSize.x*zoom))/(2*zoom*ratX);
			float difY = (winSize.y - (winSize.y*zoom))/(2*zoom*ratY);

			scale(zoom*ratX, zoom*ratY);
			translate(difX,difY);
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
			defaultFont->setAntialiasing(true);
		}
		font = defaultFont;
		
		if(win.view == nullptr || win.view->matchWindow)
		{
			const Vector2u& winSize = win.getSize();
			cliprect = RectangleF(0, 0, (float)winSize.x, (float)winSize.y);
		}
		clipoffset = Vector2f(0,0);
		
		transform = Transform();
		rotation = 0;
		scaling.x = 1;
		scaling.y = 1;
		
		derived = false;
		
		pixel = new TextureImage();
		pixel->create(1,1,*this);
		Color pixelColor = Color::WHITE;
		pixel->update(&pixelColor);
		
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
		pixel = g.pixel;
		cliprect = g.cliprect;
		clipoffset = g.clipoffset;
		transform = g.transform;
		rotation = g.rotation;
		scaling = g.scaling;
	}
	
	Graphics::~Graphics()
	{
		if(!derived)
		{
			delete font;
			delete pixel;
			SDL_DestroyRenderer((SDL_Renderer*)renderer);
		}
	}

	Graphics& Graphics::operator=(const Graphics&g)
	{
		window = g.window;
		renderer = g.renderer;
		color = g.color;
		tintColor = g.tintColor;
		alpha = g.alpha;
		font = g.font;
		pixel = g.pixel;
		cliprect = g.cliprect;
		clipoffset = g.clipoffset;
		transform = g.transform;
		rotation = g.rotation;
		scaling = g.scaling;

		return *this;
	}

	void Graphics::beginDraw()
	{
		float clipLeft = (clipoffset.x + cliprect.x);
		float clipTop = (clipoffset.y + cliprect.y);
		float clipRight = clipLeft + cliprect.width;
		float clipBottom = clipTop + cliprect.height;

		SDL_Rect clip;
		clip.x = (int)clipLeft;
		clip.y = (int)clipTop;
		clip.w = (int)(clipRight - (float)clip.x);
		clip.h = (int)(clipBottom - (float)clip.y);

		Color colorComp = color.composite(tintColor);
		byte newAlpha = (byte)((float)colorComp.a * ((float)alpha/255));

		SDL_RenderSetClipRect((SDL_Renderer*)renderer, &clip);
		SDL_SetRenderDrawColor((SDL_Renderer*)renderer, colorComp.r, colorComp.g, colorComp.b, newAlpha);

		//glPushMatrix();
		//glLoadMatrixf(transform.getMatrix());
	}

	void Graphics::endDraw()
	{
		//glPopMatrix();
		
		SDL_SetRenderDrawColor((SDL_Renderer*)renderer, 0,0,0,255);
		SDL_RenderSetClipRect((SDL_Renderer*)renderer, nullptr);
	}

	Font* Graphics::getDefaultFont()
	{
		return defaultFont;
	}
	
	void Graphics::rotate(float degrees)
	{
		transform.rotate(degrees);
		rotation += degrees;
	}

	void Graphics::rotate(float degrees, float x, float y)
	{
		transform.rotate(degrees,x,y);
		rotation += degrees;
	}

	void Graphics::rotate(float degrees, const Vector2f&center)
	{
		rotate(degrees, center.x, center.y);
	}
	
	void Graphics::scale(float scaleX, float scaleY)
	{
		transform.scale(scaleX,scaleY);
		scaling.x *= scaleX;
		scaling.y *= scaleY;
	}
	
	void Graphics::scale(const Vector2f& factors)
	{
		scale(factors.x, factors.y);
	}
	
	void Graphics::scale(float scaleX, float scaleY, float originX, float originY)
	{
		transform.scale(scaleX,scaleY, originX, originY);
		scaling.x *= scaleX;
		scaling.y *= scaleY;
	}

	void Graphics::scale(const Vector2f& factors, const Vector2f& origin)
	{
		scale(factors.x, factors.y, origin.x, origin.y);
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
		cliprect = cr;
	}
	
	void Graphics::clip(const RectangleF&cr)
	{
		RectangleF trueCR = transform.transform(cr);
		trueCR.x -= clipoffset.x;
		trueCR.y -= clipoffset.y;
		cliprect = cliprect.getIntersect(trueCR);
	}

	const RectangleF& Graphics::getClipRect()
	{
		return cliprect;
	}

	void Graphics::drawString(const String&text, float x1, float y1)
	{
		ArrayList<RenderedGlyphContainer::RenderedGlyph> glyphs = font->getRenderedGlyphs(text,renderer);
		Vector2u dimensions = font->measureString(text);
		unsigned int fontSize = font->getSize();
		Color compColor = color.composite(tintColor);
		float alphaMult = (float)alpha / 255;
		
		float y1_top = y1 - (float)dimensions.y;
		float x_offset = 0;
		for(unsigned int i = 0; i < glyphs.size(); i++)
		{
			RenderedGlyphContainer::RenderedGlyph& glyph = glyphs.get(i);
			float mult = (float)fontSize/(float)glyph.size;
			SDL_Texture*texture = (SDL_Texture*)glyph.texture;
			Vector2u glyphDimensions = font->measureString(text.charAt(i));
			unsigned int format = 0;
			int access = 0;
			int w = 0;
			int h = 0;
			SDL_QueryTexture(texture, &format, &access, &w, &h);
			float realWidth = (float)w*mult;
			float realHeight = (float)h*mult;
			
			Vector2f pnt = transform.transform(Vector2f(x1 + x_offset, y1_top));
			
			SDL_Rect rect;
			rect.x = (int)pnt.x;
			rect.y = (int)pnt.y;
			rect.w = (int)(realWidth*scaling.x);
			rect.h = (int)(realHeight*scaling.y);
			
			SDL_Point center;
			center.x = 0;
			center.y = 0;
			
			beginDraw();
			
			SDL_SetTextureColorMod(texture, compColor.r, compColor.g, compColor.b);
			SDL_SetTextureAlphaMod(texture, (byte)(compColor.a * alphaMult));
			
			SDL_RenderCopyEx((SDL_Renderer*)renderer, (SDL_Texture*)glyph.texture, nullptr, &rect, rotation, &center, SDL_FLIP_NONE);
			
			SDL_SetTextureColorMod(texture, 255,255,255);
			SDL_SetTextureAlphaMod(texture, 255);
			
			endDraw();
			
			x_offset += glyphDimensions.x;
		}
	}
	
	void Graphics::drawString(const String&text, const Vector2f& point)
	{
		drawString(text, point.x, point.y);
	}
	
	void Graphics::drawLine(float x1, float y1, float x2, float y2)
	{
		Vector2f pnt1 = transform.transform(Vector2f(x1, y1));
		Vector2f pnt2 = transform.transform(Vector2f(x2, y2));
		
		beginDraw();
		
		SDL_RenderDrawLine((SDL_Renderer*)renderer, (int)pnt1.x, (int)pnt1.y, (int)pnt2.x, (int)pnt2.y);
		
		endDraw();
	}
	
	void Graphics::drawLine(const Vector2f& point1, const Vector2f& point2)
	{
		drawLine(point1.x, point1.y, point2.x, point2.y);
	}

	void Graphics::drawRect(float x, float y, float width, float height)
	{
		float right = x+width;
		float bottom = y+height;
		Vector2f topleft = transform.transform(Vector2f(x, y));
		Vector2f topright = transform.transform(Vector2f(right, y));
		Vector2f bottomright = transform.transform(Vector2f(right, bottom));
		Vector2f bottomleft = transform.transform(Vector2f(x, bottom));

		beginDraw();

		SDL_RenderDrawLine((SDL_Renderer*)renderer, (int)topleft.x, (int)topleft.y, (int)topright.x, (int)topright.y);
		SDL_RenderDrawLine((SDL_Renderer*)renderer, (int)topright.x, (int)topright.y, (int)bottomright.x, (int)bottomright.y);
		SDL_RenderDrawLine((SDL_Renderer*)renderer, (int)bottomleft.x, (int)bottomleft.y, (int)bottomright.x, (int)bottomright.y);
		SDL_RenderDrawLine((SDL_Renderer*)renderer, (int)topleft.x, (int)topleft.y, (int)bottomleft.x, (int)bottomleft.y);

		endDraw();
	}

	void Graphics::drawRect(const RectangleF& rect)
	{
		drawRect(rect.x, rect.y, rect.width, rect.height);
	}

	void Graphics::fillRect(float x, float y, float width, float height)
	{
		Vector2f pnt = transform.transform(Vector2f(x, y));
		
		float rectLeft = pnt.x;
		float rectTop = pnt.y;
		
		SDL_Rect rect;
		rect.x = (int)rectLeft;
		rect.y = (int)rectTop;
		rect.w = (int)(((x+width) - (float)((int)x))*scaling.x);
		rect.h = (int)(((y+height) - (float)((int)y))*scaling.y);
		
		SDL_Point center;
		center.x = 0;
		center.y = 0;
		
		Color compColor = color.composite(tintColor);
		
		beginDraw();
		
		float alphaMult = (float)alpha/255;
		SDL_SetTextureColorMod((SDL_Texture*)pixel->texture, compColor.r, compColor.g, compColor.b);
		SDL_SetTextureAlphaMod((SDL_Texture*)pixel->texture, (byte)(compColor.a * alphaMult));
		
		SDL_RenderCopyEx((SDL_Renderer*)renderer, (SDL_Texture*)pixel->texture, nullptr, &rect, rotation, &center, SDL_FLIP_NONE);
		
		SDL_SetTextureColorMod((SDL_Texture*)pixel->texture, 255,255,255);
		SDL_SetTextureAlphaMod((SDL_Texture*)pixel->texture, 255);
		
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
	
	void Graphics::drawPolygon(const Polygon& polygon)
	{
		Polygon transformedPolygon = transform.transform(polygon);
		
		const ArrayList<Vector2f>& points = transformedPolygon.getPoints();
		if(points.size() > 0)
		{
			beginDraw();
			
			if(points.size() == 1)
			{
				const Vector2f& point = points.get(0);
				SDL_RenderDrawPoint((SDL_Renderer*)renderer, (int)point.x, (int)point.y);
			}
			else
			{
				for(unsigned int i=0; i<points.size(); i++)
				{
					const Vector2f& point = points.get(i);
					if(i == (points.size()-1))
					{
						const Vector2f& startPoint = points.get(0);
						SDL_RenderDrawLine((SDL_Renderer*)renderer, (int)point.x, (int)point.y, (int)startPoint.x, (int)startPoint.y);
					}
					else
					{
						const Vector2f& nextPoint = points.get(i+1);
						SDL_RenderDrawLine((SDL_Renderer*)renderer, (int)point.x, (int)point.y, (int)nextPoint.x, (int)nextPoint.y);
					}
				}
			}
			
			endDraw();
		}
	}
	
	/*void Graphics::fillPolygon(const Polygon& polygon)
	{
		//
	}*/
	
	void Graphics::drawImage(TextureImage*img, float x, float y)
	{
		SDL_Texture*texture = (SDL_Texture*)img->texture;
		unsigned int texWidth = img->getWidth();
		unsigned int texHeight = img->getHeight();

		float dx1 = x;
		float dy1 = y;
		float dx2 = x+((float)texWidth);
		float dy2 = y+((float)texHeight);
		drawImage(img, dx1,dy1,dx2,dy2, 0,0,texWidth,texHeight);
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
		
		float dx1 = x;
		float dy1 = y;
		float dx2 = x+width;
		float dy2 = y+height;
		drawImage(img, dx1,dy1,dx2,dy2, 0,0,texWidth,texHeight);
	}

	void Graphics::drawImage(TextureImage*img, const RectangleF& rect)
	{
		drawImage(img, rect.x, rect.y, rect.width, rect.height);
	}

	void Graphics::drawImage(TextureImage*img, float dx1, float dy1, float dx2, float dy2, unsigned int sx1, unsigned int sy1, unsigned int sx2, unsigned int sy2)
	{
		SDL_Texture*texture = (SDL_Texture*)img->texture;
		unsigned int texWidth = img->width;
		unsigned int texHeight = img->height;
		if(texWidth != 0 && texHeight != 0)
		{
			SDL_Rect srcrect;
			srcrect.x = (int)sx1;
			srcrect.y = (int)sy1;
			srcrect.w = (int)(sx2 - sx1);
			srcrect.h = (int)(sy2 - sy1);

			Vector2f pnt1 = transform.transform(Vector2f(dx1, dy1));

			SDL_Rect dstrect;
			dstrect.x = (int)pnt1.x;
			dstrect.y = (int)pnt1.y;
			dstrect.w = (int)((dx2 - (float)((int)dx1))*scaling.x);
			dstrect.h = (int)((dy2 - (float)((int)dy1))*scaling.y);

			SDL_Point center;
			center.x = 0;
			center.y = 0;

			beginDraw();

			float alphaMult = (float)alpha/255;
			SDL_SetTextureColorMod(texture, tintColor.r, tintColor.g, tintColor.b);
			SDL_SetTextureAlphaMod(texture, (byte)(tintColor.a * alphaMult));

			SDL_RenderCopyEx((SDL_Renderer*)renderer, texture, &srcrect, &dstrect, rotation, &center, SDL_FLIP_NONE);

			SDL_SetTextureColorMod(texture, 255,255,255);
			SDL_SetTextureAlphaMod(texture, 255);

			endDraw();
		}
	}

	void Graphics::drawImage(TextureImage*img, const RectangleF& dst, const RectangleI& src)
	{
		drawImage(img, dst.x, dst.y, dst.x+dst.width, dst.y+dst.height, src.x, src.y, src.x+src.width, src.y+src.height);
	}
}
