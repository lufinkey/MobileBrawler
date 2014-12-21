
#include "Game.h"

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
	rootScrn = new Screen();
	rootScrn->setBackgroundColor(Color::BLUE);
	screenMgr = new ScreenManager(getWindow(), rootScrn);
}

void Game::loadContent(AssetManager*assetManager)
{
	//assetManager->loadTexture("images/tails.png");
	actor = new Actor(200,200);
	actor->addAnimation("tails", new Animation(assetManager, 1, "images/tails.png"));
	actor->addAnimation("sonic", new Animation(assetManager, 30, 8, 1, "images/sonic.png"));
	actor->changeAnimation("sonic", Animation::STOPPED);
	actor->setScale(6.0f);
	actor->setWireframeColor(Color::GREEN);
	actor->setWireframeVisible(true);
	actor->setRotation(45);
}

void Game::unloadContent(AssetManager*assetManager)
{
	//
}

void Game::update(AppData appData)
{
	screenMgr->update(appData);
	actor->x = 200;
	actor->y = 200;
	actor->update(appData);
}

void Game::draw(AppData appData, Graphics graphics) const
{
	screenMgr->draw(appData, graphics);
	/*TextureImage*img = appData.getAssetManager()->getTexture("images/tails.png");
	graphics.drawImage(img, 200,200);*/
	actor->draw(appData, graphics);
	graphics.setColor(Color::GREEN);
	graphics.drawRect(200 - (42*3), 200 - (38*3), 42*6, 38*6);
}
