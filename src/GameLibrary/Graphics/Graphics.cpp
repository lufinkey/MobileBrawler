
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
	String Graphics::defaultFontPath = "fonts/arial.ttf";
	
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
		
		SDL_RenderSetViewport((SDL_Renderer*)renderer, nullptr);
		
		if(window->view != nullptr && window->view->matchWindow)
		{
			const Vector2u& winSz = window->getSize();
			window->view->setSize((double)winSz.x, (double)winSz.y);
		}
		
		if(window->view != nullptr && window->view->maintainResolution)
		{
			if((renderTarget_width!=(unsigned int)window->view->size.x) || (renderTarget_height!=(unsigned int)window->view->size.y))
			{
				if(renderTarget!=nullptr)
				{
					SDL_DestroyTexture((SDL_Texture*)renderTarget);
					renderTarget = nullptr;
				}
				renderTarget_width = (unsigned int)window->view->size.x;
				renderTarget_height = (unsigned int)window->view->size.y;
				renderTarget = SDL_CreateTexture((SDL_Renderer*)renderer, SDL_PIXELFORMAT_RGBA8888, SDL_TEXTUREACCESS_TARGET, (int)renderTarget_width, (int)renderTarget_height);
				if(renderTarget==nullptr)
				{
					renderTarget_width = 0;
					renderTarget_height = 0;
					Console::writeErrorLine("Unable to create texture for render target");
				}
				else
				{
					SDL_SetRenderTarget((SDL_Renderer*)renderer, (SDL_Texture*)renderTarget);
				}
			}
			else
			{
				SDL_SetRenderTarget((SDL_Renderer*)renderer, (SDL_Texture*)renderTarget);
			}
		}
		else
		{
			if(renderTarget!=nullptr)
			{
				renderTarget_width = 0;
				renderTarget_height = 0;
				SDL_SetRenderTarget((SDL_Renderer*)renderer, nullptr);
				SDL_DestroyTexture((SDL_Texture*)renderTarget);
			}
		}
		
		SDL_SetRenderDrawColor((SDL_Renderer*)renderer, clearColor.r,clearColor.g,clearColor.b,clearColor.a);
		SDL_RenderClear((SDL_Renderer*)renderer);
		SDL_SetRenderDrawColor((SDL_Renderer*)renderer, 0,0,0,255);
		
		double zoom = 1;
		if(window->view!=nullptr)
		{
			zoom = window->view->zoom;
		}
		
		if(window->view!=nullptr && window->view->maintainResolution && renderTarget!=nullptr)
		{
			setClipRect(0, 0, renderTarget_width, renderTarget_height);
			Vector2d winSize((double)renderTarget_width, (double)renderTarget_height);
			double difX = (winSize.x - (winSize.x*zoom))/(2*zoom);
			double difY = (winSize.y - (winSize.y*zoom))/(2*zoom);
			scale(zoom, zoom);
			translate(difY, difX);
		}
		else if(window->view == nullptr || window->view->matchWindow)
		{
			const Vector2u& winSz = window->getSize();
			Vector2d winSize = Vector2d((double)winSz.x, (double)winSz.y);
			if(window->view != nullptr)
			{
				window->view->setSize((double)winSz.x, (double)winSz.y);
			}
			
			setClipRect(0, 0, (double)winSz.x, (double)winSz.y);
			
			double difX = (winSize.x - (winSize.x*zoom))/(2*zoom);
			double difY = (winSize.y - (winSize.y*zoom))/(2*zoom);
			
			scale(zoom,zoom);
			translate(difY, difX);
		}
		else if(window->view->letterboxed)
		{
			double multScale = 1;
			Vector2u winSz = window->getSize();
			Vector2d winSize = Vector2d((double)winSz.x, (double)winSz.y);
			Vector2d viewSize = window->view->getSize();
			setClipRect(0, 0, (double)winSz.x, (double)winSz.y);
			
			double ratX = winSize.x /viewSize.x;
			double ratY = winSize.y /viewSize.y;
			if(ratX<ratY)
			{
				multScale = ratX;
			}
			else
			{
				multScale = ratY;
			}
			
			double fixedWidth = viewSize.x*multScale;
			double fixedHeight = viewSize.y*multScale;
			
			double difX = ((winSize.x - (winSize.x*zoom))+(winSize.x - fixedWidth))/(2*zoom*multScale);
			double difY = ((winSize.y - (winSize.y*zoom))+(winSize.y - fixedHeight))/(2*zoom*multScale);
			
			double letterBoxW = (winSize.x - fixedWidth)/2;
			double letterBoxH = (winSize.y - fixedHeight)/2;
			
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

			double scaleVal = zoom*multScale;

			scale(scaleVal,scaleVal);
			translate(difX, difY);
		}
		else
		{
			Vector2u winSz = window->getSize();
			Vector2d winSize = Vector2d((double)winSz.x, (double)winSz.y);
			Vector2d viewSize = window->view->getSize();
			setClipRect(0, 0, (double)winSz.x, (double)winSz.y);
			
			double ratX = winSize.x /viewSize.x;
			double ratY = winSize.y /viewSize.y;

			double difX = (winSize.x - (winSize.x*zoom))/(2*zoom*ratX);
			double difY = (winSize.y - (winSize.y*zoom))/(2*zoom*ratY);

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
		renderTarget = nullptr;
		renderTarget_width = 0;
		renderTarget_height = 0;
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
			bool success = defaultFont->loadFromFile(defaultFontPath, 24, &error);
			if(!success)
			{
				Console::writeLine("\""+defaultFontPath+"\": "+error);
			}
			defaultFont->setAntialiasing(true);
		}
		font = defaultFont;
		
		if(win.view == nullptr || win.view->matchWindow)
		{
			const Vector2u& winSize = win.getSize();
			cliprect = RectangleD(0, 0, (double)winSize.x, (double)winSize.y);
		}
		clipoffset = Vector2d(0,0);
		
		transform = TransformD();
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
		renderTarget = g.renderTarget;
		renderTarget_width = g.renderTarget_width;
		renderTarget_height = g.renderTarget_height;
		renderTarget_height = 0;
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
			if(renderTarget!=nullptr)
			{
				SDL_SetRenderTarget((SDL_Renderer*)renderer, nullptr);
				SDL_DestroyTexture((SDL_Texture*)renderTarget);
			}
			SDL_DestroyRenderer((SDL_Renderer*)renderer);
		}
	}

	/*Graphics& Graphics::operator=(const Graphics&g)
	{
		window = g.window;
		renderer = g.renderer;
		renderTarget = g.renderTarget;
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
	}*/

	void Graphics::beginDraw()
	{
		double clipLeft = (clipoffset.x + cliprect.x);
		double clipTop = (clipoffset.y + cliprect.y);
		double clipRight = clipLeft + cliprect.width;
		double clipBottom = clipTop + cliprect.height;
		
		SDL_Rect clip;
		clip.x = (int)clipLeft;
		clip.y = (int)clipTop;
		clip.w = (int)(clipRight - (double)clip.x);
		clip.h = (int)(clipBottom - (double)clip.y);
		
		Color colorComp = color.composite(tintColor);
		byte newAlpha = (byte)((double)colorComp.a * ((double)alpha/255));
		
		SDL_RenderSetClipRect((SDL_Renderer*)renderer, &clip);
		SDL_SetRenderDrawColor((SDL_Renderer*)renderer, colorComp.r, colorComp.g, colorComp.b, newAlpha);
		
		//SDL_GLContext context = SDL_RendererGetGLContext((SDL_Renderer*)renderer);
		//SDL_GL_MakeCurrent((SDL_Window*)window->windowdata, context);
		//glPushMatrix();
		//glRotatef(1.0f,1.0f,1.0f,1.0f);
	}

	void Graphics::endDraw()
	{
		//SDL_GLContext context = SDL_RendererGetGLContext((SDL_Renderer*)renderer);
		//SDL_GL_MakeCurrent((SDL_Window*)window->windowdata, context);
		//glPopMatrix();
		
		SDL_SetRenderDrawColor((SDL_Renderer*)renderer, 0,0,0,255);
		SDL_RenderSetClipRect((SDL_Renderer*)renderer, nullptr);
	}

	Font* Graphics::getDefaultFont()
	{
		if(defaultFont == nullptr)
		{
			defaultFont = new Font();
			String error;
			bool success = defaultFont->loadFromFile(defaultFontPath, 24, &error);
			if(!success)
			{
				Console::writeLine(error);
			}
			defaultFont->setAntialiasing(true);
		}
		return defaultFont;
	}
	
	void Graphics::setDefaultFontPath(const String&path)
	{
		defaultFontPath = path;
	}
	
	void Graphics::rotate(double degrees)
	{
		transform.rotate(degrees);
		rotation += degrees;
	}

	void Graphics::rotate(double degrees, double x, double y)
	{
		transform.rotate(degrees,x,y);
		rotation += degrees;
	}

	void Graphics::rotate(double degrees, const Vector2d&center)
	{
		rotate(degrees, center.x, center.y);
	}
	
	void Graphics::scale(double scaleX, double scaleY)
	{
		transform.scale(scaleX,scaleY);
		scaling.x *= scaleX;
		scaling.y *= scaleY;
	}
	
	void Graphics::scale(const Vector2d& factors)
	{
		scale(factors.x, factors.y);
	}
	
	void Graphics::scale(double scaleX, double scaleY, double originX, double originY)
	{
		transform.scale(scaleX,scaleY, originX, originY);
		scaling.x *= scaleX;
		scaling.y *= scaleY;
	}

	void Graphics::scale(const Vector2d& factors, const Vector2d& origin)
	{
		scale(factors.x, factors.y, origin.x, origin.y);
	}
		
	void Graphics::translate(double x, double y)
	{
		transform.translate(x, y);
	}

	void Graphics::translate(const Vector2d&delta)
	{
		translate(delta.x, delta.y);
	}
	
	TransformD Graphics::getTransform() const
	{
		return transform;
	}
	
	void Graphics::setAlpha(byte a)
	{
		alpha = a;
	}

	void Graphics::compositeAlpha(byte a)
	{
		double mult = ((double)a)/255;
		alpha = (byte)(((double)alpha)*mult);
	}

	byte Graphics::getAlpha() const
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

	const Color& Graphics::getColor() const
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

	const Color& Graphics::getTintColor() const
	{
		return tintColor;
	}

	void Graphics::setFont(Font*f)
	{
		font = f;
	}

	Font* Graphics::getFont() const
	{
		return font;
	}

	void Graphics::setClipRect(double x, double y, double width, double height)
	{
		setClipRect(RectangleD(x,y,width,height));
	}
	
	void Graphics::setClipRect(const RectangleD&cr)
	{
		cliprect = cr;
	}
	
	void Graphics::clip(const RectangleD&cr)
	{
		RectangleD trueCR = transform.transform(cr);
		trueCR.x -= clipoffset.x;
		trueCR.y -= clipoffset.y;
		cliprect = cliprect.getIntersect(trueCR);
	}
	
	const RectangleD& Graphics::getClipRect()
	{
		return cliprect;
	}
	
	void Graphics::drawString(const String& text, double x1, double y1)
	{
		drawString((WideString)text, x1, y1);
	}
	
	void Graphics::drawString(const String&text, const Vector2d& point)
	{
		drawString((WideString)text, point.x, point.y);
	}
	
	void Graphics::drawString(const WideString& text, double x1, double y1)
	{
		ArrayList<RenderedGlyphContainer::RenderedGlyph> glyphs = font->getRenderedGlyphs((Font::GlyphString)text,renderer);
		Vector2u dimensions = font->measureString(text);
		unsigned int fontSize = font->getSize();
		Color compColor = color.composite(tintColor);
		double alphaMult = (double)alpha / 255;
		
		double y1_top = y1 - (double)dimensions.y;
		double x_offset = 0;
		for(unsigned int i = 0; i < glyphs.size(); i++)
		{
			RenderedGlyphContainer::RenderedGlyph& glyph = glyphs.get(i);
			double mult = (double)fontSize/(double)glyph.size;
			SDL_Texture*texture = (SDL_Texture*)glyph.texture;
			Vector2u glyphDimensions = font->measureString((Font::GlyphString)text.charAt(i));
			unsigned int format = 0;
			int access = 0;
			int w = 0;
			int h = 0;
			SDL_QueryTexture(texture, &format, &access, &w, &h);
			double realWidth = (double)w*mult;
			double realHeight = (double)h*mult;
			
			Vector2d pnt = transform.transform(Vector2d(x1 + x_offset, y1_top));
			
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
	
	void Graphics::drawString(const WideString&text, const Vector2d& point)
	{
		drawString(text, point.x, point.y);
	}
	
	void Graphics::drawLine(double x1, double y1, double x2, double y2)
	{
		Vector2d pnt1 = transform.transform(Vector2d(x1, y1));
		Vector2d pnt2 = transform.transform(Vector2d(x2, y2));
		
		beginDraw();
		
		SDL_RenderDrawLine((SDL_Renderer*)renderer, (int)pnt1.x, (int)pnt1.y, (int)pnt2.x, (int)pnt2.y);
		
		endDraw();
	}
	
	void Graphics::drawLine(const Vector2d& point1, const Vector2d& point2)
	{
		drawLine(point1.x, point1.y, point2.x, point2.y);
	}

	void Graphics::drawRect(double x, double y, double width, double height)
	{
		double right = x+width;
		double bottom = y+height;
		Vector2d topleft = transform.transform(Vector2d(x, y));
		Vector2d topright = transform.transform(Vector2d(right, y));
		Vector2d bottomright = transform.transform(Vector2d(right, bottom));
		Vector2d bottomleft = transform.transform(Vector2d(x, bottom));

		beginDraw();
		
		SDL_RenderDrawLine((SDL_Renderer*)renderer, (int)topleft.x, (int)topleft.y, (int)topright.x, (int)topright.y);
		SDL_RenderDrawLine((SDL_Renderer*)renderer, (int)topright.x, (int)topright.y, (int)bottomright.x, (int)bottomright.y);
		SDL_RenderDrawLine((SDL_Renderer*)renderer, (int)bottomleft.x, (int)bottomleft.y, (int)bottomright.x, (int)bottomright.y);
		SDL_RenderDrawLine((SDL_Renderer*)renderer, (int)topleft.x, (int)topleft.y, (int)bottomleft.x, (int)bottomleft.y);

		endDraw();
	}

	void Graphics::drawRect(const RectangleD& rect)
	{
		drawRect(rect.x, rect.y, rect.width, rect.height);
	}

	void Graphics::fillRect(double x, double y, double width, double height)
	{
		Vector2d pnt = transform.transform(Vector2d(x, y));
		
		double rectLeft = pnt.x;
		double rectTop = pnt.y;
		
		SDL_Rect rect;
		rect.x = (int)rectLeft;
		rect.y = (int)rectTop;
		rect.w = (int)(rectLeft + (width*scaling.x) - (int)rectLeft);
		rect.h = (int)(rectTop + (height*scaling.y) - (int)rectTop);
		
		SDL_Point center;
		center.x = 0;
		center.y = 0;
		
		Color compColor = color.composite(tintColor);
		
		beginDraw();
		
		double alphaMult = (double)alpha/255;
		SDL_SetTextureColorMod((SDL_Texture*)pixel->texture, compColor.r, compColor.g, compColor.b);
		SDL_SetTextureAlphaMod((SDL_Texture*)pixel->texture, (byte)(compColor.a * alphaMult));
		
		SDL_RenderCopyEx((SDL_Renderer*)renderer, (SDL_Texture*)pixel->texture, nullptr, &rect, rotation, &center, SDL_FLIP_NONE);
		
		SDL_SetTextureColorMod((SDL_Texture*)pixel->texture, 255,255,255);
		SDL_SetTextureAlphaMod((SDL_Texture*)pixel->texture, 255);
		
		endDraw();
	}

	void Graphics::fillRect(const RectangleD& rect)
	{
		fillRect(rect.x, rect.y, rect.width, rect.height);
	}

	/*void Graphics::drawOval(double x1,double y1,double w,double h)
	{
		//
	}

	void Graphics::drawOval(const RectangleD& rect)
	{
		drawOval(rect.x, rect.y, rect.width, rect.height);
	}

	void Graphics::fillOval(double x1,double y1,double w,double h)
	{
		//
	}

	void Graphics::fillOval(const RectangleD& rect)
	{
		fillOval(rect.x, rect.y, rect.width, rect.height);
	}*/
	
	void Graphics::drawPolygon(const PolygonD& polygon)
	{
		PolygonD transformedPolygon = transform.transform(polygon);
		
		const ArrayList<Vector2d>& points = transformedPolygon.getPoints();
		if(points.size() > 0)
		{
			beginDraw();
			
			if(points.size() == 1)
			{
				const Vector2d& point = points.get(0);
				SDL_RenderDrawPoint((SDL_Renderer*)renderer, (int)point.x, (int)point.y);
			}
			else
			{
				for(unsigned int i=0; i<points.size(); i++)
				{
					const Vector2d& point = points.get(i);
					if(i == (points.size()-1))
					{
						const Vector2d& startPoint = points.get(0);
						SDL_RenderDrawLine((SDL_Renderer*)renderer, (int)point.x, (int)point.y, (int)startPoint.x, (int)startPoint.y);
					}
					else
					{
						const Vector2d& nextPoint = points.get(i+1);
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
	
	void Graphics::drawImage(TextureImage*img, double x, double y)
	{
		if(img==nullptr)
		{
			throw IllegalArgumentException("img", "cannot be null");
		}
		//SDL_Texture*texture = (SDL_Texture*)img->texture;
		unsigned int texWidth = img->getWidth();
		unsigned int texHeight = img->getHeight();

		double dx1 = x;
		double dy1 = y;
		double dx2 = x+((double)texWidth);
		double dy2 = y+((double)texHeight);
		drawImage(img, dx1,dy1,dx2,dy2, 0,0,texWidth,texHeight);
	}

	void Graphics::drawImage(TextureImage*img, const Vector2d& point)
	{
		drawImage(img, point.x, point.y);
	}

	void Graphics::drawImage(TextureImage*img, double x, double y, double width, double height)
	{
		if(img==nullptr)
		{
			throw IllegalArgumentException("img", "cannot be null");
		}
		//SDL_Texture*texture = (SDL_Texture*)img->texture;
		unsigned int texWidth = img->width;
		unsigned int texHeight = img->height;
		
		double dx1 = x;
		double dy1 = y;
		double dx2 = x+width;
		double dy2 = y+height;
		drawImage(img, dx1,dy1,dx2,dy2, 0,0,texWidth,texHeight);
	}

	void Graphics::drawImage(TextureImage*img, const RectangleD& rect)
	{
		drawImage(img, rect.x, rect.y, rect.width, rect.height);
	}
	
	void Graphics::drawImage(TextureImage*img, double dx1, double dy1, double dx2, double dy2, unsigned int sx1, unsigned int sy1, unsigned int sx2, unsigned int sy2)
	{
		if(img==nullptr)
		{
			throw IllegalArgumentException("img", "cannot be null");
		}
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
			
			Vector2d pnt1 = transform.transform(Vector2d(dx1, dy1));
			
			SDL_Rect dstrect;
			dstrect.x = (int)pnt1.x;
			dstrect.y = (int)pnt1.y;
			dstrect.w = (int)(pnt1.x+((dx2 - (double)((int)dx1))*scaling.x)-((int)dstrect.x));
			dstrect.h = (int)(pnt1.y+((dy2 - (double)((int)dy1))*scaling.y)-((int)dstrect.y));
			
			RectangleD dstrectBox((double)dstrect.x, (double)dstrect.y, (double)dstrect.w, (double)dstrect.h);
			RectangleD cliprectBox(clipoffset.x+cliprect.x, clipoffset.y+cliprect.y, cliprect.width, cliprect.height);
			if(!cliprectBox.intersects(dstrectBox))
			{
				return;
			}
			
			SDL_Point center;
			center.x = 0;
			center.y = 0;

			beginDraw();

			double alphaMult = (double)alpha/255;
			SDL_SetTextureColorMod(texture, tintColor.r, tintColor.g, tintColor.b);
			SDL_SetTextureAlphaMod(texture, (byte)(tintColor.a * alphaMult));

			SDL_RenderCopyEx((SDL_Renderer*)renderer, texture, &srcrect, &dstrect, rotation, &center, SDL_FLIP_NONE);

			SDL_SetTextureColorMod(texture, 255,255,255);
			SDL_SetTextureAlphaMod(texture, 255);

			endDraw();
		}
	}

	void Graphics::drawImage(TextureImage*img, const RectangleD& dst, const RectangleU& src)
	{
		drawImage(img, dst.x, dst.y, dst.x+dst.width, dst.y+dst.height, src.x, src.y, src.x+src.width, src.y+src.height);
	}
}
