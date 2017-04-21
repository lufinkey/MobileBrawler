
#include "Game.hpp"
#include "Menu/TitleScreen.hpp"
#include "Load/InitialLoadListener.hpp"

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
		#ifdef TARGETPLATFORMTYPE_DESKTOP
			getWindow()->setSize(Vector2u(300, 200));
		#endif
		getWindow()->getViewport()->setMatchesWindow(true);
		setFPS(60);
	}
	
	void Game::loadContent(AssetManager*assetManager)
	{
		menuLoad = new MenuLoad(*getWindow(), "assets/menu");
		moduleLoad = new ModuleLoad(*getWindow(), "assets/characters", "assets/stages");
		smashData = new SmashData(getWindow(), menuLoad, moduleLoad);
		
		InitialLoadListener* loadListener = new InitialLoadListener(getWindow());
		menuLoad->setLoadListener(loadListener);
		
		menuLoad->load();
		
		moduleLoad->setCharacterSelectIconMask(&menuLoad->getCharacterSelectIconMask());
		moduleLoad->setStageSelectIconMask(&menuLoad->getStageSelectIconMask());
		moduleLoad->setStageSelectPreviewMask(&menuLoad->getStageSelectPreviewMask());
		moduleLoad->load();
		
		delete loadListener;

		titleScreen = new Menu::TitleScreen(*smashData);
		menuScreenMgr = new ScreenManager(getWindow(), titleScreen);
	}
	
	void Game::unloadContent(AssetManager*assetManager)
	{
		moduleLoad->unload();
		menuLoad->unload();
	}
	
	void Game::update(ApplicationData appData)
	{
		appData.setAssetManager(menuLoad->getAssetManager());
		menuScreenMgr->update(appData);
	}
	
	void Game::draw(ApplicationData appData, Graphics graphics) const
	{
		appData.setAssetManager(menuLoad->getAssetManager());
		menuScreenMgr->draw(appData, graphics);
	}
}
