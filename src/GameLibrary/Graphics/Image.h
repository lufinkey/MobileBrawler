
#pragma once

#include "Color.h"
#include "../Utilities/ArrayList.h"
#include "../Utilities/Pair.h"
#include "../Utilities/Geometry/Rectangle.h"
#include "../Exception/Graphics/ImageOutOfBoundsException.h"
#include "../Exception/Graphics/UnsupportedImageFormatException.h"

namespace GameLibrary
{
	/*! Holds an array of pixels, representing an image. An Image must be converted into a TextureImage in order to be drawn to the Window.*/
	class Image
	{
	public:
		/*! default constructor*/
		Image();
		/*! copy constructor*/
		Image(const Image&);
		/*! assignment operator*/
		Image& operator=(const Image&);
		
		
		/*! Creates the image and fills it with a given color.
			\param width the width of the image, in pixels
			\param height the height of the image, in pixels
			\param color the color to fill the image*/
		void create(unsigned int width, unsigned int height, const Color&color = Color::TRANSPARENT);
		/*! Clears the current image and sets the size to (0,0)*/
		void clear();
		
		
		/*! Loads the image data from a file path.
			\param path the path to the image file
			\param error an optional String pointer to store the error message if the function fails
			\returns true if the load succeeds, or false if an error is encountered*/
		bool loadFromFile(const String&path, String*error=nullptr);
		/*! Saves the image data to a file. File type is automatically deduced from the file extension. This function currently only supports BMP and PNG.
			\param path the path to save the file
			\param error an optional String pointer to store the error message if the function fails
			\return true if the load succeeds, or false if an error is encountered*/
		bool saveToFile(const String&path, String*error=nullptr) const;
		
		
		/*! Sets the color of the pixel at the given index.
			\throws ImageOutOfBoundsException if the index is outside the bounds of the image
			\param index the index of the pixel
			\param color the color to set the pixel*/
		void setPixel(unsigned int index, const Color&color);
		/*! Sets the color of the pixel at the given coordinates.
			\throws ImageOutOfBoundsException if the coordinates are outside the bounds of the image
			\param x the x coordinate of the pixel
			\param y the y coordinate of the pixel
			\param color the color to set the pixel*/
		void setPixel(unsigned int x, unsigned int y, const Color&color);
		/*! Gets the value of a pixel at the given index.
			\throws ImageOutOfBoundsException if the index is outside the bounds of the image
			\param index the index of the pixel
			\returns a const Color reference representing the value of the pixel*/
		const Color& getPixel(unsigned int index) const;
		/*! Gets the value of a pixel at the given index.
			\throws ImageOutOfBoundsException if the coordinates are outside the bounds of the image
			\param x the x coordinate of the pixel
			\param y the y coordinate of the pixel
			\returns a const Color reference representing the value of the pixel*/
		const Color& getPixel(unsigned int x, unsigned int y) const;
		/*! Gets a container of all the pixels in the image.
			\returns a const ArrayList<Color> reference storing all the pixels in the image*/
		const ArrayList<Color>& getPixels() const;
		
		
		/*! Replaces specified pixels in the image.
			\param colorSwaps an ArrayList containing pairs of Color values, the first in the pair being the original pixel Color, and the second being the replacement*/
		void recolor(const ArrayList<Pair<Color,Color> >& colorSwaps);
		/*! Applies a composite mask to the image. \see GameLibrary::Color::composite(const Color&)const*/
		void applyCompositeMask(const Image&mask);
		
		
		/*! Gets the total size of the image (width * height).
			\returns an unsigned integer representing the total number of pixels in the image*/
		unsigned int getSize() const;
		/*! Gets the width of the image.
			\returns an unsigned integer representing the width of the image, in pixels*/
		unsigned int getWidth() const;
		/*! Gets the height of the image.
			\returns an unsigned integer representing the height of the image, in pixels*/
		unsigned int getHeight() const;
		
	private:
		ArrayList<Color> pixels;
		unsigned int width;
		unsigned int height;
	};
}
