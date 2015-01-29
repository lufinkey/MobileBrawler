
#include "StageLoader.h"

namespace BrawlerLibrary
{
	using namespace GameLibrary;
	
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
		
		ArrayList<FileTools::DirectoryItem> diritems;
		FileTools::getItemsInDirectory(path, &diritems);
		
		for(unsigned int i=0; i<diritems.size(); i++)
		{
			FileTools::DirectoryItem& diritem = diritems.get(i);
			if(diritem.type==FileTools::ITEMTYPE_FOLDER || diritem.type==FileTools::ITEMTYPE_LINK_FOLDER)
			{
				StageInfo info;
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
					for(unsigned int j=0; j<stages.size(); j++)
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
			assetManager->loadTexture(iconPath, compositeMask);
		}
	}
	
	void StageLoader::loadPreviews(const Image&compositeMask)
	{
		for(unsigned int i=0; i<stages.size(); i++)
		{
			String iconPath = stages.get(i).getPath() + "/preview.png";
			assetManager->loadTexture(iconPath, compositeMask);
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