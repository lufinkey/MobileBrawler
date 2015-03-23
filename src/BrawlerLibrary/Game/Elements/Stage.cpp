
#include "Stage.h"

using namespace GameLibrary;

namespace BrawlerLibrary
{
	Stage::Stage(BrawlGame*gameInstance, const Vector2d&position)
	{
		x = position.x;
		y = position.y;
	}
	
	Stage::~Stage()
	{
		//
	}
	
	void Stage::update(ApplicationData appData)
	{
		//
	}
	
	void Stage::draw(ApplicationData appData, Graphics graphics) const
	{
		//
	}
}
