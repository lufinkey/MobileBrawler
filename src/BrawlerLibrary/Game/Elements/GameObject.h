
#pragma once

#include <GameLibrary/GameLibrary.h>

namespace BrawlerLibrary
{
	class GameObject : public GameLibrary::SpriteActor
	{
	public:
		GameObject(double x, double y);
		virtual ~GameObject();
		
		virtual void update(GameLibrary::ApplicationData appData) override;
		virtual void draw(GameLibrary::ApplicationData appData, GameLibrary::Graphics graphics) const override;
	};
}
