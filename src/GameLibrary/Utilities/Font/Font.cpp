
#include "Font.h"
#include "../DataPacket.h"
#include <memory>
#include <SDL_ttf.h>

namespace GameLibrary
{
	typedef ArrayList<Pair<unsigned int, void*>> FontSizeList;

	FontSizeList& Font_getSizeList(void* fontsizes)
	{
		return *(((std::shared_ptr<FontSizeList>*)fontsizes)->get());
	}

	const FontSizeList& Font_getConstSizeList(void* fontsizes)
	{
		return *(((const std::shared_ptr<FontSizeList>*)fontsizes)->get());
	}

	void* Font::loadFontSize(unsigned int size)
	{
		DataPacket& fontDataPacket = *(((std::shared_ptr<DataPacket>*)fontdata)->get());
		SDL_RWops* ops = SDL_RWFromConstMem(fontDataPacket.getData(), fontDataPacket.size());
		if(ops == NULL)
		{
			return NULL;
		}
		TTF_Font* loadedfont = TTF_OpenFontRW(ops,0,size);
		if(loadedfont == NULL)
		{
			return NULL;
		}
		return (void*)loadedfont;
	}

	void* Font::getFontPtr(unsigned int size)
	{
		FontSizeList& sizeList = Font_getSizeList(fontsizes);
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
		if(fontsizeptr != NULL)
		{
			sizeList.add(Pair<unsigned int, void*>(size, fontsizeptr));
		}
		return fontsizeptr;
	}

	void Font::clearFontSizes()
	{
		FontSizeList& sizeList = Font_getSizeList(fontsizes);
		for(unsigned int i=0; i<sizeList.size(); i++)
		{
			Pair<unsigned int, void*>& fontSize = sizeList.get(i);
			TTF_Font* fontSizeData = (TTF_Font*)fontSize.second;
			TTF_CloseFont(fontSizeData);
			fontSize.second = NULL;
		}
		sizeList.clear();
	}

	Font::Font()
	{
		size = 0;
		style = STYLE_PLAIN;
		fontdata = NULL;
		fontsizes = NULL;
		antialiasing = false;
	}

	Font::Font(const Font&font)
	{
		font.mlock.lock();
		size = font.size;
		style = font.style;
		antialiasing = font.antialiasing;
		if(font.fontdata!=NULL)
		{
			std::shared_ptr<DataPacket>*font_fontdata = (std::shared_ptr<DataPacket>*)font.fontdata;
			fontdata = (void*)(new std::shared_ptr<DataPacket>(*font_fontdata));
		}
		if(font.fontsizes != NULL)
		{
			std::shared_ptr<FontSizeList>*font_fontsizes = (std::shared_ptr<FontSizeList>*)font.fontsizes;
			fontsizes = (void*)(new std::shared_ptr<FontSizeList>(*font_fontsizes));
		}
		font.mlock.unlock();
	}

	Font::~Font()
	{
		if(fontdata!=NULL)
		{
			std::shared_ptr<DataPacket>* fontData_ptr = (std::shared_ptr<DataPacket>*)fontdata;
			delete fontData_ptr;
		}
		if(fontsizes != NULL)
		{
			clearFontSizes();
			std::shared_ptr<FontSizeList>* sizeList = (std::shared_ptr<FontSizeList>*)fontsizes;
			delete sizeList;
			fontsizes = NULL;
		}
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
		if(ops == NULL)
		{
			error = SDL_GetError();
			delete fontDataPacket;
			mlock.unlock();
			return false;
		}

		TTF_Font* loadedfont = TTF_OpenFontRW(ops,0,defaultsize);
		if(loadedfont == NULL)
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
		if(fontdata != NULL)
		{
			std::shared_ptr<DataPacket>*old_fontdata = (std::shared_ptr<DataPacket>*)fontdata;
			delete old_fontdata;
			fontdata = NULL;
		}
		fontdata = (void*)(new std::shared_ptr<DataPacket>(fontDataPacket));
		if(fontsizes != NULL)
		{
			clearFontSizes();
			std::shared_ptr<FontSizeList>*old_fontsizes = (std::shared_ptr<FontSizeList>*)fontsizes;
			delete old_fontsizes;
			fontsizes = NULL;
		}
		FontSizeList* sizeList = new FontSizeList();
		fontsizes = (void*)(new std::shared_ptr<FontSizeList>(sizeList));
		sizeList->add(Pair<unsigned int, void*>(defaultsize, (void*)loadedfont));

		mlock.unlock();
		return true;
	}

	ArrayList<RenderedGlyphContainer::RenderedGlyph> Font::getRenderedGlyphs(const String&text, void*renderer)
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
}
