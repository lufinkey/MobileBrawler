
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
		size.x = w;
		size.y = h;
		width = w;
		height = h;
		filled = false;

		updateSize();
	}
	
	WireframeActor::~WireframeActor()
	{
		//
	}
	
	void WireframeActor::update(ApplicationData appData)
	{
		Actor::update(appData);
	}
	
	void WireframeActor::draw(ApplicationData appData, Graphics graphics) const
	{
		drawActor(appData, graphics, x, y, scale);
	}

	void WireframeActor::drawActor(ApplicationData&appData, Graphics&graphics, float x, float y, float scale) const
	{
		if(visible && scale!=0)
		{
			graphics.translate(x,y);
			Graphics boundingBoxGraphics(graphics);
			if(rotation != 0)
			{
				graphics.rotate(rotation);
			}
			Graphics frameGraphics(graphics);
			if(mirrored)
			{
				if(mirroredVertical)
				{
					graphics.scale(-scale,-scale);
				}
				else
				{
					graphics.scale(-scale,scale);
				}
			}
			else
			{
				if(mirroredVertical)
				{
					graphics.scale(scale,-scale);
				}
				else
				{
					graphics.scale(scale,scale);
				}
			}
			
			Actor::draw(appData, graphics);
			
			Graphics actorGraphics(graphics);
			actorGraphics.setColor(color);
			actorGraphics.setAlpha((byte)(alpha*255));

			if(filled)
			{
				actorGraphics.fillRect(0, 0, size.x, size.y);
			}
			else
			{
				actorGraphics.drawRect(0, 0, size.x, size.y);
			}

			if(frame_visible)
			{
				frameGraphics.setColor(frame_color);
				frameGraphics.drawRect(0, 0, width, height);
				boundingBoxGraphics.setColor(frame_color);
				boundingBoxGraphics.drawRect(framerect.x, framerect.y, framerect.width, framerect.height);
			}
		}
	}

	void WireframeActor::updateSize()
	{
		width = size.x*scale;
		height = size.y*scale;
		framerect = rotationMatrix.transform(RectangleF(0, 0, size.x, size.y));
		framerect.x *= scale;
		framerect.y *= scale;
		framerect.width *= scale;
		framerect.height *= scale;
	}
	
	RectangleF WireframeActor::getFrame() const
	{
		RectangleF frame = framerect;
		frame.x += x;
		frame.y += y;
		return frame;
	}
	
	void WireframeActor::scaleToFit(const RectangleF&container)
	{
		if(width == 0 || height == 0)
		{
			x = container.x + (container.width/2);
			y = container.y + (container.height/2);
			return;
		}
		RectangleF currentFrame = getFrame();
		RectangleF oldFrame = currentFrame;
		currentFrame.scaleToFit(container);
		float ratio = currentFrame.width/oldFrame.width;
		setScale(getScale()*ratio);
		RectangleF newFrame = getFrame();
		x = container.x + ((container.width-newFrame.width)/2);
		y = container.y + ((container.height-newFrame.height)/2);
	}

	void WireframeActor::setSize(const Vector2f&sz)
	{
		size.x = sz.x;
		size.y = sz.y;
		updateSize();
	}
	
	void WireframeActor::setSize(float w, float h)
	{
		size.x = w;
		size.y = h;
		updateSize();
	}
	
	void WireframeActor::setFilled(bool toggle)
	{
		filled = toggle;
	}
	
	const Vector2f& WireframeActor::getSize() const
	{
		return size;
	}
	
	bool WireframeActor::isFilled() const
	{
		return filled;
	}

	bool WireframeActor::checkPointCollision(const Vector2f&point)
	{
		Polygon polygon = Polygon();
		polygon.addPoint(Vector2f(0,0));
		polygon.addPoint(Vector2f(width,0));
		polygon.addPoint(Vector2f(width,height));
		polygon.addPoint(Vector2f(0,height));
		polygon = rotationMatrix.transform(polygon);

		Vector2f fixedPoint(point.x-x, point.y-y);

		return polygon.contains(fixedPoint);
	}
}
