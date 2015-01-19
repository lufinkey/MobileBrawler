
#include "CharacterInfo.h"

#pragma once

namespace BrawlerLibrary
{
	class CharacterLoader
	{
	private:
		ArrayList<CharacterInfo> characters;
		ArrayList<String> paths;
		
	public:
		CharacterLoader();
		~CharacterLoader();
		
		void addPath(const String&path);
		void reloadPaths();
	};
}
