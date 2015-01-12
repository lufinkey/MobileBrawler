
#include "Game.h"
#include "Global.h"

#include "Menu/MainMenu.h"

namespace SmashBros
{
	Game::Game()
	{
		screenMgr = nullptr;
		rootScrn = nullptr;
	}

	Game::~Game()
	{
		if(screenMgr != nullptr)
		{
			delete screenMgr;
		}
		if(rootScrn != nullptr)
		{
			delete rootScrn;
		}
	}

	void Game::initialize()
	{
		//this->getWindow()->setSize(Vector2u(SMASHBROS_WINDOWWIDTH, SMASHBROS_WINDOWHEIGHT));
		this->getWindow()->getView()->setSize(SMASHBROS_WINDOWWIDTH, SMASHBROS_WINDOWHEIGHT);
		setFPS(60);
	}

	void Game::loadContent(AssetManager*assetManager)
	{
		rootScrn = new Menu::MainMenu(assetManager);
		screenMgr = new ScreenManager(getWindow(), rootScrn);
	}

	void Game::unloadContent(AssetManager*assetManager)
	{
		//
	}

	void Game::update(AppData appData)
	{
		screenMgr->update(appData);
	}

	void Game::draw(AppData appData, Graphics graphics) const
	{
		screenMgr->draw(appData, graphics);
	}
}
