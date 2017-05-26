
#include "ModuleManager.hpp"

namespace SmashBros
{
	ModuleManager::ModuleManager(fgl::Window* window, const fgl::String& assetsRoot)
	{
		assetManager = new fgl::AssetManager(window, assetsRoot);

		auto charactersRoot = fgl::FileTools::combinePathStrings(assetsRoot, "characters");
		auto stagesRoot = fgl::FileTools::combinePathStrings(assetsRoot, "stages");
		
		characterLoader = new CharacterLoader();
		characterLoader->addPath(charactersRoot);
		stageLoader = new StageLoader();
		stageLoader->addPath(stagesRoot);
	}
	
	ModuleManager::~ModuleManager()
	{
		delete characterLoader;
		delete stageLoader;
		delete assetManager;
	}
	
	void ModuleManager::addCharactersPath(const fgl::String& path)
	{
		characterLoader->addPath(path);
	}
	
	void ModuleManager::addStagesPath(const fgl::String& path)
	{
		stageLoader->addPath(path);
	}
	
	CharacterLoader* ModuleManager::getCharacterLoader() const
	{
		return characterLoader;
	}
	
	StageLoader* ModuleManager::getStageLoader() const
	{
		return stageLoader;
	}

	fgl::TextureImage* ModuleManager::getCharacterIcon(const fgl::String& identifier) const
	{
		auto& characterInfo = characterLoader->getCharacterInfo(identifier);
		return assetManager->getTexture(characterInfo.getIconPath());
	}

	fgl::TextureImage* ModuleManager::getCharacterPortrait(const fgl::String& identifier) const
	{
		auto& characterInfo = characterLoader->getCharacterInfo(identifier);
		return assetManager->getTexture(characterInfo.getPortraitPath());
	}

	fgl::TextureImage* ModuleManager::getStageIcon(const fgl::String& identifier) const
	{
		auto& stageInfo = stageLoader->getStageInfo(identifier);
		return assetManager->getTexture(stageInfo.getIconPath());
	}

	fgl::TextureImage* ModuleManager::getStagePreview(const fgl::String& identifier) const
	{
		auto& stageInfo = stageLoader->getStageInfo(identifier);
		return assetManager->getTexture(stageInfo.getPreviewPath());
	}

	void ModuleManager::loadAssets()
	{
		//load icon masks
		auto characterselect_iconmask = assetManager->loadImage("menu/characterselect/icon_mask.png");
		auto stageselect_iconmask = assetManager->loadImage("menu/stageselect/icon_mask.png");
		auto stageselect_previewmask = assetManager->loadImage("menu/stageselect/preview_mask.png");

		//load character data
		for(auto& iconPath : characterLoader->getIconPaths())
		{
			assetManager->loadMaskedTexture(iconPath, characterselect_iconmask);
		}
		for(auto& portraitPath : characterLoader->getPortraitPaths())
		{
			assetManager->loadTexture(portraitPath);
		}
		
		//load stage data
		for(auto& iconPath : stageLoader->getIconPaths())
		{
			assetManager->loadMaskedTexture(iconPath, stageselect_iconmask);
		}
		for(auto& previewPath : stageLoader->getPreviewPaths())
		{
			assetManager->loadMaskedTexture(previewPath, stageselect_previewmask);
		}
	}
	
	void ModuleManager::unloadAssets()
	{
		assetManager->unload();
	}
}
