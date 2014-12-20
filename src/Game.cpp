
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
	setFPS(60);
	rootScrn = new GameLibrary::Screen();
	rootScrn->setBackgroundColor(GameLibrary::Color::BLUE);
	screenMgr = new GameLibrary::ScreenManager(getWindow(), rootScrn);
}

void Game::loadContent(GameLibrary::AssetManager*assetManager)
{
	//assetManager->loadTexture("images/tails.png");
	actor = new Actor(200,200);
	actor->addAnimation("tails", new Animation(assetManager, 1, "images/tails.png"));
	actor->addAnimation("sonic", new Animation(assetManager, 30, 8, 1, "images/sonic.png"));
	actor->changeAnimation("sonic", Animation::FORWARD);
	actor->setScale(6.0f);
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
	GameLibrary::TextureImage* img = appData.getAssetManager()->getTexture("images/sonic.png");
	/*GameLibrary::TextureImage*img = appData.getAssetManager()->getTexture("images/tails.png");
	graphics.drawImage(img, 200,200);*/
	actor->draw(appData, graphics);
	graphics.setColor(Color::GREEN);
	graphics.drawRect(200 - (42*3), 200 - (38*3), 42*6, 38*6);
}
