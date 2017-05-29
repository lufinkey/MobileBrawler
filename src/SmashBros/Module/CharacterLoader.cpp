
#include "CharacterLoader.hpp"

namespace SmashBros
{
	CharacterLoader::CharacterLoader()
	{
		//
	}
	
	void CharacterLoader::addPath(const fgl::String& path)
		//TODO add ability to pass in ArrayList for error catching
	{
		//ensure a duplicate path does not get added
		for(auto& cmpPath : paths)
		{
			if(path==cmpPath)
			{
				return;
			}
		}

		//add path
		paths.add(path);
		
		//load entries from path
		fgl::ArrayList<fgl::FileTools::DirectoryEntry> dirEntries;
		fgl::FileTools::readEntriesFromDirectory(path, &dirEntries);
		for(auto& dirEntry : dirEntries)
		{
			if(dirEntry.type==fgl::FileTools::ENTRYTYPE_FOLDER || dirEntry.type==fgl::FileTools::ENTRYTYPE_LINK_FOLDER)
			{
				CharacterInfo info;
				auto characterPath = fgl::FileTools::combinePathStrings(path, dirEntry.name);
				bool success = info.loadFromPath(characterPath);
				//TODO see if minsmashversion is compatible
				if(success)
				{
					if(!hasCharacter(info.getIdentifier()))
					{
						characters.add(info);
					}
				}
			}
		}
	}
	
	void CharacterLoader::reloadPaths()
	{
		characters.clear();
		for(auto& path : paths)
		{
			fgl::ArrayList<fgl::FileTools::DirectoryEntry> dirEntries;
			fgl::FileTools::readEntriesFromDirectory(path, &dirEntries);
			
			for(auto& dirEntry : dirEntries)
			{
				if(dirEntry.type==fgl::FileTools::ENTRYTYPE_FOLDER || dirEntry.type==fgl::FileTools::ENTRYTYPE_LINK_FOLDER)
				{
					CharacterInfo info;
					auto characterPath = fgl::FileTools::combinePathStrings(path, dirEntry.name);
					bool success = info.loadFromPath(characterPath);
					//TODO see if minsmashversion is compatible
					if(success)
					{
						if(!hasCharacter(info.getIdentifier()))
						{
							characters.add(info);
						}
					}
				}
			}
		}
	}
	
	const fgl::ArrayList<fgl::String>& CharacterLoader::getPaths() const
	{
		return paths;
	}
	
	const fgl::ArrayList<CharacterInfo>& CharacterLoader::getCharacters() const
	{
		return characters;
	}

	bool CharacterLoader::hasCharacter(const fgl::String& identifier) const
	{
		for(auto& character : characters)
		{
			if(character.getIdentifier()==identifier)
			{
				return true;
			}
		}
		return false;
	}

	const CharacterInfo& CharacterLoader::getCharacterInfo(const fgl::String& identifier) const
	{
		for(auto& character : characters)
		{
			if(character.getIdentifier()==identifier)
			{
				return character;
			}
		}
		throw fgl::IllegalArgumentException("identifier", "no character exists with the given identifier");
	}

	fgl::ArrayList<fgl::String> CharacterLoader::getIconPaths() const
	{
		fgl::ArrayList<fgl::String> iconPaths;
		iconPaths.reserve(characters.size());
		for(auto& character : characters)
		{
			iconPaths.add(character.getIconPath());
		}
		return iconPaths;
	}

	fgl::ArrayList<fgl::String> CharacterLoader::getPortraitPaths() const
	{
		fgl::ArrayList<fgl::String> portraitPaths;
		portraitPaths.reserve(characters.size());
		for(auto& character : characters)
		{
			portraitPaths.add(character.getPortraitPath());
		}
		return portraitPaths;
	}

	void CharacterLoader::registerCharacter(const fgl::String& identifier, const std::function<fl::Character*(fgl::AssetManager*)>& initializer)
	{
		if(characterInitializers.has(identifier))
		{
			throw fgl::IllegalArgumentException("identifier", "character has already been registered");
		}
		characterInitializers[identifier] = initializer;
	}

	void CharacterLoader::unregisterCharacter(const fgl::String& identifier)
	{
		characterInitializers.remove(identifier);
	}

	fl::Character* CharacterLoader::createCharacter(const fgl::String& identifier, fgl::AssetManager* assetManager) const
	{
		return characterInitializers.get(identifier, [](fgl::AssetManager* assetManager) -> fl::Character* {
			return nullptr;
		})(assetManager);
	}
}
