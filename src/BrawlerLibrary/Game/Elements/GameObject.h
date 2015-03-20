
#pragma once

#include "ActionPerformer/ActionPerformer.h"

namespace BrawlerLibrary
{
	class BrawlGame;
	
	class GameObject : public ActionPerformer
	{
	public:
		GameObject(BrawlGame*gameInstance, const GameLibrary::Vector2d&position);
		virtual ~GameObject();
		
		virtual void update(GameLibrary::ApplicationData appData) override;
		virtual void draw(GameLibrary::ApplicationData appData, GameLibrary::Graphics graphics) const override;
		
	private:
		BrawlGame*gameInstance;
	};
}
