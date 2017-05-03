
#include "CharacterLoader.hpp"

namespace SmashLib
{
	using namespace fgl;
	
	CharacterLoader::CharacterLoader(Window* window)
	{
		assetManager = new AssetManager(window);
	}
	
	CharacterLoader::~CharacterLoader()
	{
		delete assetManager;
	}
	
	AssetManager* CharacterLoader::getAssetManager() const
	{
		return assetManager;
	}
	
	void CharacterLoader::addPath(const String&path)
		//TODO add ability to pass in ArrayList for error catching
	{
		for(unsigned int i=0; i<paths.size(); i++)
		{
			if(path.equals(paths.get(i)))
			{
				return;
			}
		}
		
		ArrayList<FileTools::DirectoryEntry> dirEntries;
		FileTools::readEntriesFromDirectory(path, &dirEntries);
		
		for(unsigned int i=0; i<dirEntries.size(); i++)
		{
			FileTools::DirectoryEntry& dirEntry = dirEntries.get(i);
			if(dirEntry.type==FileTools::ENTRYTYPE_FOLDER || dirEntry.type==FileTools::ENTRYTYPE_LINK_FOLDER)
			{
				CharacterInfo info;
				bool success = info.loadFromPath(path + "/" + dirEntry.name);
				//TODO see if minsmashversion is compatible
				if(success)
				{
					bool alreadyAdded = false;
					for(size_t j=0; j<characters.size(); j++)
					{
						CharacterInfo&cmp = characters.get(j);
						if(info.getName().equals(cmp.getName()) && info.getCreator().equals(cmp.getCreator()))
						{
							alreadyAdded = true;
							j = characters.size();
						}
					}
					if(!alreadyAdded)
					{
						characters.add(info);
					}
				}
			}
		}
	}
	
	void CharacterLoader::reloadPaths()
	{
		characters.clear();
		for(unsigned int i=0; i<paths.size(); i++)
		{
			String path = paths.get(i);
			
			ArrayList<FileTools::DirectoryEntry> dirEntries;
			FileTools::readEntriesFromDirectory(path, &dirEntries);
			
			for(unsigned int j=0; j<dirEntries.size(); j++)
			{
				FileTools::DirectoryEntry& dirEntry = dirEntries.get(j);
				if(dirEntry.type==FileTools::ENTRYTYPE_FOLDER || dirEntry.type==FileTools::ENTRYTYPE_LINK_FOLDER)
				{
					CharacterInfo info;
					bool success = info.loadFromPath(path + "/" + dirEntry.name);
					if(success)
					{
						characters.add(info);
					}
				}
			}
		}
	}
	
	void CharacterLoader::loadIcons(const Image& compositeMask)
	{
		for(unsigned int i=0; i<characters.size(); i++)
		{
			String iconPath = characters.get(i).getPath() + "/icon.png";
			//assetManager->loadTexture(iconPath, compositeMask);
			//TODO make some way to save composite masks on reload
			assetManager->loadTexture(iconPath);
		}
	}
	
	void CharacterLoader::loadPortraits()
	{
		for(unsigned int i = 0; i < characters.size(); i++)
		{
			String portraitPath = characters.get(i).getPath() + "/portrait.png";
			assetManager->loadTexture(portraitPath);
		}
	}
	
	void CharacterLoader::reloadAssets(const Image&iconMask)
	{
		assetManager->unload();
		loadIcons(iconMask);
		loadPortraits();
	}
	
	const ArrayList<String>& CharacterLoader::getPaths() const
	{
		return paths;
	}
	
	const ArrayList<CharacterInfo>& CharacterLoader::getCharacters() const
	{
		return characters;
	}
	
	ArrayList<CharacterInfo>& CharacterLoader::getCharacters()
	{
		return characters;
	}
}
