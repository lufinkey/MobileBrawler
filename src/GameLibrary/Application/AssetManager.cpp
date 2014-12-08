
#include "AssetManager.h"
#include "../Window/Window.h"

namespace GameLibrary
{
	AssetManager::AssetManager(Window&win)
	{
		window = &win;
	}

	AssetManager::~AssetManager()
	{
		for(unsigned int i=0; i<textures.size(); i++)
		{
			delete textures.get(i).second;
		}
		textures.clear();
		for(unsigned int i=0; i<fonts.size(); i++)
		{
			delete fonts.get(i).second;
		}
		fonts.clear();
	}

	bool AssetManager::loadTexture(const String&path, String&error)
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
		bool success = texture->loadFromFile(path, *window->getGraphics(), error);
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

	bool AssetManager::loadFont(const String&path, String&error)
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
		bool success = font->loadFromFile(path, 24, error);
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
}