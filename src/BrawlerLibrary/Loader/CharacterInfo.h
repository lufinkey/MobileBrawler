
#pragma once

#include <GameLibrary/GameLibrary.h>

namespace BrawlerLibrary
{
	using namespace GameLibrary;
	
	class CharacterInfo
	{
	private:
		String path;
		String name;
		String creator;
		String version;
		String minsmashversion;
		
	public:
		CharacterInfo();
		CharacterInfo(const CharacterInfo&);
		~CharacterInfo();
		
		CharacterInfo& operator=(const CharacterInfo&);
		
		bool loadFromPath(const String&path, String*error=nullptr);
		
		const String& getPath() const;
		const String& getName() const;
		const String& getCreator() const;
		const String& getMinimumSmashVersion() const;
		
		void setPath(const String&path);
		void setName(const String&name);
		void setCreator(const String&creator);
		void setMinimumSmashVersion(const String&minsmashversion);
	};
}
