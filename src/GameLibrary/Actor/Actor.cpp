
#include "Actor.h"

namespace GameLibrary
{
	Actor::Actor() : Actor(0,0)
	{
		//
	}

	Actor::Actor(float x1, float y1)
	{
		x = x1;
		y = y1;
	}

	Actor::~Actor()
	{
		//
	}

	void Actor::update(ApplicationData appData)
	{
		BaseActor::update(appData);
	}

	void Actor::draw(ApplicationData appData, Graphics graphics) const
	{
		BaseActor::draw(appData, graphics);
	}

	RectangleF Actor::getFrame() const
	{
		return RectangleF(x-(width/2), y-(height/2), width, height);
	}
}
