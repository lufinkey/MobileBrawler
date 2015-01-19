
#include "CharacterLoader.h"

namespace BrawlerLibrary
{
	CharacterLoader::CharacterLoader()
	{
		//
	}
	
	CharacterLoader::~CharacterLoader()
	{
		//
	}
	
	void CharacterLoader::addPath(const String&path)
	{
		for(unsigned int i=0; i<paths.size(); i++)
		{
			if(path.equals(paths.get(i)))
			{
				return;
			}
		}
		
		//
	}
	
	void CharacterLoader::reloadPaths()
	{
		//
	}
}
