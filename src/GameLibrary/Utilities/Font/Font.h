
#pragma once

#include "RenderedGlyphContainer.h"
#include "../ArrayList.h"
#include "../Pair.h"
#include "../String.h"
#include "../WideString.h"
#include "../StringConvert.h"
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
		typedef RenderedGlyphContainer::GlyphString GlyphString;
		typedef GlyphString::char_type glyph_char;

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
		
		/*! default constructor*/
		Font();
		/*! copy constructor*/
		Font(const Font&);
		/*! destructor*/
		~Font();
		/*! assignment operator*/
		Font& operator=(const Font&);
		
		
		/*! Loads a Font from a given file path.
			\param path the file path of the font file
			\param size the glyph size of the font
			\param error an optional String pointer to store the error message if the function fails
			\returns true if the load succeeds, or false if an error is encountered*/
		bool loadFromFile(const String&path, unsigned int size=24, String*error=nullptr);
		
		
		/*! Estimates the display size of a given string of text.
			\param text a string of text to estimate
			\returns a Vector2u representing the display width (x) and height (y) of the string*/
		Vector2u measureString(const GlyphString&text);
		
		
		/*! Sets a bitmask for the style (plain, bold, italic, etc.).
			\param style a bitmask of style values \see GameLibrary::Font::Style*/
		void setStyle(int style);
		/*! Sets the glyph size.
			\param size a glyph size*/
		void setSize(unsigned int size);
		/*! Sets smoothing enabled for glyph rendering. Smooth font glyphs take up more memory than normal ones. Antialiasing is false by default.
			\param antialiasing true to smooth font glyphs, or false to render them normally*/
		void setAntialiasing(bool antialiasing);
		
		
		/*! Gets a bitmask of font styles (plain, bold, italic, etc.)
			\returns a bitmask of style values \see GameLibrary::Font::Style*/
		int getStyle();
		/*! Gets the current glyph size.*/
		unsigned int getSize();
		/*! Tells whether smoothing is enabled for glyph rendering.
			\returns true if smoothing is enabled, or false if otherwise*/
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
		ArrayList<RenderedGlyphContainer::RenderedGlyph> getRenderedGlyphs(const GlyphString&text, void*renderer);

		static int styleToTTFStyle(int fontstyle);
	};
}
