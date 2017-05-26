
#pragma once

#include "CharacterInfo.hpp"

namespace SmashBros
{
	class CharacterLoader
	{
	public:
		CharacterLoader();
		
		void addPath(const fgl::String& path);
		void reloadPaths();
		
		const fgl::ArrayList<fgl::String>& getPaths() const;
		const fgl::ArrayList<CharacterInfo>& getCharacters() const;
		bool hasCharacter(const fgl::String& identifier) const;
		const CharacterInfo& getCharacterInfo(const fgl::String& identifier) const;

		fgl::ArrayList<fgl::String> getIconPaths() const;
		fgl::ArrayList<fgl::String> getPortraitPaths() const;
		
	private:
		fgl::ArrayList<CharacterInfo> characters;
		fgl::ArrayList<fgl::String> paths;
	};
}
