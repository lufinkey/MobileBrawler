
#include "RenderedGlyphContainer.h"
#include "Font.h"
#include <SDL_ttf.h>

namespace GameLibrary
{
	RenderedGlyphContainer::RenderedGlyphContainer()
	{
		//
	}
	
	RenderedGlyphContainer::~RenderedGlyphContainer()
	{
		clear();
	}
	
	void RenderedGlyphContainer::clear()
	{
		mlock.lock();
		for(size_t i=0; i<glyphs.size(); i++)
		{
			destroyGlyphStyles(glyphs.get(i).second);
		}
		glyphs.clear();
		mlock.unlock();
	}

	ArrayList<RenderedGlyphContainer::RenderedGlyph> RenderedGlyphContainer::getRenderedGlyphs(void*fontptr, void*renderer, unsigned int size, int fontstyle, const GlyphString&txt, bool antialiasing)
	{
		mlock.lock();
		ArrayList<RenderedGlyph> glyphTextures;
		int ttf_style = Font::styleToTTFStyle(fontstyle);
		TTF_SetFontStyle((TTF_Font*)fontptr, ttf_style);
		size_t length = txt.length();
		for(size_t i=0; i<length; i++)
		{
			try
			{
				glyphTextures.add(getGlyph(txt.charAt(i), fontptr, renderer, size, fontstyle, antialiasing));
			}
			catch(const RenderGlyphException&e)
			{
				mlock.unlock();
				throw RenderGlyphException(e);
			}
		}
		mlock.unlock();
		return glyphTextures;
	}
	
	RenderedGlyphContainer::RenderedGlyph RenderedGlyphContainer::getGlyph(glyph_char glyph, void*fontptr, void*renderer, unsigned int size, int fontstyle, bool antialiasing)
	{
		size_t index = ARRAYLIST_NOTFOUND;
		for(size_t i=0; i<glyphs.size(); i++)
		{
			if(glyphs.get(i).first == glyph)
			{
				index = i;
				i = glyphs.size();
			}
		}
		if(index == ARRAYLIST_NOTFOUND)
		{
			RenderedGlyphStyles* glyphStyles = new RenderedGlyphStyles();
			glyphs.add(Pair<glyph_char, RenderedGlyphStyles*>(glyph, glyphStyles));

			RenderedGlyph renderedGlyph = renderGlyph(glyph, fontptr, renderer, size, fontstyle, antialiasing);
			glyphStyles->styles.add(renderedGlyph);
			return renderedGlyph;
		}
		else
		{
			RenderedGlyphStyles* glyphStyles = glyphs.get(index).second;
			ArrayList<RenderedGlyph>& renderedGlyphs = glyphStyles->styles;
			RenderedGlyph renderedGlyph = findGlyph(renderedGlyphs, size, fontstyle, antialiasing);
			if(renderedGlyph.texture == nullptr)
			{
				renderedGlyph = renderGlyph(glyph, fontptr, renderer, size, fontstyle, antialiasing);
				glyphStyles->styles.add(renderedGlyph);
			}
			return renderedGlyph;
		}
	}

	RenderedGlyphContainer::RenderedGlyph RenderedGlyphContainer::findGlyph(const ArrayList<RenderedGlyph>&renderedGlyphs, unsigned int size, int fontstyle, bool antialiasing)
	{
		size_t total = renderedGlyphs.size();
		for(size_t i=0; i<total; i++)
		{
			const RenderedGlyph& renderedGlyph = renderedGlyphs.get(i);
			if(renderedGlyph.size >= size && renderedGlyph.fontstyle == fontstyle && renderedGlyph.antialias==antialiasing)
			{
				return renderedGlyph;
			}
		}
		RenderedGlyph renderedGlyph;
		renderedGlyph.texture = nullptr;
		renderedGlyph.size = 0;
		renderedGlyph.fontstyle = Font::STYLE_PLAIN;
		renderedGlyph.antialias = false;
		return renderedGlyph;
	}

	RenderedGlyphContainer::RenderedGlyph RenderedGlyphContainer::renderGlyph(glyph_char glyph, void*fontptr, void*renderer, unsigned int size, int fontstyle, bool antialiasing)
	{
		TTF_Font* font = (TTF_Font*)fontptr;
		SDL_Color color = {255,255,255,255}; //white
		SDL_Surface* surface = nullptr;
		if(antialiasing)
		{
			surface = TTF_RenderGlyph_Blended(font, glyph, color);
		}
		else
		{
			surface = TTF_RenderGlyph_Solid(font, glyph, color);
		}
		if(surface == nullptr)
		{
			throw RenderGlyphException(TTF_GetError());
		}
		SDL_Texture*texture = SDL_CreateTextureFromSurface((SDL_Renderer*)renderer, surface);
		SDL_FreeSurface(surface);
		if(texture == nullptr)
		{
			throw RenderGlyphException(SDL_GetError());
		}

		RenderedGlyph renderedGlyph;
		renderedGlyph.texture = texture;
		renderedGlyph.size = size;
		renderedGlyph.fontstyle = fontstyle;
		renderedGlyph.antialias = antialiasing;

		return renderedGlyph;
	}

	void RenderedGlyphContainer::destroyGlyph(RenderedGlyphContainer::RenderedGlyph&renderedGlyph)
	{
		SDL_DestroyTexture((SDL_Texture*)renderedGlyph.texture);
	}

	void RenderedGlyphContainer::destroyGlyphStyles(RenderedGlyphContainer::RenderedGlyphStyles* glyphStyles)
	{
		if(glyphStyles!=nullptr)
		{
			ArrayList<RenderedGlyph>& styles = glyphStyles->styles;
			size_t total = styles.size();
			for(size_t i=0; i<total; i++)
			{
				destroyGlyph(styles[i]);
			}
			styles.clear();
			delete glyphStyles;
		}
	}
}