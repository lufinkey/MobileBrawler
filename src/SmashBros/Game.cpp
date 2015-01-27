
#include "Game.h"
#include "Global.h"
#include "Menu/TitleScreen.h"

namespace SmashBros
{
	Game::Game()
	{
		smashData = nullptr;
		menuLoad = nullptr;
		moduleLoad = nullptr;
		menuScreenMgr = nullptr;
		titleScreen = nullptr;
		Graphics::setDefaultFontPath("assets/fonts/arial.ttf");
	}
	
	Game::~Game()
	{
		if(menuScreenMgr != nullptr)
		{
			delete menuScreenMgr;
		}
		if(titleScreen != nullptr)
		{
			delete titleScreen;
		}
		if(smashData != nullptr)
		{
			delete smashData;
		}
		if(menuLoad != nullptr)
		{
			delete menuLoad;
		}
		if(moduleLoad != nullptr)
		{
			delete moduleLoad;
		}
	}
	
	void Game::initialize()
	{
		getWindow()->setSize(Vector2u(SMASHBROS_WINDOWWIDTH, SMASHBROS_WINDOWHEIGHT));
		getWindow()->getView()->setSize(SMASHBROS_WINDOWWIDTH, SMASHBROS_WINDOWHEIGHT);
		getWindow()->getView()->setLetterboxed(true);
		setFPS(60);
		menuLoad = new MenuLoad(*getWindow(), "assets/menu");
		moduleLoad = new ModuleLoad(*getWindow(), "assets/characters", "assets/stages");
		smashData = new SmashData(getWindow(), menuLoad, moduleLoad);
	}
	
	void Game::loadContent(AssetManager*assetManager)
	{
		menuLoad->load();
		
		moduleLoad->setCharacterSelectIconMask(&menuLoad->getCharacterSelectIconMask());
		moduleLoad->setStageSelectIconMask(&menuLoad->getStageSelectIconMask());
		moduleLoad->load();

		titleScreen = new Menu::TitleScreen(*smashData);
		menuScreenMgr = new ScreenManager(getWindow(), titleScreen);
	}
	
	void Game::unloadContent(AssetManager*assetManager)
	{
		moduleLoad->unload();
		menuLoad->unload();
	}
	
	void Game::update(AppData appData)
	{
		appData.setAssetManager(menuLoad->getAssetManager());
		menuScreenMgr->update(appData);
	}
	
	void Game::draw(AppData appData, Graphics graphics) const
	{
		appData.setAssetManager(menuLoad->getAssetManager());
		menuScreenMgr->draw(appData, graphics);
	}
}
