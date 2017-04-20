
#include "CharacterInfo.h"

#pragma once

namespace BrawlerLibrary
{
	class CharacterLoader
	{
	private:
		fgl::ArrayList<CharacterInfo> characters;
		fgl::ArrayList<fgl::String> paths;
		
		fgl::AssetManager* assetManager;
		
	public:
		explicit CharacterLoader(fgl::Window& window);
		~CharacterLoader();
		
		fgl::AssetManager* getAssetManager() const;
		
		void addPath(const fgl::String&path);
		void reloadPaths();
		
		void loadIcons(const fgl::Image&compositeMask=fgl::Image());
		void loadPortraits();
		
		void reloadAssets(const fgl::Image&iconMask=fgl::Image());
		
		const fgl::ArrayList<fgl::String>& getPaths() const;
		const fgl::ArrayList<CharacterInfo>& getCharacters() const;
		fgl::ArrayList<CharacterInfo>& getCharacters();
	};
}
