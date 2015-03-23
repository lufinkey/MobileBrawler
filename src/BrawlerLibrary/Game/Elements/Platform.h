
#pragma once

#include "PhysicalGameObject.h"

namespace BrawlerLibrary
{
	class Platform : public PhysicalGameObject
	{
	public:
		Platform(BrawlGame*gameInstance, const GameLibrary::Vector2d&position);
		virtual ~Platform();
		
		virtual void update(GameLibrary::ApplicationData appData) override;
		virtual void draw(GameLibrary::ApplicationData appData, GameLibrary::Graphics graphics) const override;
		
	private:
		GameLibrary::String name;
	};
}
