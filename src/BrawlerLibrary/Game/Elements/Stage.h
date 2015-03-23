
#pragma once

#include "Platform.h"
#include "../../Loader/StageInfo.h"

namespace BrawlerLibrary
{
	class BrawlGame;
	
	class Stage : GameLibrary::Drawable
	{
	public:
		Stage(BrawlGame*gameInstance, const StageInfo&info, const GameLibrary::Vector2d&position);
		virtual ~Stage();
		
		virtual void update(GameLibrary::ApplicationData appData) override;
		virtual void draw(GameLibrary::ApplicationData appData, GameLibrary::Graphics graphics) const override;
		
	private:
		double x;
		double y;
		
		ArrayList<Platform*> platforms;
		ArrayList<GameObject*> objects;
	};
}
