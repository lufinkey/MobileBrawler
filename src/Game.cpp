
#include "Game.h"

using namespace GameLibrary;

Game::Game()
{
	rootScrn = nullptr;
	screenMgr = nullptr;
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
	rootScrn = new GameLibrary::Screen();
	rootScrn->setBackgroundColor(GameLibrary::Color::BLUE);
	screenMgr = new GameLibrary::ScreenManager(getWindow(), rootScrn);
}

void Game::loadContent(GameLibrary::AssetManager*assetManager)
{
	assetManager->loadTexture("test.png");
}

void Game::unloadContent(GameLibrary::AssetManager*assetManager)
{
	//
}

void Game::update(GameLibrary::AppData appData)
{
	screenMgr->update(appData);
}

void Game::draw(GameLibrary::AppData appData, GameLibrary::Graphics graphics)
{
	screenMgr->draw(appData, graphics);
	GameLibrary::TextureImage*img = appData.getAssetManager()->getTexture("test.png");
	graphics.drawImage(img, 200,200);
}
