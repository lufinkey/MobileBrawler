
#include "RenderedGlyphContainer.h"
#include "Font.h"
#include <SDL_ttf.h>

namespace GameLibrary
{
	RenderedGlyphContainer::RenderedGlyphContainer()
	{
		for(unsigned int i=0; i<256; i++)
		{
			glyphs[i] = NULL;
		}
	}

	RenderedGlyphContainer::~RenderedGlyphContainer()
	{
		clear();
	}

	void RenderedGlyphContainer::clear()
	{
		mlock.lock();
		for(unsigned int i=0; i<256; i++)
		{
			destroyGlyphStyles(glyphs[i]);
			glyphs[i] = NULL;
		}
		mlock.unlock();
	}

	ArrayList<RenderedGlyphContainer::RenderedGlyph> RenderedGlyphContainer::getRenderedGlyphs(void*fontptr, void*renderer, unsigned int size, byte style, const String&txt, bool antialiasing)
	{
		mlock.lock();
		ArrayList<RenderedGlyph> glyphTextures;
		int ttf_style = Font::styleToTTFStyle(style);
		TTF_SetFontStyle((TTF_Font*)fontptr, ttf_style);
		unsigned int length = txt.length();
		for(unsigned int i=0; i<length; i++)
		{
			try
			{
				glyphTextures.add(getGlyph(txt.charAt(i), fontptr, renderer, size, style, antialiasing));
			}
			catch(const Exception&e)
			{
				//TODO replace with more specific exception type
				mlock.unlock();
				throw Exception(e);
			}
		}
		mlock.unlock();
		return glyphTextures;
	}

	RenderedGlyphContainer::RenderedGlyph RenderedGlyphContainer::getGlyph(signed char glyph, void*fontptr, void*renderer, unsigned int size, byte style, bool antialiasing)
	{
		int index = ((int)glyph) + std::numeric_limits<signed char>::min();
		RenderedGlyphStyles* glyphStyles = glyphs[index];
		if(glyphStyles == NULL)
		{
			glyphStyles = new RenderedGlyphStyles();
			glyphs[index] = glyphStyles;

			RenderedGlyph renderedGlyph = renderGlyph(glyph, fontptr, renderer, size, style, antialiasing);
			glyphStyles->styles.add(renderedGlyph);
			return renderedGlyph;
		}
		else
		{
			ArrayList<RenderedGlyph>& renderedGlyphs = glyphStyles->styles;
			RenderedGlyph renderedGlyph = findGlyph(renderedGlyphs, size, style, antialiasing);
			if(renderedGlyph.texture == NULL)
			{
				renderedGlyph = renderGlyph(glyph, fontptr, renderer, size, style, antialiasing);
				glyphStyles->styles.add(renderedGlyph);
			}
			return renderedGlyph;
		}
	}

	RenderedGlyphContainer::RenderedGlyph RenderedGlyphContainer::findGlyph(const ArrayList<RenderedGlyph>&glyphStyles, unsigned int size, byte style, bool antialiasing)
	{
		unsigned int total = glyphStyles.size();
		for(unsigned int i=0; i<total; i++)
		{
			const RenderedGlyph& glyphStyle = glyphStyles.get(i);
			if(glyphStyle.size >= size && glyphStyle.style == style && glyphStyle.antialias==antialiasing)
			{
				return glyphStyle;
			}
		}
		RenderedGlyph renderedGlyph;
		renderedGlyph.texture = NULL;
		renderedGlyph.size = 0;
		renderedGlyph.style = Font::STYLE_PLAIN;
		renderedGlyph.antialias = false;
		return renderedGlyph;
	}

	RenderedGlyphContainer::RenderedGlyph RenderedGlyphContainer::renderGlyph(char glyph, void*fontptr, void*renderer, unsigned int size, byte style, bool antialiasing)
	{
		TTF_Font* font = (TTF_Font*)fontptr;
		SDL_Color color = {255,255,255,255}; //white
		SDL_Surface* surface = NULL;
		if(antialiasing)
		{
			surface = TTF_RenderGlyph_Blended(font, glyph, color);
		}
		else
		{
			surface = TTF_RenderGlyph_Solid(font, glyph, color);
		}
		if(surface == NULL)
		{
			//TODO replace with more specific exception type
			throw Exception(TTF_GetError());
		}
		SDL_Texture*texture = SDL_CreateTextureFromSurface((SDL_Renderer*)renderer, surface);
		SDL_FreeSurface(surface);
		if(texture == NULL)
		{
			//TODO replace with more specific exception type;
			throw Exception(TTF_GetError());
		}

		RenderedGlyph renderedGlyph;
		renderedGlyph.texture = texture;
		renderedGlyph.size = size;
		renderedGlyph.style = style;
		renderedGlyph.antialias = antialiasing;

		return renderedGlyph;
	}

	void RenderedGlyphContainer::destroyGlyph(RenderedGlyphContainer::RenderedGlyph&renderedGlyph)
	{
		SDL_DestroyTexture((SDL_Texture*)renderedGlyph.texture);
	}

	void RenderedGlyphContainer::destroyGlyphStyles(RenderedGlyphContainer::RenderedGlyphStyles* glyphStyles)
	{
		if(glyphStyles!=NULL)
		{
			ArrayList<RenderedGlyph>& styles = glyphStyles->styles;
			unsigned int total = styles.size();
			for(unsigned int i=0; i<total; i++)
			{
				destroyGlyph(styles[i]);
			}
			styles.clear();
			delete glyphStyles;
		}
	}
}