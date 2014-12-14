
#include "RenderGlyphException.h"

namespace GameLibrary
{
	RenderGlyphException::RenderGlyphException(const RenderGlyphException&exception) : Exception(exception)
	{
		//
	}

	RenderGlyphException::RenderGlyphException(const String&message) : Exception(message)
	{
		//
	}

	RenderGlyphException::~RenderGlyphException()
	{
		//
	}
}
