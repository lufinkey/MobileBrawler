
#pragma once

#include "BaseActor.h"

namespace GameLibrary
{
	class WireframeActor : public BaseActor
	{
	public:
		WireframeActor();
		WireframeActor(const WireframeActor&) = delete;
		WireframeActor(float x, float y);
		WireframeActor(float x, float y, float width, float height);
		virtual ~WireframeActor();
		
		WireframeActor& operator=(const WireframeActor&) = delete;
		
		virtual void update(ApplicationData appData);
		virtual void draw(ApplicationData appData, Graphics graphics) const;
		
		virtual RectangleF getFrame() const;

		void setSize(const Vector2f&);
		void setSize(float width, float height);
		void setFilled(bool);
		
		const Vector2f& getSize() const;
		bool isFilled() const;
		
	protected:
		virtual void updateSize();
		//NOTE: this function is very inefficient in loops. You should use it for checking single pixels. Do NOT use for pixel level collisions (use PixelIterator)
		virtual bool checkPointCollision(const Vector2f&point);
		virtual void drawActor(ApplicationData&appData, Graphics&graphics, float x, float y, float scale) const;
		
	private:
		bool filled;
		Vector2f size;
		RectangleF framerect;
	};
}
