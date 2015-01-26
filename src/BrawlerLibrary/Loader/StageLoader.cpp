//
//  StageLoader.cpp
//  MobileBrawler
//
//  Created by Keeton on 1/26/15.
//  Copyright (c) 2015 Luis Finke. All rights reserved.
//

#include "StageLoader.h"

namespace BrawlerLibrary {
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
                //TODO see if minsmashversion is compatible
                //TODO compare minsmashversion to current application
                if (info.minsmashversion == "1.0") {
                    // check if minsmashversion is compatible
                    GameLibrary::Console::writeLine("Minsmashversion is compatible");
                }
                else {
                    GameLibrary::Console::writeLine("Minsmashversion is NOT compatible");
                }
                if(success)
                {
                    bool alreadyAdded = false;
                    for(unsigned int j=0; j<characters.size(); j++)
                    {
                        StageInfo&cmp = characters.get(j);
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
    
    void StageLoader::loadIcons(const Image&compositeMask)
    {
        for(unsigned int i=0; i<characters.size(); i++)
        {
            String iconPath = characters.get(i).getPath() + "/preview.png";
            assetManager->unloadTexture(iconPath);
            assetManager->loadTexture(iconPath, compositeMask);
        }
    }
    
    const ArrayList<String>& StageLoader::getPaths() const
    {
        return paths;
    }
    
    const ArrayList<StageInfo>& StageLoader::getStages() const
    {
        return characters;
    }
    
    ArrayList<StageInfo>& StageLoader::getStages()
    {
        return characters;
    }
}