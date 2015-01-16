
#pragma once

#include <GameLibraryImport.hpp>

namespace BrawlerLibrary
{
	class CharacterInfo
	{
	private:
		String path;
		String name;
		String creator;
		String minsmashversion;
		
	public:
		CharacterInfo();
		CharacterInfo(const CharacterInfo&);
		~CharacterInfo();
		
		CharacterInfo& operator=(const CharacterInfo&);
		
		bool loadFromPath(const String&path, String&error);
		
		const String& getPath() const;
		const String& getName() const;
		const String& getMinimumSmashVersion() const;
		
		void setPath(const String&path);
		void setName(const String&name);
		void setMinimumSmashVersion() const;
	};
}
