
#include "Font.h"
#include "../DataPacket.h"
#include <SDL_ttf.h>
#include <memory>

namespace GameLibrary
{
	int Font::styleToTTFStyle(int fontstyle)
	{
		if(fontstyle == Font::STYLE_PLAIN)
		{
			return TTF_STYLE_NORMAL;
		}
		else
		{
			int stylemask = 0;
			if((fontstyle & Font::STYLE_BOLD) == Font::STYLE_BOLD)
			{
				stylemask = stylemask | TTF_STYLE_BOLD;
			}
			if((fontstyle & Font::STYLE_ITALIC) == Font::STYLE_ITALIC)
			{
				stylemask = stylemask | TTF_STYLE_ITALIC;
			}
			if((fontstyle & Font::STYLE_UNDERLINE) == Font::STYLE_UNDERLINE)
			{
				stylemask = stylemask | TTF_STYLE_UNDERLINE;
			}
			if((fontstyle & Font::STYLE_STRIKETHROUGH) == Font::STYLE_STRIKETHROUGH)
			{
				stylemask = stylemask | TTF_STYLE_STRIKETHROUGH;
			}
			return stylemask;
		}
	}

	void* Font::loadFontSize(unsigned int size)
	{
		DataPacket& fontDataPacket = *fontdata.get();
		SDL_RWops* ops = SDL_RWFromConstMem(fontDataPacket.getData(), (int)fontDataPacket.size());
		if(ops == nullptr)
		{
			return nullptr;
		}
		TTF_Font* loadedfont = TTF_OpenFontRW(ops,0,size);
		if(loadedfont == nullptr)
		{
			return nullptr;
		}
		return (void*)loadedfont;
	}

	void* Font::getFontPtr(unsigned int size)
	{
		FontSizeList& sizeList = *fontsizes.get();
		size_t total = sizeList.size();
		for(size_t i=0; i<total; i++)
		{
			const Pair<unsigned int, void*>& fontSize = sizeList.get(i);
			if(fontSize.first == size)
			{
				return fontSize.second;
			}
		}

		void* fontsizeptr = loadFontSize(size);
		if(fontsizeptr != nullptr)
		{
			sizeList.add(Pair<unsigned int, void*>(size, fontsizeptr));
		}
		return fontsizeptr;
	}

	void Font::clearFontSizes()
	{
		if(fontsizes.get()!=nullptr)
		{
			FontSizeList& sizeList = *fontsizes.get();
			for(unsigned int i=0; i<sizeList.size(); i++)
			{
				Pair<unsigned int, void*>& fontSize = sizeList.get(i);
				TTF_Font* fontSizeData = (TTF_Font*)fontSize.second;
				TTF_CloseFont(fontSizeData);
				fontSize.second = nullptr;
			}
			sizeList.clear();
		}
	}

	Font::Font()
	{
		if(!TTF_WasInit())
		{
			if(TTF_Init() < 0)
			{
				throw InitializeLibraryException("SDL_ttf", TTF_GetError());
			}
		}

		size = 0;
		style = STYLE_PLAIN;
		fontdata = nullptr;
		antialiasing = false;
	}

	Font::Font(const Font&font)
	{
		font.mlock.lock();
		size = font.size;
		style = font.style;
		antialiasing = font.antialiasing;
		fontdata = font.fontdata;
		fontsizes = font.fontsizes;
		font.mlock.unlock();
	}

	Font::~Font()
	{
		clearFontSizes();
		for(unsigned int i=0; i<glyphs.size(); i++)
		{
			delete glyphs.get(i).first;
		}
		glyphs.clear();
	}
	
	Font& Font::operator=(const Font&font)
	{
		mlock.lock();
		
		clearFontSizes();
		for(unsigned int i=0; i<glyphs.size(); i++)
		{
			delete glyphs.get(i).first;
		}
		glyphs.clear();

		font.mlock.lock();
		size = font.size;
		style = font.style;
		antialiasing = font.antialiasing;
		fontdata = font.fontdata;
		fontsizes = font.fontsizes;
		font.mlock.unlock();
		mlock.unlock();
		
		return *this;
	}

	bool Font::loadFromFile(const String&path, unsigned int defaultsize, String*error)
	{
		mlock.lock();
		DataPacket* fontDataPacket = new DataPacket();
		if(!fontDataPacket->loadFromFile(path, error))
		{
			delete fontDataPacket;
			mlock.unlock();
			return false;
		}

		SDL_RWops* ops = SDL_RWFromConstMem(fontDataPacket->getData(), (int)fontDataPacket->size());
		if(ops == nullptr)
		{
			if(error!=nullptr)
			{
				*error = SDL_GetError();
			}
			delete fontDataPacket;
			mlock.unlock();
			return false;
		}

		TTF_Font* loadedfont = TTF_OpenFontRW(ops,0,defaultsize);
		if(loadedfont == nullptr)
		{
			if(error!=nullptr)
			{
				*error = TTF_GetError();
			}
			if(SDL_RWclose(ops) != 0)
			{
				if(error!=nullptr)
				{
					*error = (String)"" + *error + "\n" + SDL_GetError();
				}
			}
			delete fontDataPacket;
			mlock.unlock();
			return false;
		}

		size = defaultsize;
		style = Font::STYLE_PLAIN;
		antialiasing = false;
		glyphs.clear();
		fontdata = std::shared_ptr<DataPacket>(fontDataPacket);
		if(fontsizes != nullptr)
		{
			clearFontSizes();
			fontsizes = nullptr;
		}
		FontSizeList* sizeList = new FontSizeList();
		fontsizes = std::shared_ptr<FontSizeList>(sizeList);
		sizeList->add(Pair<unsigned int, void*>(defaultsize, (void*)loadedfont));
		mlock.unlock();
		return true;
	}

	RenderedGlyphContainer* Font::getRenderedGlyphContainer(void*renderer)
	{
		for(unsigned int i=0; i<glyphs.size(); i++)
		{
			Pair<RenderedGlyphContainer*, void*>& container = glyphs.get(i);
			if(container.second == renderer)
			{
				return container.first;
			}
		}
		Pair<RenderedGlyphContainer*, void*> container;
		container.first = new RenderedGlyphContainer();
		container.second = renderer;
		glyphs.add(container);
		return container.first;
	}

	ArrayList<RenderedGlyphContainer::RenderedGlyph> Font::getRenderedGlyphs(const GlyphString&text, void*renderer)
	{
		if(fontdata!=nullptr)
		{
			mlock.lock();
			RenderedGlyphContainer* container = getRenderedGlyphContainer(renderer);
			ArrayList<RenderedGlyphContainer::RenderedGlyph> renderedGlyphs;
			try
			{
				if(size>36)
				{
					renderedGlyphs = container->getRenderedGlyphs(getFontPtr(size),renderer,size,style,text,antialiasing);
				}
				else
				{
					renderedGlyphs = container->getRenderedGlyphs(getFontPtr(36),renderer,36,style,text,antialiasing);
				}
			}
			catch(const RenderGlyphException&e)
			{
				mlock.unlock();
				throw RenderGlyphException(e);
			}
			mlock.unlock();
			return renderedGlyphs;
		}
		return ArrayList<RenderedGlyphContainer::RenderedGlyph>();
	}
	
	Vector2u Font::measureString(const String& text)
	{
		return measureString((GlyphString)text);
	}
	
	Vector2u Font::measureString(const WideString& text)
	{
		return measureString((GlyphString)text);
	}

	Vector2u Font::measureString(const GlyphString& text)
	{
		mlock.lock();
		if(fontdata == nullptr || fontsizes == nullptr)
		{
			mlock.unlock();
			return Vector2u(0,0);
		}
		TTF_Font* font = (TTF_Font*)getFontPtr(size);
		TTF_SetFontStyle(font, styleToTTFStyle(style));
		int descent = TTF_FontDescent(font);
		int totalWidth = 0;
		int totalHeight = 0;
		for(unsigned int i=0; i<text.length(); i++)
		{
			int w = 0;
			int h = 0;
			glyph_char str[2];
			str[0] = text.charAt(i);
			str[1] = NULL;
			if(TTF_SizeUNICODE(font, str, &w, &h) < 0)
			{
				mlock.unlock();
				//TODO replace with more specific exception type
				throw Exception(TTF_GetError());
			}
			if(h > totalHeight)
			{
				totalHeight = h;
			}
			totalWidth += w;
		}
		int fixedHeight = totalHeight - descent;
		if(fixedHeight < 0)
		{
			fixedHeight = 0;
		}
		mlock.unlock();
		return Vector2u((unsigned int)totalWidth, (unsigned int)fixedHeight);
	}

	void Font::setStyle(int s)
	{
		mlock.lock();
		style = s;
		mlock.unlock();
	}

	void Font::setSize(unsigned int s)
	{
		mlock.lock();
		size = s;
		mlock.unlock();
	}

	void Font::setAntialiasing(bool toggle)
	{
		mlock.lock();
		antialiasing = toggle;
		mlock.unlock();
	}

	int Font::getStyle()
	{
		return style;
	}

	unsigned int Font::getSize()
	{
		return size;
	}

	bool Font::getAntialiasing()
	{
		return antialiasing;
	}
}
