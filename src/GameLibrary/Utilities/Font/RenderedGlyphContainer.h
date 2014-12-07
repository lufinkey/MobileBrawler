
#include "../../Types.h"
#include "../ArrayList.h"
#include "../String.h"
#include <mutex>

#pragma once

namespace GameLibrary
{
	class RenderedGlyphContainer
	{
		friend class Font;
		friend class Graphics;
	private:
		typedef struct
		{
			void* texture;
			unsigned int size;
			byte style;
			bool antialias;
		} RenderedGlyph;

		typedef struct
		{
			ArrayList<RenderedGlyph> styles;
		} RenderedGlyphStyles;

		RenderedGlyphStyles* glyphs[256];
		std::mutex mlock;

		RenderedGlyph renderGlyph(char glyph, void*fontptr, void*renderer, unsigned int size, byte style, bool antialiasing);
		void destroyGlyph(RenderedGlyph&renderedGlyph);
		void destroyGlyphStyles(RenderedGlyphStyles*glyphStyles);

		RenderedGlyph getGlyph(signed char glyph, void*fontptr, void*renderer, unsigned int size, byte style, bool antialiasing);
		RenderedGlyph findGlyph(const ArrayList<RenderedGlyph>&glyphStyles, unsigned int size, byte style, bool antialiasing);

	public:
		RenderedGlyphContainer();
		~RenderedGlyphContainer();

		ArrayList<RenderedGlyph> getRenderedGlyphs(void*fontptr, void*renderer, unsigned int size, byte style, const String&txt, bool antialiasing = false);

		void clear();
	};
}