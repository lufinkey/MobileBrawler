
#include "BaseActor.h"

namespace GameLibrary
{
	BaseActor::BaseActor()
	{
		actorType = ACTORTYPE_BASE;
		x = 0;
		y = 0;
		width = 0;
		height = 0;
		
		clicked = false;
		prevclicked = false;
		visible = true;
		mirrored = false;
		mirroredVertical = false;
		color = Color::WHITE;
		rotation = 0;
		alpha = 1;
		scale = 1;
	}
	
	BaseActor::~BaseActor()
	{
		//
	}
	
	void BaseActor::update(ApplicationData appData)
	{
		//
	}
	
	void BaseActor::draw(ApplicationData appData, Graphics graphics) const
	{
		//
	}
	
	BaseActor::ActorType BaseActor::getActorType() const
	{
		return actorType;
	}
	
	float BaseActor::getWidth() const
	{
		return width;
	}
	
	float BaseActor::getHeight() const
	{
		return height;
	}
	
	void BaseActor::setVisible(bool toggle)
	{
		visible = toggle;
	}
	
	void BaseActor::setColor(const Color&c)
	{
		color = c;
	}
	
	void BaseActor::setRotation(float degrees)
	{
		rotation = degrees;
		updateSize();
	}
	
	void BaseActor::setAlpha(float a)
	{
		alpha = a;
	}
	
	void BaseActor::setScale(float s)
	{
		scale = s;
		updateSize();
	}

	void BaseActor::mirror(bool toggle)
	{
		mirrored = toggle;
		updateSize();
	}

	void BaseActor::mirrorVertical(bool toggle)
	{
		mirroredVertical = toggle;
		updateSize();
	}
	
	bool BaseActor::isVisible() const
	{
		return visible;
	}
	
	Color BaseActor::getColor() const
	{
		return color;
	}
	
	float BaseActor::getRotation() const
	{
		return rotation;
	}
	
	float BaseActor::getAlpha() const
	{
		return alpha;
	}
	
	float BaseActor::getScale() const
	{
		return scale;
	}

	bool BaseActor::isMirrored() const
	{
		return mirrored;
	}

	bool BaseActor::isMirroredVertical() const
	{
		return mirroredVertical;
	}
	
	bool BaseActor::isOnScreen(View*view) const
	{
		return true;
	}
	
	bool BaseActor::isMouseClicked() const
	{
		return clicked;
	}
	
	bool BaseActor::wasMouseClicked() const
	{
		return prevclicked;
	}
	
	bool BaseActor::didMouseClick() const
	{
		if(clicked && !prevclicked)
		{
			return true;
		}
		return false;
	}
	
	bool BaseActor::didMouseRelease() const
	{
		if(prevclicked && !clicked)
		{
			return true;
		}
		return false;
	}
	
	RectangleF BaseActor::getFrame() const
	{
		return RectangleF(x,y,width,height);
	}

	void BaseActor::updateSize()
	{
		width = 0;
		height = 0;
	}
}