
#include "Game.h"

using namespace GameLibrary;

Game::Game()
{
	rootScrn = nullptr;
	screenMgr = nullptr;
	actor = nullptr;
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
	if(actor != nullptr)
	{
		delete actor;
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
	//assetManager->loadTexture("test.png");
	actor = new Actor(200,200);
	actor->addAnimation("normal", new Animation(assetManager, 1, "test.png"));
}

void Game::unloadContent(GameLibrary::AssetManager*assetManager)
{
	//
}

void Game::update(GameLibrary::AppData appData)
{
	screenMgr->update(appData);
	actor->update(appData);
}

void Game::draw(GameLibrary::AppData appData, GameLibrary::Graphics graphics) const
{
	screenMgr->draw(appData, graphics);
	/*GameLibrary::TextureImage*img = appData.getAssetManager()->getTexture("test.png");
	graphics.drawImage(img, 200,200);*/
	actor->draw(appData, graphics);
}
