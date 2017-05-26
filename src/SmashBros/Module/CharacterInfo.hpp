
#pragma once

#include <GameLibrary/GameLibrary.hpp>

namespace SmashBros
{
	class CharacterInfo
	{
	public:
		CharacterInfo();
		~CharacterInfo();
		
		bool loadFromPath(const fgl::String& path, fgl::String*error=nullptr);
		bool saveToPath(const fgl::String& path, fgl::String*error=nullptr) const;
		
		const fgl::String& getPath() const;
		const fgl::String& getIdentifier() const;
		const fgl::String& getName() const;
		const fgl::String& getCreator() const;
		const fgl::String& getMinimumSmashVersion() const;
		
		void setPath(const fgl::String& path);
		void setIdentifier(const fgl::String& identifier);
		void setName(const fgl::String& name);
		void setCreator(const fgl::String& creator);
		void setMinimumSmashVersion(const fgl::String& minsmashversion);

		fgl::String getIconPath() const;
		fgl::String getPortraitPath() const;
		
	private:
		fgl::String path;
		fgl::String identifier;
		fgl::String name;
		fgl::String creator;
		fgl::String version;
		fgl::String minsmashversion;
	};
}
