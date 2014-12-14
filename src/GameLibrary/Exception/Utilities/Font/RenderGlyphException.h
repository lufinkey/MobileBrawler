
#include "../../Exception.h"

#pragma once

namespace GameLibrary
{
	class RenderGlyphException : public Exception
	{
	public:
		RenderGlyphException(const RenderGlyphException&);
		RenderGlyphException(const String&message);
		virtual ~RenderGlyphException();
	};
}
