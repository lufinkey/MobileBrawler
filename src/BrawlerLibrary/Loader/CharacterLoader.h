
#include "CharacterInfo.h"

#pragma once

namespace BrawlerLibrary
{
	class CharacterLoader
	{
	private:
		ArrayList<CharacterInfo> characters;
		ArrayList<String> paths;
		
		AssetManager* assetManager;
		
	public:
		CharacterLoader(Window& window);
		~CharacterLoader();
		
		AssetManager* getAssetManager() const;
		
		void addPath(const String&path);
		void reloadPaths();
		
		void loadIcons(const Image&alphaMask=Image());
	};
}
