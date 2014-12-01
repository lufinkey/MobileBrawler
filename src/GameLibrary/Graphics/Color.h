
#include "../Types.h"

#pragma once

namespace GameLibrary
{
	class Color
	{
	public:
		static const Color BLACK;
		static const Color BLUE;
		static const Color CYAN;
		static const Color DARKGRAY;
		static const Color GRAY;
		static const Color GREEN;
		static const Color LIGHTGRAY;
		static const Color MAGENTA;
		static const Color ORANGE;
		static const Color PINK;
		static const Color RED;
		static const Color WHITE;
		static const Color YELLOW;
		static const Color TRANSPARENT;
		
		byte r,g,b,a;
		
		Color();
		Color(const Color&color);
		Color(Uint32 rgb, bool alpha = false);
		Color(byte r, byte g, byte b, byte a=255);
		~Color();
		
		Color&operator=(const Color&color);
		bool operator==(const Color&color) const;
		
		Uint32 getRGBA();
		
		bool equals(const Color&color) const;
	};
}