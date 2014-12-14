
#include "WireframeActor.h"

namespace GameLibrary
{
	WireframeActor::WireframeActor() : WireframeActor(0,0,0,0)
	{
		//
	}

	WireframeActor::WireframeActor(float x, float y) : WireframeActor(x,y,0,0)
	{
		//
	}

	WireframeActor::WireframeActor(float x1, float y1, float w, float h)
	{
		x = x1;
		y = y1;
		width = w;
		height = h;
		filled = false;
	}

	WireframeActor::~WireframeActor()
	{
		//
	}
	
	void WireframeActor::update(ApplicationData appData)
	{
		BaseActor::update(appData);
	}

	void WireframeActor::draw(ApplicationData appData, Graphics graphics) const
	{
		BaseActor::draw(appData, graphics);
	}
		
	RectangleF WireframeActor::getFrame() const
	{
		return RectangleF(x,y,width,height);
	}
		
	void WireframeActor::setFilled(bool toggle)
	{
		filled = toggle;
	}

	bool WireframeActor::isFilled() const
	{
		return filled;
	}
}
