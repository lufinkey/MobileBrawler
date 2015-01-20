
#include "AssetManager.h"
#include "../Window/Window.h"

namespace GameLibrary
{
	AssetManager::AssetManager(Window&win, const String&root)
	{
		window = &win;
		rootdir = root;
	}

	AssetManager::~AssetManager()
	{
		unloadTextures();
		unloadFonts();
	}
	
	String AssetManager::getFullPath(const String&path) const
	{
		String fullpath;
		if(rootdir.length() == 0)
		{
			fullpath = path;
		}
		else
		{
			if(rootdir.charAt(rootdir.length()-1)=='/')
			{
				fullpath = rootdir + path;
			}
			else
			{
				fullpath = rootdir + '/' + path;
			}
		}
		return fullpath;
	}
	
	void AssetManager::setRootDirectory(const String&root)
	{
		rootdir = root;
	}
	
	const String& AssetManager::getRootDirectory() const
	{
		return rootdir;
	}
	
	Window* AssetManager::getWindow() const
	{
		return window;
	}

	bool AssetManager::loadTexture(const String&path, String*error)
	{
		for(unsigned int i=0; i<textures.size(); i++)
		{
			Pair<String,TextureImage*>& pair = textures.get(i);
			if(pair.first.equals(path))
			{
				return true;
			}
		}

		TextureImage* texture = new TextureImage();
		String fullpath = getFullPath(path);
		bool success = texture->loadFromFile(fullpath, *window->getGraphics(), error);
		if(success)
		{
			textures.add(Pair<String,TextureImage*>(path, texture));
			return true;
		}
		else
		{
			delete texture;
			return false;
		}
	}

	void AssetManager::unloadTexture(const String&path)
	{
		for(unsigned int i=0; i<textures.size(); i++)
		{
			Pair<String,TextureImage*>& pair = textures.get(i);
			if(pair.first.equals(path))
			{
				delete pair.second;
				textures.remove(i);
				return;
			}
		}
	}

	void AssetManager::unloadTextures()
	{
		for(unsigned int i=0; i<textures.size(); i++)
		{
			delete textures.get(i).second;
		}
		textures.clear();
	}

	TextureImage* AssetManager::getTexture(const String&path)
	{
		for(unsigned int i=0; i<textures.size(); i++)
		{
			Pair<String,TextureImage*>& pair = textures.get(i);
			if(pair.first.equals(path))
			{
				return pair.second;
			}
		}
		return nullptr;
	}
	
	void AssetManager::addTexture(const String&path, TextureImage*image)
	{
		if(image!=nullptr)
		{
			textures.add(Pair<String, TextureImage*>(path, image));
		}
	}

	bool AssetManager::loadFont(const String&path, String*error)
	{
		for(unsigned int i=0; i<fonts.size(); i++)
		{
			Pair<String,Font*>& pair = fonts.get(i);
			if(pair.first.equals(path))
			{
				return true;
			}
		}

		Font* font = new Font();
		String fullpath = getFullPath(path);
		bool success = font->loadFromFile(fullpath, 24, error);
		if(success)
		{
			fonts.add(Pair<String,Font*>(path, font));
			return true;
		}
		else
		{
			delete font;
			return false;
		}
	}

	void AssetManager::unloadFont(const String&path)
	{
		for(unsigned int i=0; i<fonts.size(); i++)
		{
			Pair<String,Font*>& pair = fonts.get(i);
			if(pair.first.equals(path))
			{
				delete pair.second;
				fonts.remove(i);
				return;
			}
		}
	}

	void AssetManager::unloadFonts()
	{
		for(unsigned int i=0; i<fonts.size(); i++)
		{
			delete fonts.get(i).second;
		}
		fonts.clear();
	}

	Font* AssetManager::getFont(const String&path)
	{
		for(unsigned int i=0; i<fonts.size(); i++)
		{
			Pair<String,Font*>& pair = fonts.get(i);
			if(pair.first.equals(path))
			{
				return pair.second;
			}
		}
		return nullptr;
	}
	
	void AssetManager::addFont(const String&path, Font*font)
	{
		if(font!=nullptr)
		{
			fonts.add(Pair<String, Font*>(path, font));
		}
	}
	
	void AssetManager::unload()
	{
		unloadTextures();
		unloadFonts();
	}
}