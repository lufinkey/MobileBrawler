
#pragma once

#include "RenderedGlyphContainer.h"
#include "../ArrayList.h"
#include "../Pair.h"
#include "../String.h"
#include "../Geometry/Vector2.h"
#include "../../Exception/InitializeLibraryException.h"
#include "../../Exception/Utilities/Font/RenderGlyphException.h"
#include <mutex>
#include <memory>

namespace GameLibrary
{
	/*! Holds data for a typeface, or font. It also holds a RenderedGlyphContainer for containing previously rendered glyphs.*/
	class Font
	{
		friend class Graphics;
		friend class RenderedGlyphContainer;
	public:
		/*Bitmask values for Font styles*/
		enum Style
		{
			/*! Plain font. No */
			STYLE_PLAIN         = 0x00000000,
			STYLE_BOLD          = 0x00000001,
			STYLE_ITALIC        = 0x00000002,
			STYLE_UNDERLINE     = 0x00000004,
			STYLE_STRIKETHROUGH = 0x00000008
		};

		Font();
		Font(const Font&);
		~Font();

		bool loadFromFile(const String&path, unsigned int size=24, String*error=nullptr);

		Vector2u measureString(const String&text);

		void setStyle(int style);
		void setSize(unsigned int size);
		void setAntialiasing(bool antialiasing);

		int getStyle();
		unsigned int getSize();
		bool getAntialiasing();

	private:
		typedef ArrayList<Pair<unsigned int, void*>> FontSizeList;

		std::shared_ptr<FontSizeList> fontsizes;
		std::shared_ptr<DataPacket> fontdata;
		ArrayList<Pair<RenderedGlyphContainer*, void*> > glyphs;

		unsigned int size;
		int style;
		bool antialiasing;

		mutable std::mutex mlock;

		void*loadFontSize(unsigned int size);
		void*getFontPtr(unsigned int size);
		void clearFontSizes();
		RenderedGlyphContainer* getRenderedGlyphContainer(void*renderer);
		ArrayList<RenderedGlyphContainer::RenderedGlyph> getRenderedGlyphs(const String&text, void*renderer);

		static int styleToTTFStyle(int fontstyle);
	};
}
