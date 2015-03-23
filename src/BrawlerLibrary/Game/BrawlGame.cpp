
#include "BrawlGame.h"

using namespace GameLibrary;

namespace BrawlerLibrary
{
	BrawlGame::BrawlGame(const RectangleD&frame, const GameLibrary::Vector2d&natSize) : ScreenElement(frame)
	{
		camera = nullptr;
		naturalSize = natSize;
	}
	
	BrawlGame::~BrawlGame()
	{
		//
	}
	
	void BrawlGame::update(ApplicationData appData)
	{
		//
	}
	
	void BrawlGame::drawMain(ApplicationData appData, Graphics graphics) const
	{
		//
	}
	
	void BrawlGame::startGame()
	{
		//
	}
	
	void BrawlGame::stopGame()
	{
		//
	}
	
	Camera* BrawlGame::getCamera() const
	{
		return camera;
	}
	
	const Vector2d& BrawlGame::getNaturalSize() const
	{
		return naturalSize;
	}
}
