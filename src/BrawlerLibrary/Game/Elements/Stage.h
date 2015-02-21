
#pragma once

#include <GameLibrary/GameLibrary.h>

namespace BrawlerLibrary
{
	class Stage : GameLibrary::Drawable
	{
	public:
		Stage(double x, double y);
		virtual ~Stage();
		
		virtual void update(GameLibrary::ApplicationData appData) override;
		virtual void draw(GameLibrary::ApplicationData appData, GameLibrary::Graphics graphics) const override;
	};
}
