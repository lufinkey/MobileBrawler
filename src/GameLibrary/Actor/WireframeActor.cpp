
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
		BaseActor::update(appData);
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
			
			BaseActor::draw(appData, graphics);
			
			Graphics actorGraphics(graphics);
			actorGraphics.setColor(color);

			if(filled)
			{
				actorGraphics.fillRect(0, 0, size.x*scale, size.y*scale);
			}
			else
			{
				actorGraphics.drawRect(0, 0, size.x*scale, size.y*scale);
			}

			if(frame_visible)
			{
				frameGraphics.setColor(frame_color);
				frameGraphics.drawRect(0, 0, size.x*scale, size.y*scale);
				boundingBoxGraphics.setColor(frame_color);
				boundingBoxGraphics.drawRect(framerect.x, framerect.y, framerect.width, framerect.height);
			}
		}
	}

	void WireframeActor::updateSize()
	{
		width = size.x*scale;
		height = size.y*scale;
		framerect = rotationMatrix.transform(RectangleF(0, 0, width, height));
	}
	
	RectangleF WireframeActor::getFrame() const
	{
		RectangleF frame = framerect;
		frame.x += x;
		frame.y += y;
		return frame;
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
}
