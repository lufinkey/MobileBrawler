
#pragma once

#include "GameObject.h"

namespace BrawlerLibrary
{
	class PhysicalGameObject : public GameObject
	{
	public:
		PhysicalGameObject(BrawlGame*gameInstance, const GameLibrary::Vector2d&position);
		virtual ~PhysicalGameObject();
	};
}
