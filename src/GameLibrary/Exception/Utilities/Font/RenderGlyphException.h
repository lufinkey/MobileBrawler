
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
		explicit RenderGlyphException(const String&message);
		/*! virtual destructor*/
		virtual ~RenderGlyphException();
		/*! assignment operator*/
		RenderGlyphException& operator=(const RenderGlyphException&);
		
		/*! \copydoc GameLibrary::Exception::getClassName()const*/
		virtual String getClassName() const override;
	};
}
