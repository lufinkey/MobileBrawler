
#pragma once

#include <GameLibrary/GameLibrary.hpp>
#include "CharacterLoader.hpp"
#include "StageLoader.hpp"

namespace SmashBros
{
	class ModuleManager
	{
	public:
		ModuleManager(fgl::Window* window, const fgl::String& assetsRoot);
		~ModuleManager();
		
		void addCharactersPath(const fgl::String&);
		void addStagesPath(const fgl::String&);
		
		CharacterLoader* getCharacterLoader() const;
		StageLoader* getStageLoader() const;

		fgl::TextureImage* getCharacterIcon(const fgl::String& identifier) const;
		fgl::TextureImage* getCharacterPortrait(const fgl::String& identifier) const;
		fgl::TextureImage* getStageIcon(const fgl::String& identifier) const;
		fgl::TextureImage* getStagePreview(const fgl::String& identifier) const;
		
		void loadAssets();
		void unloadAssets();

	private:
		fgl::AssetManager* assetManager;

		CharacterLoader* characterLoader;
		StageLoader* stageLoader;
	};
}
