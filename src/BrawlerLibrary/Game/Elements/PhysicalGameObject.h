
#pragma once

#include "GameObject.h"

namespace BrawlerLibrary
{
	class PhysicalGameObject : public GameObject
	{
	public:
		PhysicalGameObject(BrawlGame*gameInstance, const fgl::Vector2d&position);
		virtual ~PhysicalGameObject();
	};
}
