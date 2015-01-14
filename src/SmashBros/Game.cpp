
#include "Game.h"
#include "Global.h"

#include "Menu/TitleScreen.h"

namespace SmashBros
{
	Game::Game()
	{
		menuScreenMgr = nullptr;
		titleScreen = nullptr;
		menuAssetManager = nullptr;
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
		if(menuAssetManager != nullptr)
		{
			delete menuAssetManager;
		}
	}
	
	void Game::initialize()
	{
		getWindow()->setSize(Vector2u(SMASHBROS_WINDOWWIDTH, SMASHBROS_WINDOWHEIGHT));
		getWindow()->getView()->setSize(SMASHBROS_WINDOWWIDTH, SMASHBROS_WINDOWHEIGHT);
		setFPS(60);
		
		menuAssetManager = new AssetManager(*getWindow(), "assets/menu");
	}
	
	void Game::loadContent(AssetManager*assetManager)
	{
		loadMenuAssets(menuAssetManager);
		titleScreen = new Menu::TitleScreen(Menu::MenuData(menuAssetManager));
		menuScreenMgr = new ScreenManager(getWindow(), titleScreen);
	}
	
	void Game::unloadContent(AssetManager*assetManager)
	{
		//
	}
	
	void Game::update(AppData appData)
	{
		appData.setAssetManager(menuAssetManager);
		menuScreenMgr->update(appData);
	}
	
	void Game::draw(AppData appData, Graphics graphics) const
	{
		appData.setAssetManager(menuAssetManager);
		menuScreenMgr->draw(appData, graphics);
	}
	
	void Game::loadMenuAssets(AssetManager*assetManager)
	{
		BatchLoader* batchLoader = new BatchLoader(assetManager);
		
		batchLoader->addTexture("backgrounds/main.png");
		
		batchLoader->addTexture("buttons/back.png");
		batchLoader->addTexture("buttons/main/group.png");
		batchLoader->addTexture("buttons/main/solo.png");
		batchLoader->addTexture("buttons/group/rules.png");
		batchLoader->addTexture("buttons/group/smash.png");
		batchLoader->addTexture("buttons/solo/training.png");
		
		batchLoader->addTexture("characterselect/chip_cpu.png");
		batchLoader->addTexture("characterselect/chip_p1.png");
		batchLoader->addTexture("characterselect/chip_p2.png");
		batchLoader->addTexture("characterselect/chip_p3.png");
		batchLoader->addTexture("characterselect/chip_p4.png");
		batchLoader->addTexture("characterselect/panel_p1.png");
		batchLoader->addTexture("characterselect/panel_p2.png");
		batchLoader->addTexture("characterselect/panel_p3.png");
		batchLoader->addTexture("characterselect/panel_p4.png");
		batchLoader->addTexture("characterselect/panel_cpu.png");
		batchLoader->addTexture("characterselect/panel_na.png");
		batchLoader->addTexture("characterselect/panel_blank.png");
		
		batchLoader->addTexture("elements/headerbar_full.png");
		batchLoader->addTexture("elements/headerbar_small.png");
		
		batchLoader->addFont("fonts/LemonMilk.otf");
		
		batchLoader->addTexture("titlescreen/logo.png");
		batchLoader->addTexture("titlescreen/background.png");
		
		batchLoader->loadAll();
		
		delete batchLoader;
	}
}
