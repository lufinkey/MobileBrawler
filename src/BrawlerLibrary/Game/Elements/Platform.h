
#pragma once

#include "PhysicalGameObject.h"

namespace BrawlerLibrary
{
	class Platform : public PhysicalGameObject
	{
	public:
		Platform(double x, double y);
		virtual ~Platform();
		
		virtual void update(GameLibrary::ApplicationData appData) override;
		virtual void draw(GameLibrary::ApplicationData appData, GameLibrary::Graphics graphics) const override;
	};
}
