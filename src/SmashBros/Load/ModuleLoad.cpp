
#include "ModuleLoad.h"

namespace SmashBros
{
	ModuleLoad::ModuleLoad(Window&window, const String&charactersRoot, const String&stagesRoot)
	{
		characterselect_iconmask = nullptr;
		stageselect_iconmask = nullptr;
		
		characterLoader = new CharacterLoader(window);
		characterLoader->addPath(charactersRoot);
		//stageLoader = new StageLoader(window);
		//stageLoader->addPath(stagesRoot);
	}
	
	ModuleLoad::~ModuleLoad()
	{
		delete characterLoader;
		//delete stageLoader;
	}
	
	void ModuleLoad::addCharactersPath(const String&path)
	{
		characterLoader->addPath(path);
	}
	
	void ModuleLoad::addStagesPath(const String&path)
	{
		//stageLoader->addPath(path);
	}
	
	void ModuleLoad::setCharacterSelectIconMask(Image const* mask)
	{
		characterselect_iconmask = mask;
	}
	
	void ModuleLoad::setStageSelectIconMask(Image const* mask)
	{
		stageselect_iconmask = mask;
	}
	
	CharacterLoader* ModuleLoad::getCharacterLoader() const
	{
		return characterLoader;
	}
	
	/*StageLoader* ModuleLoad::getStageLoader() const
	{
		return stageLoader;
	}*/
	
	void ModuleLoad::load()
	{
		//load character data
		if(characterselect_iconmask!=nullptr)
		{
			characterLoader->loadIcons(*characterselect_iconmask);
		}
		else
		{
			characterLoader->loadIcons();
		}
		characterLoader->loadPortraits();
		
		//load stage data
		/*if(stageselect_iconmask!=nullptr)
		{
			stageLoader->loadIcons(*stageselect_iconmask);
		}
		else
		{
			stageLoader->loadIcons();
		}
		stageLoader->loadThumbnails();*/
	}
	
	void ModuleLoad::reload()
	{
		if(characterselect_iconmask!=nullptr)
		{
			characterLoader->reloadAssets(*characterselect_iconmask);
		}
		else
		{
			characterLoader->reloadAssets();
		}
		
		/*if(stageselect_iconmask!=nullptr)
		{
			stageLoader->reloadAssets(*stageselect_iconmask);
		}
		else
		{
			stageLoader->reloadAssets();
		}*/
	}
	
	void ModuleLoad::unload()
	{
		characterLoader->getAssetManager()->unload();
		//stageLoader->getAssetManager()->unload();
	}
}
