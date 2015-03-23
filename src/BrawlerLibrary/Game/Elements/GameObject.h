
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
		
	private:
		BrawlGame*gameInstance;
	};
}
