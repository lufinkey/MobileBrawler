
#include "Color.h"
#include "../Utilities/ArrayList.h"
#include "../Exception/Graphics/ImageOutOfBoundsException.h"
#include "../Exception/Graphics/UnsupportedImageFormatException.h"

#pragma once

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
		
		bool loadFromFile(const String&path, String&error = String());
		bool saveToFile(const String&path, String&error = String()) const; //currently only supports BMP and PNG
		
		void setPixel(unsigned int index, const Color&color);
		void setPixel(unsigned int x, unsigned int y, const Color&color);
		const Color& getPixel(unsigned int index) const;
		const Color& getPixel(unsigned int x, unsigned int y) const;
		const ArrayList<Color>& getPixels() const;
		
		unsigned int getSize() const;
		unsigned int getWidth() const;
		unsigned int getHeight() const;
	};
}
