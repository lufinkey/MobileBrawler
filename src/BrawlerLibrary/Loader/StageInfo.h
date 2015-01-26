//
//  StageInfo.h
//  MobileBrawler
//
//  Created by Keeton on 1/26/15.
//  Copyright (c) 2015 Luis Finke. All rights reserved.
//

#pragma once

#include <GameLibrary/GameLibrary.h>

namespace BrawlerLibrary
{
    using namespace GameLibrary;
    
    class StageInfo
    {
    private:
        String path;
        String name;
        String creator;
        String version;
        
    public:
        StageInfo();
        StageInfo(const StageInfo&);
        ~StageInfo();
        
        StageInfo& operator=(const StageInfo&);
        
        bool loadFromPath(const String&path, String*error=nullptr);
        
        const String& getPath() const;
        const String& getName() const;
        const String& getCreator() const;
        const String& getMinimumSmashVersion() const;
        
        void setPath(const String&path);
        void setName(const String&name);
        void setCreator(const String&creator);
        void setMinimumSmashVersion(const String&minsmashversion);
        
        String minsmashversion;
    };
}