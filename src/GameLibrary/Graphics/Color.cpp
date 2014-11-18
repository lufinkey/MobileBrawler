
#include "Color.h"

namespace GameLibrary
{
	const Color Color::BLACK = Color(0,0,0);
	const Color Color::BLUE = Color(0,0,255);
	const Color Color::CYAN = Color(0,255,255);
	const Color Color::DARKGRAY = Color(64,64,64);
	const Color Color::GRAY = Color(128,128,128);
	const Color Color::GREEN = Color(0,255,0);
	const Color Color::LIGHTGRAY = Color(192,192,192);
	const Color Color::MAGENTA = Color(255,0,255);
	const Color Color::ORANGE = Color(255,200,0);
	const Color Color::PINK = Color(255,175,175);
	const Color Color::RED = Color(255,0,0);
	const Color Color::WHITE = Color(255,255,255);
	const Color Color::YELLOW = Color(255,255,0);
	const Color Color::TRANSPARENT = Color(0,0,0,0);
	
	Color::Color()
	{
		r = 255;
		g = 255;
		b = 255;
		a = 255;
	}
	
	Color::Color(byte R, byte G, byte B, byte A)
	{
		r = R;
		g = G;
		b = B;
		a = A;
	}
	
	Color::Color(int rgb, bool alpha)
	{
		byte*rgbArray = (byte*)(&rgb);
		r = rgbArray[0];
		g = rgbArray[1];
		b = rgbArray[2];
		if(alpha)
		{
			a = rgbArray[3];
		}
	}
	
	Color::Color(const Color&color)
	{
		r = color.r;
		g = color.g;
		b = color.b;
		a = color.a;
	}
	
	Color::~Color()
	{
		//
	}
	
	Color& Color::operator=(const Color&color)
	{
		r = color.r;
		g = color.g;
		b = color.b;
		a = color.a;
		return *this;
	}
	
	bool Color::operator==(const Color&color) const
	{
		return equals(color);
	}
	
	int Color::getRGBA()
	{
		int rgba = 0;
		byte*arr = (byte*)(&rgba);
		arr[0] = r;
		arr[1] = g;
		arr[2] = b;
		arr[3] = a;
		return rgba;
	}
	
	bool Color::equals(const Color&color) const
	{
		if(r==color.r && g==color.g && b==color.b && a==color.a)
		{
			return true;
		}
		return false;
	}
}