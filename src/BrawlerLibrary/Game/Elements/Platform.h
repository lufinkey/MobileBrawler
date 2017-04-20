
#pragma once

#include "PhysicalGameObject.h"

namespace BrawlerLibrary
{
	class Platform : public PhysicalGameObject
	{
	public:
		Platform(BrawlGame*gameInstance, const fgl::Vector2d&position);
		virtual ~Platform();
		
		virtual void update(fgl::ApplicationData appData) override;
		virtual void draw(fgl::ApplicationData appData, fgl::Graphics graphics) const override;
		
	private:
		fgl::String name;
	};
}
