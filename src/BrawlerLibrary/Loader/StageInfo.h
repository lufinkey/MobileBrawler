
#pragma once

#include <GameLibrary/GameLibrary.h>

namespace BrawlerLibrary
{
	class StageInfo
	{
	private:
		GameLibrary::String path;
		//GameLibrary::String name;
		GameLibrary::String creator;
		GameLibrary::String version;
		//GameLibrary::String minsmashversion; //TODO uncomment and remove public variable
		
	public:
		StageInfo();
		StageInfo(const StageInfo&);
		~StageInfo();
		
		GameLibrary::String name;	//TODO Remove this line and the following
		GameLibrary::String minsmashversion;
		
		StageInfo& operator=(const StageInfo&);
		
		bool loadFromPath(const GameLibrary::String&path, GameLibrary::String*error=nullptr);
		
		const GameLibrary::String& getPath() const;
		const GameLibrary::String& getName() const;
		const GameLibrary::String& getCreator() const;
		const GameLibrary::String& getMinimumSmashVersion() const;
		
		void setPath(const GameLibrary::String&path);
		void setName(const GameLibrary::String&name);
		void setCreator(const GameLibrary::String&creator);
		void setMinimumSmashVersion(const GameLibrary::String&minsmashversion);
	};
}