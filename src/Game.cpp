
#include "Game.h"

Game::Game()
{
	rootScrn = nullptr;
	screenMgr = nullptr;
	actor = nullptr;
	textActor = nullptr;
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
	if(textActor != nullptr)
	{
		delete textActor;
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
	actor->addAnimation("sonic", new Animation(assetManager, 16, 8, 1, "images/sonic.png"));
	actor->changeAnimation("sonic", Animation::FORWARD);
	actor->setScale(6.0f);
	actor->setFrameColor(Color::GREEN);
	actor->setFrameVisible(true);
	actor->setRotation(45);

	textActor = new TextActor(400,200, "Hello World\nThis is Finke\nThere are a few things I need\nI need you to kill yourself");
	textActor->setFrameColor(Color::GREEN);
	textActor->setFrameVisible(true);
	textActor->setRotation(45);
	textActor->setScale(2.0f);
	textActor->setAlignment(TextActor::ALIGN_TOPLEFT);
	textActor->setLineSpacing(-40);
}

void Game::unloadContent(AssetManager*assetManager)
{
	//
}

void Game::update(AppData appData)
{
	screenMgr->update(appData);
	actor->update(appData);
	textActor->update(appData);
}

void Game::draw(AppData appData, Graphics graphics) const
{
	screenMgr->draw(appData, graphics);
	/*TextureImage*img = appData.getAssetManager()->getTexture("images/tails.png");
	graphics.drawImage(img, 200,200);*/
	actor->draw(appData, graphics);
	textActor->draw(appData, graphics);
	graphics.setColor(Color::RED);
	graphics.fillRect(400,200,2,2);
}
