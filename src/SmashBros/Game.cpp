
#include "Game.h"
#include "Global.h"
#include "Menu/TitleScreen.h"

namespace SmashBros
{
	Game::Game()
	{
		smashData = nullptr;
		menuAssetManager = nullptr;
		characterLoader = nullptr;
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
		if(menuAssetManager != nullptr)
		{
			delete menuAssetManager;
		}
		if(characterLoader != nullptr)
		{
			delete characterLoader;
		}
	}
	
	void Game::initialize()
	{
		getWindow()->setSize(Vector2u(SMASHBROS_WINDOWWIDTH, SMASHBROS_WINDOWHEIGHT));
		getWindow()->getView()->setSize(SMASHBROS_WINDOWWIDTH, SMASHBROS_WINDOWHEIGHT);
		getWindow()->getView()->setLetterboxed(true);
		setFPS(60);
		characterLoader = new CharacterLoader(*getWindow());
		menuAssetManager = new AssetManager(*getWindow(), "assets/menu");
		//TODO fix when implementing placement plists
		smashData = new SmashData(getWindow(), characterLoader, nullptr, MenuData(menuAssetManager, Dictionary(), Dictionary()));
	}
	
	void Game::loadContent(AssetManager*assetManager)
	{
		//TODO change this when implementing themes
		characterselect_iconmask.loadFromFile("assets/menu/characterselect/icon_mask.png");
		loadMenuAssets(menuAssetManager);
		characterLoader->addPath("assets/characters");
		characterLoader->loadIcons(characterselect_iconmask);
		characterLoader->loadPortraits();
		titleScreen = new Menu::TitleScreen(*smashData);
		menuScreenMgr = new ScreenManager(getWindow(), titleScreen);
	}
	
	void Game::unloadContent(AssetManager*assetManager)
	{
		characterLoader->getAssetManager()->unload();
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
		batchLoader->addTexture("characterselect/panel_background_p1.png");
		batchLoader->addTexture("characterselect/panel_background_p2.png");
		batchLoader->addTexture("characterselect/panel_background_p3.png");
		batchLoader->addTexture("characterselect/panel_background_p4.png");
		batchLoader->addTexture("characterselect/panel_background_cpu.png");
		batchLoader->addTexture("characterselect/panel_background_na.png");
		batchLoader->addTexture("characterselect/panel_background_blank.png");
		batchLoader->addTexture("characterselect/panel_overlay_p1.png");
		batchLoader->addTexture("characterselect/panel_overlay_p2.png");
		batchLoader->addTexture("characterselect/panel_overlay_p3.png");
		batchLoader->addTexture("characterselect/panel_overlay_p4.png");
		batchLoader->addTexture("characterselect/panel_overlay_cpu.png");
		batchLoader->addTexture("characterselect/panel_overlay_na.png");
		batchLoader->addTexture("characterselect/panel_overlay_blank.png");
		batchLoader->addTexture("characterselect/icon_frame.png");
		batchLoader->addTexture("characterselect/readytofight_banner.png");
		
		batchLoader->addTexture("elements/button_arrow_down.png");
		batchLoader->addTexture("elements/button_arrow_left.png");
		batchLoader->addTexture("elements/button_arrow_right.png");
		batchLoader->addTexture("elements/button_arrow_up.png");
		batchLoader->addTexture("elements/headerbar_full.png");
		batchLoader->addTexture("elements/headerbar_small.png");
		batchLoader->addTexture("elements/menu_bar.png");
		batchLoader->addTexture("elements/rules_bar.png");
		
		batchLoader->addFont("fonts/default.ttf");
		
		batchLoader->addTexture("titlescreen/logo.png");
		batchLoader->addTexture("titlescreen/background.png");
		
		batchLoader->loadAll();
		
		delete batchLoader;
	}
}
