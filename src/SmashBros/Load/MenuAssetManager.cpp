
#include "MenuAssetManager.hpp"

namespace SmashBros
{
	MenuAssetManager::MenuAssetManager(fgl::Window* window, const fgl::String& rootDir)
		: AssetManager(window, rootDir)
	{
		//
	}
	
	MenuAssetManager::~MenuAssetManager()
	{
		unloadImages();
	}
	
	bool MenuAssetManager::loadImage(const fgl::String& path, fgl::String* error)
	{
		if(getImage(path)!=nullptr)
		{
			return true;
		}
		
		FILE* file = openFile(path, "rb");
		if(file==nullptr)
		{
			if(error!=nullptr)
			{
				*error = "Unable to load file";
			}
			return false;
		}
		
		fgl::Image* image = new fgl::Image();
		bool success = image->loadFromFile(file, error);
		std::fclose(file);
		if(success)
		{
			if(error!=nullptr)
			{
				error->clear();
			}
			images.add(std::pair<fgl::String, fgl::Image*>(path, image));
			return true;
		}
		else
		{
			delete image;
			return false;
		}
	}
	
	void MenuAssetManager::unloadImage(const fgl::String& path)
	{
		for(size_t images_size=images.size(), i=0; i<images_size; i++)
		{
			std::pair<fgl::String,fgl::Image*>& pair = images.get(i);
			if(pair.first.equals(path))
			{
				delete pair.second;
				images.remove(i);
				return;
			}
		}
	}
	
	void MenuAssetManager::unloadImages()
	{
		for(auto& imagePair : images)
		{
			delete imagePair.second;
		}
		images.clear();
	}
	
	fgl::Image* MenuAssetManager::getImage(const fgl::String& path) const
	{
		for(auto& imagePair : images)
		{
			if(imagePair.first.equals(path))
			{
				return imagePair.second;
			}
		}
		return nullptr;
	}
	
	void MenuAssetManager::addImage(const fgl::String& path, fgl::Image* image)
	{
		if(image==nullptr)
		{
			throw fgl::IllegalArgumentException("image", "cannot be null");
		}
		images.add(std::pair<fgl::String, fgl::Image*>(path, image));
	}
	
	bool MenuAssetManager::loadMaskedTexture(const fgl::String& path, fgl::Image* imageMask, fgl::String* error)
	{
		if(getTexture(path)!=nullptr)
		{
			return true;
		}
		
		FILE* file = openFile(path, "rb");
		if(file==nullptr)
		{
			if(error!=nullptr)
			{
				*error = "Unable to load file";
			}
			return false;
		}
		
		auto window = getWindow();
		
		fgl::Image image;
		bool success = image.loadFromFile(file, error);
		std::fclose(file);
		if(!success)
		{
			return false;
		}
		if(imageMask!=nullptr)
		{
			image.applyCompositeMask(*imageMask);
		}
		fgl::TextureImage* texture = new fgl::TextureImage();
		success = texture->loadFromImage(image, *window->getGraphics(), error);
		if(!success)
		{
			delete texture;
			return false;
		}
		addTexture(path, texture);
		return true;
	}
	
	void MenuAssetManager::unload()
	{
		AssetManager::unload();
		unloadImages();
	}
}
