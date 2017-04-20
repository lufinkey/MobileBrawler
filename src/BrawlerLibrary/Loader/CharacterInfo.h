
#pragma once

#include <GameLibrary/GameLibrary.hpp>

namespace BrawlerLibrary
{
	class CharacterInfo
	{
	private:
		fgl::String path;
		fgl::String name;
		fgl::String creator;
		fgl::String version;
		fgl::String minsmashversion;
		
	public:
		CharacterInfo();
		CharacterInfo(const CharacterInfo&);
		~CharacterInfo();
		
		CharacterInfo& operator=(const CharacterInfo&);
		
		bool loadFromPath(const fgl::String&path, fgl::String*error=nullptr);
		bool saveToPath(const fgl::String&path, fgl::String*error=nullptr) const;
		
		const fgl::String& getPath() const;
		const fgl::String& getName() const;
		const fgl::String& getCreator() const;
		const fgl::String& getMinimumSmashVersion() const;
		
		void setPath(const fgl::String&path);
		void setName(const fgl::String&name);
		void setCreator(const fgl::String&creator);
		void setMinimumSmashVersion(const fgl::String&minsmashversion);
	};
}
