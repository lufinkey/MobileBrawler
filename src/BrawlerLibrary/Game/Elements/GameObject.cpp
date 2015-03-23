
#include "GameObject.h"
#include "../BrawlGame.h"

namespace BrawlerLibrary
{
	GameObject::GameObject(BrawlGame*gameInst, const GameLibrary::Vector2d&position) : ActionPerformer(position)
	{
		gameInstance = gameInst;
	}
	
	GameObject::~GameObject()
	{
		//
	}
}
