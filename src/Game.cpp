
#include "Game.h"

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

void Game::loadContent()
{
	getWindow()->getAssetManager()->loadTexture("test.png");
}

void Game::unloadContent()
{
	//
}

void Game::update(GameLibrary::AppData appData)
{
	if(GameLibrary::Keyboard::didKeyPress(GameLibrary::Keyboard::RIGHTARROW))
	{
		GameLibrary::Screen* screen = new GameLibrary::Screen();
		screen->setBackgroundColor(GameLibrary::Color::random());
		screenMgr->push(screen);
	}
	else if(GameLibrary::Keyboard::didKeyPress(GameLibrary::Keyboard::LEFTARROW))
	{
		screenMgr->pop();
	}
	else if(GameLibrary::Keyboard::didKeyPress(GameLibrary::Keyboard::UPARROW))
	{
		GameLibrary::Screen* screen = new GameLibrary::Screen();
		screen->setBackgroundColor(GameLibrary::Color::random());
		screenMgr->getTopScreen()->present(screen);
	}
	else if(GameLibrary::Keyboard::didKeyPress(GameLibrary::Keyboard::DOWNARROW))
	{
		screenMgr->getTopScreen()->dismiss();
	}
	screenMgr->update(appData);
}

void Game::draw(GameLibrary::AppData appData, GameLibrary::Graphics graphics)
{
	screenMgr->draw(appData, graphics);
	GameLibrary::TextureImage*img = getWindow()->getAssetManager()->getTexture("test.png");
	graphics.drawImage(img, 200,200);
}
