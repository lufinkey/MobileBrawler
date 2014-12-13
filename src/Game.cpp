
#include "Game.h"

Game::Game()
{
	//
}

Game::~Game()
{
	//
}

void Game::initialize()
{
	//
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
	//
}

void Game::draw(GameLibrary::AppData appData, GameLibrary::Graphics g)
{
	GameLibrary::TextureImage*img = getWindow()->getAssetManager()->getTexture("test.png");
	g.drawImage(img, 200,200);
}
