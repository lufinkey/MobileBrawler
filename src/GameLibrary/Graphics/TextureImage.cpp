
#include "TextureImage.h"
#include "Image.h"
#include <SDL.h>

namespace GameLibrary
{
	TextureImage::TextureImage(const TextureImage&image) : TextureImage()
	{
		//
	}

	TextureImage& TextureImage::operator=(const TextureImage&image)
	{
		return *this;
	}

	TextureImage::TextureImage()
	{
		texture = nullptr;
		width = 0;
		height = 0;
	}

	TextureImage::~TextureImage()
	{
		if(texture != nullptr)
		{
			SDL_DestroyTexture((SDL_Texture*)texture);
		}
	}
	
	void TextureImage::create(unsigned int w, unsigned int h, Graphics&graphics)
	{
		if(w>0 && h>0)
		{
			SDL_Texture* newTexture = SDL_CreateTexture((SDL_Renderer*)graphics.renderer, SDL_PIXELFORMAT_ABGR8888, SDL_TEXTUREACCESS_STREAMING, (int)w, (int)h);
			if(newTexture == nullptr)
			{
				//TODO replace with a more specific exception type
				throw Exception(SDL_GetError());
			}
			if(texture != nullptr)
			{
				SDL_DestroyTexture((SDL_Texture*)texture);
				texture = nullptr;
			}
			texture = (void*)newTexture;
			width = w;
			height = h;
			unsigned int total = w*h;
			pixels.resize(total);
			for(unsigned int i=0; i<total; i++)
			{
				pixels[i] = false;
			}
		}
		else
		{
			if(texture != nullptr)
			{
				SDL_DestroyTexture((SDL_Texture*)texture);
				texture = nullptr;
			}
			width = 0;
			height = 0;
			pixels.resize(0);
			pixels.shrink_to_fit();
		}
	}

	void TextureImage::update(const Color*pxls)
	{
		if(texture == nullptr)
		{
			//TODO replace with more specific exception type
			throw Exception("Cannot update an empty TextureImage");
		}
		void* pixelptr;
		int pitch;
		if(SDL_LockTexture((SDL_Texture*)texture, nullptr, &pixelptr, &pitch) < 0)
		{
			//TODO replace with more specific exception type
			throw Exception(SDL_GetError());
		}

		Color*texture_pixels = (Color*)pixelptr;
		unsigned int total = width*height;
		for(unsigned int i=0; i<total; i++)
		{
			const Color& color = pxls[i];
			if(color.a > 0)
			{
				pixels[i]=true;
			}
			else
			{
				pixels[i] = false;
			}
			texture_pixels[i] = color;
		}

		SDL_UnlockTexture((SDL_Texture*)texture);
	}

	//TODO figure out where the Rect updates first, so I can figure out how to update the bool vector
	//TODO add checking for out of bounds
	/*void TextureImage::update(const Color*pixels, unsigned int x, unsigned int y, unsigned int w, unsigned int h)
	{
		if(texture == nullptr)
		{
			//TODO replace with more specific exception type
			throw Exception("Cannot update an empty TextureImage");
		}

		SDL_Rect rect;
		rect.x = (int)x;
		rect.y = (int)y;
		rect.w = (int)w;
		rect.h = (int)h;

		void* pixelptr;
		int pitch;
		if(SDL_LockTexture((SDL_Texture*)texture, &rect, &pixelptr, &pitch) < 0)
		{
			//TODO replace with more specific exception type
			throw Exception(SDL_GetError());
		}

		Color*texture_pixels = (Color*)pixelptr;
		unsigned int total = w*h;
		for(unsigned int i=0; i<total; i++)
		{
			texture_pixels[i] = pixels[i];
		}

		SDL_UnlockTexture((SDL_Texture*)texture);
	}*/
	
	bool TextureImage::loadFromFile(const String&path, Graphics&graphics, String&error)
	{
		Image img;
		if(img.loadFromFile(path, error))
		{
			return loadFromImage(img,graphics,error);
		}
		return false;
	}

	bool TextureImage::loadFromImage(const Image&image, Graphics&graphics, String&error)
	{
		const ArrayList<Color>& image_pixels = image.getPixels();
		if(image_pixels.size()>0)
		{
			SDL_Texture* newTexture = SDL_CreateTexture((SDL_Renderer*)graphics.renderer, SDL_PIXELFORMAT_ABGR8888, SDL_TEXTUREACCESS_STREAMING, (int)image.getWidth(), (int)image.getHeight());
			if(newTexture == nullptr)
			{
				//TODO replace with a more specific exception type
				error = SDL_GetError();
				return false;
			}
			if(texture != nullptr)
			{
				SDL_DestroyTexture((SDL_Texture*)texture);
				texture = nullptr;
			}
			texture = (void*)newTexture;
			unsigned int w = image.getWidth();
			unsigned int h = image.getHeight();
			unsigned int totalsize = w*h;
			void*pixelptr;
			int pitch;
			if(SDL_LockTexture((SDL_Texture*)texture, nullptr, &pixelptr, &pitch) < 0)
			{
				//TODO replace with a more specific exception type
				error = SDL_GetError();
				return false;
			}

			pixels.resize(totalsize);
			pixels.shrink_to_fit();

			int*texture_pixels = (int*)pixelptr;
			for(unsigned int i=0; i<totalsize; i++)
			{
				const Color&px = image_pixels[i];
				if(px.a>0)
				{
					pixels[i] = true;
				}
				else
				{
					pixels[i] = false;
				}
				texture_pixels[i] = px.getRGBA();
			}

			SDL_UnlockTexture((SDL_Texture*)texture);

			width = w;
			height = h;

			return true;
		}
		else
		{
			if(texture != nullptr)
			{
				SDL_DestroyTexture((SDL_Texture*)texture);
				texture = nullptr;
			}
			width = 0;
			height = 0;
			pixels.resize(0);
			pixels.shrink_to_fit();
			return true;
		}
		return false;
	}

	bool TextureImage::checkPixel(unsigned int index) const
	{
		/*if(index > pixels.size())
		{
			throw ImageOutOfBoundsException(index,width,height);
		}*/
		//TODO uncomment checking of out of bounds (once I add a function returning the vector of bits)
		return pixels[index];
	}

	bool TextureImage::checkPixel(unsigned int x, unsigned int y) const
	{
		/*if(x > width || y > height)
		{
			throw ImageOutOfBoundsException(x, y, width, height);
		}*/
		//TODO uncomment checking of out of bounds (once I add a function returning the vector of bits)
		return pixels[(width*y)+x];
	}
}