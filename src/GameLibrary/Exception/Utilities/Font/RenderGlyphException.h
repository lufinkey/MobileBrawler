
#pragma once

#include "../../Exception.h"

namespace GameLibrary
{
	/*! Thrown to indicate an error rendering a font glyph*/
	class RenderGlyphException : public Exception
	{
	public:
		/*! copy constructor*/
		RenderGlyphException(const RenderGlyphException&);
		/*! \copydoc GameLibrary::Exception::Exception(const GameLibrary::String&)*/
		RenderGlyphException(const String&message);
		/*! virtual destructor*/
		virtual ~RenderGlyphException();
		/*! assignment operator*/
		RenderGlyphException& operator=(const RenderGlyphException&);
	};
}
