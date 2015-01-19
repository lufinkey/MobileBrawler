
#pragma once

#include "Color.h"
#include "../Utilities/ArrayList.h"
#include "../Utilities/Pair.h"
#include "../Utilities/Geometry/Rectangle.h"
#include "../Exception/Graphics/ImageOutOfBoundsException.h"
#include "../Exception/Graphics/UnsupportedImageFormatException.h"

namespace GameLibrary
{
	class Image
	{
	private:
		ArrayList<Color> pixels;
		unsigned int width;
		unsigned int height;
		
	public:
		Image();
		Image(const Image&);
		~Image();
		
		Image& operator=(const Image&);
		
		void create(unsigned int width, unsigned int height, const Color&color = Color::TRANSPARENT);
		void clear();
		
		bool loadFromFile(const String&path, String*error=nullptr);
		bool saveToFile(const String&path, String*error=nullptr) const; //currently only supports BMP and PNG
		
		void setPixel(unsigned int index, const Color&color);
		void setPixel(unsigned int x, unsigned int y, const Color&color);
		const Color& getPixel(unsigned int index) const;
		const Color& getPixel(unsigned int x, unsigned int y) const;
		const ArrayList<Color>& getPixels() const;

		void recolor(const ArrayList<Pair<Color,Color> >& colorSwaps);
		void applyAlphaMask(const Image&mask);
		void applyAlphaMask(const Image&mask, const RectangleI&dstRect);
		
		unsigned int getSize() const;
		unsigned int getWidth() const;
		unsigned int getHeight() const;
	};
}
