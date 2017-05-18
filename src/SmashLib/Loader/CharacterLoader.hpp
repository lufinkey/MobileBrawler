
#include "CharacterInfo.hpp"

#pragma once

namespace SmashLib
{
	class CharacterLoader
	{
	public:
		explicit CharacterLoader(fgl::Window* window);
		~CharacterLoader();
		
		fgl::AssetManager* getAssetManager() const;
		
		void addPath(const fgl::String&path);
		void reloadPaths();
		
		void loadIcons(const fgl::Image* compositeMask=nullptr);
		void loadPortraits();
		
		void reloadAssets(const fgl::Image* iconMask=nullptr);
		
		const fgl::ArrayList<fgl::String>& getPaths() const;
		const fgl::ArrayList<CharacterInfo>& getCharacters() const;
		fgl::ArrayList<CharacterInfo>& getCharacters();
		
	private:
		fgl::ArrayList<CharacterInfo> characters;
		fgl::ArrayList<fgl::String> paths;
		
		fgl::AssetManager* assetManager;
	};
}
