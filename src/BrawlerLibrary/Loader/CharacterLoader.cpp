
#include "CharacterLoader.h"

namespace BrawlerLibrary
{
	CharacterLoader::CharacterLoader(Window&window)
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
		
		ArrayList<FileTools::DirectoryItem> diritems;
		FileTools::getItemsInDirectory(path, &diritems);
		
		for(unsigned int i=0; i<diritems.size(); i++)
		{
			FileTools::DirectoryItem& diritem = diritems.get(i);
			if(diritem.type==FileTools::ITEMTYPE_FOLDER || diritem.type==FileTools::ITEMTYPE_LINK_FOLDER)
			{
				CharacterInfo info;
				bool success = info.loadFromPath(path + "/" + diritem.name);
				//TODO see if minsmashversion is compatible using a list of compatible versions
                //TODO compare minsmashversion to current application and handle accordingly
                /*if (info.minsmashversion == "1.0") {
                    // check if minsmashversion is compatible
                    GameLibrary::Console::writeLine("Minsmashversion is compatible");
                }
                else {
                    GameLibrary::Console::writeLine("Minsmashversion is NOT compatible");
                }*/ //COMMENTED because it doesn't account for failure to load for other reasons, or handles the incorrect smash version
				//This will be handled later, as we don't yet have a plan for this.
				if(success)
				{
					bool alreadyAdded = false;
					for(unsigned int j=0; j<characters.size(); j++)
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
			
			ArrayList<FileTools::DirectoryItem> diritems;
			FileTools::getItemsInDirectory(path, &diritems);
			
			for(unsigned int j=0; j<diritems.size(); j++)
			{
				FileTools::DirectoryItem& diritem = diritems.get(j);
				if(diritem.type==FileTools::ITEMTYPE_FOLDER || diritem.type==FileTools::ITEMTYPE_LINK_FOLDER)
				{
					CharacterInfo info;
					bool success = info.loadFromPath(path + "/" + diritem.name);
					if(success)
					{
						characters.add(info);
					}
				}
			}
		}
	}
	
	void CharacterLoader::loadIcons(const Image&compositeMask)
	{
		for(unsigned int i=0; i<characters.size(); i++)
		{
			String iconPath = characters.get(i).getPath() + "/icon.png";
			assetManager->loadTexture(iconPath, compositeMask);
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
