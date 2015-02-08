
#include "Color.h"
#include "../Utilities/Math.h"

namespace GameLibrary
{
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
	
	Color::Color(const GameLibrary::Color::RGBA32& rgba)
	{
		byte*rgbaArray = (byte*)(&rgba);
		r = rgbaArray[3];
		g = rgbaArray[2];
		b = rgbaArray[1];
		a = rgbaArray[0];
	}
	
	Color::Color(const Color&color)
	{
		r = color.r;
		g = color.g;
		b = color.b;
		a = color.a;
	}
	
	Color& Color::operator=(const Color&color)
	{
		r = color.r;
		g = color.g;
		b = color.b;
		a = color.a;
		return *this;
	}

	Color& Color::operator=(const GameLibrary::Color::RGBA32& rgba)
	{
		byte*rgbaArray = (byte*)(&rgba);
		r = rgbaArray[3];
		g = rgbaArray[2];
		b = rgbaArray[1];
		a = rgbaArray[0];
		return *this;
	}
	
	bool Color::operator==(const Color&color) const
	{
		return equals(color);
	}
	
	bool Color::operator!=(const Color&color) const
	{
		return !equals(color);
	}
	
	Uint32 Color::getRGBA() const
	{
		Uint32 rgba = 0;
		byte*arr = (byte*)(&rgba);
		arr[3] = r;
		arr[2] = g;
		arr[1] = b;
		arr[0] = a;
		return rgba;
	}

	Uint32 Color::getARGB() const
	{
		Uint32 argb = 0;
		byte*arr = (byte*)(&argb);
		arr[3] = a;
		arr[2] = r;
		arr[1] = g;
		arr[0] = b;
		return argb;
	}

	Uint32 Color::getABGR() const
	{
		Uint32 abgr = 0;
		byte*arr = (byte*)(&abgr);
		arr[3] = a;
		arr[2] = b;
		arr[1] = g;
		arr[0] = r;
		return abgr;
	}
	
	Uint32 Color::getBGRA() const
	{
		Uint32 abgr = 0;
		byte*arr = (byte*)(&abgr);
		arr[3] = b;
		arr[2] = g;
		arr[1] = r;
		arr[0] = a;
		return abgr;
	}
	
	bool Color::equals(const Color&color) const
	{
		if(r==color.r && g==color.g && b==color.b && a==color.a)
		{
			return true;
		}
		return false;
	}

	byte Color_compositeByte(byte orig, byte comp)
	{
		/*float x = (float)orig;
		float n = (float)comp;
		return (byte)((-n / 255) * (n - x - 255));*/
		return (byte)(orig*((float)comp/255));
	}

	Color Color::composite(const Color&comp) const
	{
		byte cr = Color_compositeByte(r,comp.r);
		byte cg = Color_compositeByte(g,comp.g);
		byte cb = Color_compositeByte(b,comp.b);
		byte ca = Color_compositeByte(a,comp.a);
		return Color(cr,cg,cb,ca);
	}

	Color Color::random(bool alpha)
	{
		Color color;
		color.r = (byte)(Math::random()*255);
		color.g = (byte)(Math::random()*255);
		color.b = (byte)(Math::random()*255);
		if(alpha)
		{
			color.a = (byte)(Math::random()*255);
		}
		return color;
	}
}