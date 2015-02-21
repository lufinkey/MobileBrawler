
#pragma once

#include <GameLibrary/GameLibrary.h>

namespace BrawlerLibrary
{
	class BrawlGame : GameLibrary::ScreenElement
	{
	public:
		BrawlGame(const GameLibrary::RectangleD&frame);
		virtual ~BrawlGame();

		virtual void update(GameLibrary::ApplicationData appData) override;
		virtual void draw(GameLibrary::ApplicationData appData, GameLibrary::Graphics graphics) const override;
		
		virtual GameLibrary::RectangleD getFrame() const;
		
		virtual void startGame();
		virtual void stopGame();
	};
}
