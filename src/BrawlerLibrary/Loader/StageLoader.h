//
//  StageLoader.h
//  MobileBrawler
//
//  Created by Keeton on 1/26/15.
//  Copyright (c) 2015 Luis Finke. All rights reserved.
//

#include "StageInfo.h"

#pragma once

namespace BrawlerLibrary {
    using namespace GameLibrary;
    class StageLoader
    {
    private:
        ArrayList<String> paths;
        ArrayList<StageInfo> characters;
        
        AssetManager* assetManager;
        
    public:
        StageLoader(Window& window);
        StageLoader();
        
        AssetManager* getAssetManager() const;
        
        void addPath(const String&path);
        
        void loadIcons(const Image&compositeMask=Image());
        
        const ArrayList<String>& getPaths() const;
        const ArrayList<StageInfo>& getStages() const;
        ArrayList<StageInfo>& getStages();
        
    };
}
