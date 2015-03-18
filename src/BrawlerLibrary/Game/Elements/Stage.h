
#pragma once

#include <GameLibrary/GameLibrary.h>

namespace BrawlerLibrary
{
	class BrawlGame;
	
	class Stage : GameLibrary::Drawable
	{
	public:
		Stage(BrawlGame*gameInstance, const GameLibrary::Vector2d&position);
		virtual ~Stage();
		
		virtual void update(GameLibrary::ApplicationData appData) override;
		virtual void draw(GameLibrary::ApplicationData appData, GameLibrary::Graphics graphics) const override;
	};
}
