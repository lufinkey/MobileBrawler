
#include "Font.h"
#include "../DataPacket.h"
#include <SDL_ttf.h>
#include <memory>

namespace GameLibrary
{
	int Font::styleToTTFStyle(byte style)
	{
		if(style == Font::STYLE_PLAIN)
		{
			return TTF_STYLE_NORMAL;
		}
		else
		{
			int stylemask = 0;
			if((style & Font::STYLE_BOLD) == Font::STYLE_BOLD)
			{
				stylemask = stylemask | TTF_STYLE_BOLD;
			}
			if((style & Font::STYLE_ITALIC) == Font::STYLE_ITALIC)
			{
				stylemask = stylemask | TTF_STYLE_ITALIC;
			}
			if((style & Font::STYLE_UNDERLINE) == Font::STYLE_UNDERLINE)
			{
				stylemask = stylemask | TTF_STYLE_UNDERLINE;
			}
			if((style & Font::STYLE_STRIKETHROUGH) == Font::STYLE_STRIKETHROUGH)
			{
				stylemask = stylemask | TTF_STYLE_STRIKETHROUGH;
			}
			return stylemask;
		}
	}

	void* Font::loadFontSize(unsigned int size)
	{
		DataPacket& fontDataPacket = *fontdata.get();
		SDL_RWops* ops = SDL_RWFromConstMem(fontDataPacket.getData(), fontDataPacket.size());
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
		unsigned int total = sizeList.size();
		for(unsigned int i=0; i<total; i++)
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

	Font::Font()
	{
		if(!TTF_WasInit())
		{
			if(TTF_Init() < 0)
			{
				//TODO replace with more specific exception type
				throw Exception(TTF_GetError());
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
	}

	bool Font::loadFromFile(const String&path, unsigned int defaultsize, String&error)
	{
		mlock.lock();
		DataPacket* fontDataPacket = new DataPacket();
		if(!fontDataPacket->loadFromFile(path, error))
		{
			delete fontDataPacket;
			mlock.unlock();
			return false;
		}

		SDL_RWops* ops = SDL_RWFromConstMem(fontDataPacket->getData(), fontDataPacket->size());
		if(ops == nullptr)
		{
			error = SDL_GetError();
			delete fontDataPacket;
			mlock.unlock();
			return false;
		}

		TTF_Font* loadedfont = TTF_OpenFontRW(ops,0,defaultsize);
		if(loadedfont == nullptr)
		{
			error = TTF_GetError();
			if(SDL_RWclose(ops) != 0)
			{
				error = (String)"1: " + error + '\n' + "2: " + SDL_GetError();
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

	ArrayList<RenderedGlyphContainer::RenderedGlyph> Font::getRenderedGlyphs(const String&text, void*renderer)
	{
		if(fontdata!=nullptr)
		{
			mlock.lock();
			ArrayList<RenderedGlyphContainer::RenderedGlyph> renderedGlyphs;
			try
			{
				if(size>36)
				{
					renderedGlyphs = glyphs.getRenderedGlyphs(getFontPtr(size),renderer,size,style,text,antialiasing);
				}
				else
				{
					renderedGlyphs = glyphs.getRenderedGlyphs(getFontPtr(36),renderer,36,style,text,antialiasing);
				}
			}
			catch(const Exception&e)
			{
				//TODO replace with more specific exception type
				mlock.unlock();
				throw Exception(e);
			}
			mlock.unlock();
			return renderedGlyphs;
		}
		return ArrayList<RenderedGlyphContainer::RenderedGlyph>();
	}

	Vector2u Font::measureString(const String&text)
	{
		mlock.lock();
		if(fontdata == nullptr || fontsizes == nullptr)
		{
			mlock.unlock();
			return Vector2u(0,0);
		}
		TTF_Font* font = (TTF_Font*)getFontPtr(size);
		TTF_SetFontStyle(font, styleToTTFStyle(style));
		int w = 0;
		int h = 0;
		if(TTF_SizeText(font, text, &w, &h) < 0)
		{
			mlock.unlock();
			//TODO replace with more specific exception type
			throw Exception(TTF_GetError());
		}
		mlock.unlock();
		return Vector2u((unsigned int)w, (unsigned int)h);
	}

	void Font::setStyle(byte s)
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

	byte Font::getStyle()
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
