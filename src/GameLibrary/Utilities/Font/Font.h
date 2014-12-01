
#include "RenderedGlyphContainer.h"
#include "../ArrayList.h"
#include "../Pair.h"
#include "../String.h"
#include <mutex>

#pragma once

namespace GameLibrary
{
	class Font
	{
		friend class Graphics;
	private:
		void* fontsizes;
		void* fontdata;
		RenderedGlyphContainer glyphs;

		unsigned int size;
		byte style;
		bool antialiasing;

		mutable std::mutex mlock;

		void*loadFontSize(unsigned int size);
		void*getFontPtr(unsigned int size);
		void clearFontSizes();
		ArrayList<RenderedGlyphContainer::RenderedGlyph> getRenderedGlyphs(const String&text, void*renderer);

	public:
		enum : byte
		{
			STYLE_PLAIN         = 0x00000000,
			STYLE_BOLD          = 0x00000001,
			STYLE_ITALIC        = 0x00000002,
			STYLE_UNDERLINE     = 0x00000004,
			STYLE_STRIKETHROUGH = 0x00000008
		};

		Font();
		Font(const Font&);
		~Font();

		bool loadFromFile(const String&path, unsigned int size=24, String&error=String());
	};
}
