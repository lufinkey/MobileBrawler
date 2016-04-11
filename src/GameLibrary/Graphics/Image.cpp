
#include "Image.h"
#include "PixelIterator.h"
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
	
	bool Image::loadFromFile(const String&path, String*error)
	{
		SDL_Surface* surface = IMG_Load(path);
		if(surface != nullptr)
		{
			int mustlock = SDL_MUSTLOCK(surface);
			if(mustlock!=0)
			{
				if(SDL_LockSurface(surface) < 0)
				{
					if(error!=nullptr)
					{
						*error = SDL_GetError();
					}
					SDL_FreeSurface(surface);
					return false;
				}
			}

			unsigned int bpp = (unsigned int)surface->format->BytesPerPixel;
			
			unsigned int rmask = (unsigned int)surface->format->Rmask;
			unsigned int rshift = (unsigned int)surface->format->Rshift;
			unsigned int gmask = (unsigned int)surface->format->Gmask;
			unsigned int gshift = (unsigned int)surface->format->Gshift;
			unsigned int bmask = (unsigned int)surface->format->Bmask;
			unsigned int bshift = (unsigned int)surface->format->Bshift;
			unsigned int amask = (unsigned int)surface->format->Amask;
			unsigned int ashift = (unsigned int)surface->format->Ashift;
			
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
						{
							int color = *((int*)&surfacePixels[counter]);
							pixels[i].r = (byte)((color & rmask) >> rshift);
							pixels[i].g = (byte)((color & gmask) >> gshift);
							pixels[i].b = (byte)((color & bmask) >> bshift);
							pixels[i].a = 255;
						}
						break;
						
						case 4:
						{
							int color = *((int*)&surfacePixels[counter]);
							pixels[i].r = (byte)((color & rmask) >> rshift);
							pixels[i].g = (byte)((color & gmask) >> gshift);
							pixels[i].b = (byte)((color & bmask) >> bshift);
							pixels[i].a = (byte)((color & amask) >> ashift);
						}
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
		if(error!=nullptr)
		{
			*error = IMG_GetError();
		}
		return false;
	}

	bool Image::saveToFile(const String& path, String*error) const
	{
		size_t dotIndex = path.lastIndexOf('.');
		if(dotIndex == String::NOTFOUND)
		{
			throw UnsupportedImageFormatException("");
		}
		else
		{
			String format = path.substring(dotIndex + 1, path.length());
			if(format.indexOf('/')!=String::NOTFOUND || format.indexOf('\\')!=String::NOTFOUND)
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
						if(error!=nullptr)
						{
							*error = SDL_GetError();
						}
						return false;
					}

					if(IMG_SavePNG(surface, path) != 0)
					{
						if(error!=nullptr)
						{
							*error = IMG_GetError();
						}
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
						if(error!=nullptr)
						{
							*error = SDL_GetError();
						}
						return false;
					}

					if(SDL_SaveBMP(surface, path) != 0)
					{
						if(error!=nullptr)
						{
							*error = SDL_GetError();
						}
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

	void Image::recolor(const ArrayList<Pair<Color, Color> >& colorSwaps)
	{
		size_t total = pixels.size();
		size_t totalSwaps = colorSwaps.size();
		for(size_t i=0; i<total; i++)
		{
			const Color& color = pixels.get(i);
			for(size_t j=0; j<totalSwaps; j++)
			{
				const Pair<Color,Color>& colorSwap = colorSwaps.get(j);
				if(color.equals(colorSwap.first))
				{
					pixels.set(i, colorSwap.second);
					j = totalSwaps;
				}
			}
		}
	}
	
	void Image::applyCompositeMask(const Image&mask)
	{
		if(width == 0 || height == 0 || mask.width==0 || mask.height==0)
		{
			return;
		}
		RectangleD dstRect = RectangleD(0,0,(double)width,(double)height);
		PixelIterator pxlIter(Vector2u(width,height), RectangleU(0,0,width,height), dstRect, dstRect, 1, 1, false, false);
		
		PixelIterator mask_pxlIter(Vector2u(mask.width,mask.height), RectangleU(0,0,mask.width,mask.height), dstRect, dstRect, 1, 1, false, false);
		
		std::vector<bool> masked(pixels.size());
		size_t total = pixels.size();
		for(size_t i=0; i<total; i++)
		{
			masked[i] = false;
		}

		bool running = pxlIter.nextPixelIndex();
		bool mask_running = mask_pxlIter.nextPixelIndex();
		while(running && mask_running)
		{
			double pxlIndex = pxlIter.getCurrentPixelIndex();
			double mask_pxlIndex = mask_pxlIter.getCurrentPixelIndex();
			
			if(pxlIndex>=0 && mask_pxlIndex>=0)
			{
				unsigned int index = (unsigned int)pxlIndex;
				if(!masked[index])
				{
					unsigned int mask_index = (unsigned int)mask_pxlIndex;
					const Color& mask_color = mask.getPixel(mask_index);
					Color curcol = pixels[index];
					pixels[index] = curcol.composite(mask_color);
					masked[index] = true;
				}
			}
			
			running = pxlIter.nextPixelIndex();
			mask_running = mask_pxlIter.nextPixelIndex();
		}
		if(running != mask_running)
		{
			throw Exception("Unknown masking bug. This exception means there is a bug within the Image::applyMask function");
		}
	}

	unsigned int Image::getSize() const
	{
		return (unsigned int)pixels.size();
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