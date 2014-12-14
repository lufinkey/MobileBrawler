
#include "RenderedGlyphContainer.h"
#include "Font.h"
#include <SDL_ttf.h>

namespace GameLibrary
{
	RenderedGlyphContainer::RenderedGlyphContainer()
	{
		for(unsigned int i=0; i<256; i++)
		{
			glyphs[i] = nullptr;
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
			glyphs[i] = nullptr;
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
			catch(const RenderGlyphException&e)
			{
				mlock.unlock();
				throw RenderGlyphException(e);
			}
		}
		mlock.unlock();
		return glyphTextures;
	}

	RenderedGlyphContainer::RenderedGlyph RenderedGlyphContainer::getGlyph(signed char glyph, void*fontptr, void*renderer, unsigned int size, byte style, bool antialiasing)
	{
		unsigned int index = ((unsigned int)glyph) + SCHAR_MAX;
		RenderedGlyphStyles* glyphStyles = glyphs[index];
		if(glyphStyles == nullptr)
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
			if(renderedGlyph.texture == nullptr)
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
		renderedGlyph.texture = nullptr;
		renderedGlyph.size = 0;
		renderedGlyph.style = Font::STYLE_PLAIN;
		renderedGlyph.antialias = false;
		return renderedGlyph;
	}

	RenderedGlyphContainer::RenderedGlyph RenderedGlyphContainer::renderGlyph(char glyph, void*fontptr, void*renderer, unsigned int size, byte style, bool antialiasing)
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
		if(glyphStyles!=nullptr)
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