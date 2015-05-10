
#pragma once

#include <GameLibrary/GameLibrary.h>

namespace BrawlerLibrary
{
	class CharacterInfo
	{
	private:
		GameLibrary::String path;
		GameLibrary::String name;
		GameLibrary::String creator;
		GameLibrary::String version;
		GameLibrary::String minsmashversion;
		
	public:
		CharacterInfo();
		CharacterInfo(const CharacterInfo&);
		~CharacterInfo();
		
		CharacterInfo& operator=(const CharacterInfo&);
		
		bool loadFromPath(const GameLibrary::String&path, GameLibrary::String*error=nullptr);
		bool saveToPath(const GameLibrary::String&path, GameLibrary::String*error=nullptr) const;
		
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
