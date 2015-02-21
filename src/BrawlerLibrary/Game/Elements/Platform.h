
#pragma once

#include "GameObject.h"

namespace BrawlerLibrary
{
	class Platform : public GameObject
	{
	public:
		Platform(double x, double y);
		virtual ~Platform();
		
		virtual void update(GameLibrary::ApplicationData appData) override;
		virtual void draw(GameLibrary::ApplicationData appData, GameLibrary::Graphics graphics) const override;
	};
}
