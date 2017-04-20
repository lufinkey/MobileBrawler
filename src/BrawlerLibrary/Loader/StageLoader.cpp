
#include "StageLoader.hpp"

namespace BrawlerLibrary
{
	using namespace fgl;
	
	StageLoader::StageLoader(Window&window)
	{
		assetManager = new AssetManager(window);
	}
	
	StageLoader::StageLoader()
	{
		delete assetManager;
	}
	
	AssetManager* StageLoader::getAssetManager() const
	{
		return assetManager;
	}
	
	void StageLoader::addPath(const String&path)
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
				StageInfo info;
				bool success = info.loadFromPath(path + "/" + dirEntry.name);
				//TODO see if minsmashversion is compatible
				if(success)
				{
					bool alreadyAdded = false;
					for(size_t j=0; j<stages.size(); j++)
					{
						StageInfo&cmp = stages.get(j);
						if(info.getName().equals(cmp.getName()) && info.getCreator().equals(cmp.getCreator()))
						{
							alreadyAdded = true;
							j = stages.size();
						}
					}
					if(!alreadyAdded)
					{
						stages.add(info);
					}
				}
			}
		}
	}
	
	void StageLoader::loadIcons(const Image&compositeMask)
	{
		for(unsigned int i=0; i<stages.size(); i++)
		{
			String iconPath = stages.get(i).getPath() + "/icon.png";
			//assetManager->loadTexture(iconPath, compositeMask);
			//TODO add some way to save composite masks when reloading
			assetManager->loadTexture(iconPath);
		}
	}
	
	void StageLoader::loadPreviews(const Image&compositeMask)
	{
		for(unsigned int i=0; i<stages.size(); i++)
		{
			String iconPath = stages.get(i).getPath() + "/preview.png";
			//assetManager->loadTexture(iconPath, compositeMask);
			//TODO add some way to save composite masks when reloading
			assetManager->loadTexture(iconPath);
		}
	}
	
    void StageLoader::reloadAssets(const Image&iconMask, const Image&previewMask)
    {
        assetManager->unload();
		loadIcons(iconMask);
		loadPreviews(previewMask);
    }
    
	const ArrayList<String>& StageLoader::getPaths() const
	{
		return paths;
	}
	
	const ArrayList<StageInfo>& StageLoader::getStages() const
	{
		return stages;
	}
	
	ArrayList<StageInfo>& StageLoader::getStages()
	{
		return stages;
	}
}
