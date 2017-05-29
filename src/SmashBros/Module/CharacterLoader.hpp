
#pragma once

#include "CharacterInfo.hpp"
#include <fightlib/fightlib.hpp>

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

		void registerCharacter(const fgl::String& identifier, const std::function<fl::Character*(fgl::AssetManager*)>& initializer);
		void unregisterCharacter(const fgl::String& identifier);
		fl::Character* createCharacter(const fgl::String& identifier, fgl::AssetManager* assetManager) const;
		
	private:
		fgl::ArrayList<CharacterInfo> characters;
		fgl::ArrayList<fgl::String> paths;

		fgl::BasicDictionary<fgl::String, std::function<fl::Character*(fgl::AssetManager* assetManager)>> characterInitializers;
	};
}
