
#include "CharacterInfo.h"

#pragma once

namespace BrawlerLibrary
{
	class CharacterLoader
	{
	private:
		ArrayList<CharacterInfo> characters;
		ArrayList<String> paths;
		
		AssetManager* menuAssets;
		
	public:
		CharacterLoader(Window& window);
		~CharacterLoader();
		
		void addPath(const String&path);
		void reloadPaths();
	};
}
