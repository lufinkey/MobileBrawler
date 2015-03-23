
#include "GameObject.h"
#include "../BrawlGame.h"

namespace BrawlerLibrary
{
	using namespace GameLibrary;
	
	GameObject::GameObject(BrawlGame*gameInst, const GameLibrary::Vector2d&position) : ActionPerformer(position)
	{
		gameInstance = gameInst;
		zdepth = 0.5;
	}
	
	GameObject::~GameObject()
	{
		//
	}
	
	void GameObject::setZDepth(double z)
	{
		if(z>1.0 || z<0.0)
		{
			throw IllegalArgumentException("zdepth", "must be between 0.0 and 1.0");
		}
		zdepth = z;
	}
	
	double GameObject::getZDepth() const
	{
		return zdepth;
	}
}
