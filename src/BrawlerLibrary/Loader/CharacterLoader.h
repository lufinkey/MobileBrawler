
#include "CharacterInfo.h"

#pragma once

namespace BrawlerLibrary
{
	class CharacterLoader
	{
	private:
		GameLibrary::ArrayList<CharacterInfo> characters;
		GameLibrary::ArrayList<GameLibrary::String> paths;
		
		GameLibrary::AssetManager* assetManager;
		
	public:
		CharacterLoader(GameLibrary::Window& window);
		~CharacterLoader();
		
		GameLibrary::AssetManager* getAssetManager() const;
		
		void addPath(const GameLibrary::String&path);
		void reloadPaths();
		
		void loadIcons(const GameLibrary::Image&compositeMask=GameLibrary::Image());
		void loadPortraits();
		
		void reloadAssets(const GameLibrary::Image&iconMask=GameLibrary::Image());
		
		const GameLibrary::ArrayList<GameLibrary::String>& getPaths() const;
		const GameLibrary::ArrayList<CharacterInfo>& getCharacters() const;
		GameLibrary::ArrayList<CharacterInfo>& getCharacters();
	};
}
