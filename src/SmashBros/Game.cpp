
#include "Game.hpp"
#include "Menu/TitleScreen.hpp"
#include "Load/InitialLoadListener.hpp"

namespace SmashBros
{
	Game::Game()
	{
		menuAssetManager = nullptr;
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
	
	void Game::loadContent(AssetManager* assetMgr)
	{
		fgl::String assetsRoot = fgl::FileTools::combinePathStrings(assetMgr->getRootDirectory(), "assets");
		fgl::String menuAssetsRoot = fgl::FileTools::combinePathStrings(assetsRoot, "menu");

		menuAssetManager = new fgl::AssetManager(getWindow(), menuAssetsRoot);

		menuLoad = new MenuLoad(menuAssetManager);
		moduleLoad = new ModuleLoad(getWindow(), "assets/characters", "assets/stages");
		smashData = new SmashData(getWindow(), menuLoad, moduleLoad);
		
		InitialLoadListener* loadListener = new InitialLoadListener(getWindow());
		menuLoad->setLoadListener(loadListener);
		
		menuLoad->load();
		
		moduleLoad->setCharacterSelectIconMask(menuLoad->getCharacterSelectIconMask());
		moduleLoad->setStageSelectIconMask(menuLoad->getStageSelectIconMask());
		moduleLoad->setStageSelectPreviewMask(menuLoad->getStageSelectPreviewMask());
		moduleLoad->load();

		menuLoad->setLoadListener(nullptr);
		delete loadListener;

		titleScreen = new Menu::TitleScreen(*smashData);
		menuScreenMgr = new ScreenManager(getWindow(), titleScreen);
	}
	
	void Game::unloadContent(AssetManager* assetMgr)
	{
		moduleLoad->unload();
		menuLoad->unload();
		delete menuAssetManager;
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
