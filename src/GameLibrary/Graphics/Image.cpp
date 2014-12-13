
#include "Image.h"
#include <SDL_image.h>

namespace GameLibrary
{
	Image::Image()
	{
		int flags = IMG_INIT_JPG | IMG_INIT_PNG | IMG_INIT_TIF;
		if(IMG_Init(flags) != flags)
		{
			//TODO replace with more specific exception type
			throw Exception(IMG_GetError());
		}

		width = 0;
		height = 0;
	}

	Image::Image(const Image&img)
	{
		pixels = img.pixels;
		width = img.width;
		height = img.height;
	}

	Image::~Image()
	{
		pixels.clear();
	}
	
	Image& Image::operator=(const Image&img)
	{
		pixels = img.pixels;
		width = img.width;
		height = img.height;
		return *this;
	}
	
	void Image::create(unsigned int w, unsigned int h, const Color&color)
	{
		unsigned int total = w*h;
		if(width == 0 || height == 0)
		{
			width = 0;
			height = 0;
		}
		else
		{
			width = w;
			height = h;
		}
		pixels.resize(total);
		for(unsigned int i = 0; i < total; i++)
		{
			pixels[i] = color;
		}
	}

	void Image::clear()
	{
		pixels.clear();
		width = 0;
		height = 0;
	}
	
	bool Image::loadFromFile(const String&path, String&error)
	{
		SDL_Surface* surface = IMG_Load(path);
		if(surface != nullptr)
		{
			int mustlock = SDL_MUSTLOCK(surface);
			if(mustlock!=0)
			{
				if(SDL_LockSurface(surface) < 0)
				{
					error = SDL_GetError();
					SDL_FreeSurface(surface);
					return false;
				}
			}

			unsigned int bpp = (unsigned int)surface->format->BytesPerPixel;
			width = (unsigned int)surface->w;
			height = (unsigned int)surface->h;
			unsigned int total = width*height;
			pixels.resize(total);

			unsigned int pitchDif = ((unsigned int)surface->pitch - (width*bpp));
			
			unsigned int counter = 0;
			byte*surfacePixels = (byte*)surface->pixels;

			unsigned int i=0;
			for(unsigned int ycnt=0; ycnt<height; ycnt++)
			{
				for(unsigned int xcnt = 0; xcnt < width; xcnt++)
				{
					switch(bpp)
					{
						case 1:
						pixels[i].r = surfacePixels[counter];
						pixels[i].g = surfacePixels[counter];
						pixels[i].b = surfacePixels[counter];
						pixels[i].a = 255;
						break;

						case 2:
						pixels[i].r = surfacePixels[counter];
						pixels[i].g = surfacePixels[counter+1];
						pixels[i].b = surfacePixels[counter+1];
						pixels[i].a = 255;
						break;

						case 3:
	#if SDL_BYTEORDER == SDL_BIG_ENDIAN
						pixels[i].r = surfacePixels[counter+2];
						pixels[i].g = surfacePixels[counter+1];
						pixels[i].b = surfacePixels[counter];
	#else
						pixels[i].r = surfacePixels[counter];
						pixels[i].g = surfacePixels[counter+1];
						pixels[i].b = surfacePixels[counter+2];
	#endif
						pixels[i].a = 255;
						break;

						case 4:
	#if SDL_BYTEORDER == SDL_BIG_ENDIAN
						pixels[i].r = surfacePixels[counter+3];
						pixels[i].g = surfacePixels[counter+2];
						pixels[i].b = surfacePixels[counter+1];
						pixels[i].a = surfacePixels[counter];
	#else
						pixels[i].r = surfacePixels[counter];
						pixels[i].g = surfacePixels[counter+1];
						pixels[i].b = surfacePixels[counter+2];
						pixels[i].a = surfacePixels[counter+3];
	#endif
						break;
					}
					i++;
					counter += bpp;
				}
				counter += pitchDif;
			}

			if(mustlock != 0)
			{
				SDL_UnlockSurface(surface);
			}

			SDL_FreeSurface(surface);

			return true;
		}
		error = IMG_GetError();
		return false;
	}

	bool Image::saveToFile(const String&path, String&error) const
	{
		unsigned int dotIndex = path.lastIndexOf('.');
		if(dotIndex == STRING_NOTFOUND)
		{
			throw UnsupportedImageFormatException("");
		}
		else
		{
			String format = path.substring(dotIndex + 1, path.length());
			if(format.indexOf('/')!=STRING_NOTFOUND || format.indexOf('\\')!=STRING_NOTFOUND)
			{
				throw UnsupportedImageFormatException("");
			}
			else
			{
				if(format.equals("png"))
				{
					SDL_Surface* surface = SDL_CreateRGBSurfaceFrom((void*)pixels.getData(), (int)width, (int)height, 32, width*4, 0x000000ff, 0x0000ff00, 0x00ff0000, 0xff000000);
					if(surface == nullptr)
					{
						error = SDL_GetError();
						return false;
					}

					if(IMG_SavePNG(surface, path) != 0)
					{
						error = IMG_GetError();
						SDL_FreeSurface(surface);
						return false;
					}

					SDL_FreeSurface(surface);
					return true;
				}
				else if(format.equals("bmp"))
				{
					SDL_Surface* surface = SDL_CreateRGBSurfaceFrom((void*)pixels.getData(), (int)width, (int)height, 32, width*4, 0x000000ff, 0x0000ff00, 0x00ff0000, 0xff000000);
					if(surface == nullptr)
					{
						error = SDL_GetError();
						return false;
					}

					if(SDL_SaveBMP(surface, path) != 0)
					{
						error = SDL_GetError();
						SDL_FreeSurface(surface);
						return false;
					}

					SDL_FreeSurface(surface);
					return true;
				}
				else
				{
					throw UnsupportedImageFormatException(format);
				}
			}
		}

		return false;
	}

	void Image::setPixel(unsigned int index, const Color&color)
	{
		try
		{
			pixels[index] = color;
		}
		catch(const ArrayListOutOfBoundsException&)
		{
			throw ImageOutOfBoundsException(index, width, height);
		}
	}
	
	void Image::setPixel(unsigned int x, unsigned int y, const Color&color)
	{
		try
		{
			pixels[(width*y)+x] = color;
		}
		catch(const ArrayListOutOfBoundsException&)
		{
			throw ImageOutOfBoundsException(x, y, width, height);
		}
	}

	const Color& Image::getPixel(unsigned int index) const
	{
		try
		{
			return pixels[index];
		}
		catch(const ArrayListOutOfBoundsException&)
		{
			throw ImageOutOfBoundsException(index, width, height);
		}
	}

	const Color& Image::getPixel(unsigned int x, unsigned int y) const
	{
		try
		{
			return pixels[(width*y)+x];
		}
		catch(const ArrayListOutOfBoundsException&)
		{
			throw ImageOutOfBoundsException(x, y, width, height);
		}
	}

	const ArrayList<Color>& Image::getPixels() const
	{
		return pixels;
	}

	unsigned int Image::getSize() const
	{
		return pixels.size();
	}
	
	unsigned int Image::getWidth() const
	{
		return width;
	}

	unsigned int Image::getHeight() const
	{
		return height;
	}
}