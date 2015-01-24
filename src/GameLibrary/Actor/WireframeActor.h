
#pragma once

#include "Actor.h"

namespace GameLibrary
{
	class WireframeActor : public Actor
	{
	public:
		WireframeActor();
		WireframeActor(const WireframeActor&) = delete;
		WireframeActor(float x, float y);
		WireframeActor(float x, float y, float width, float height);
		virtual ~WireframeActor();
		
		WireframeActor& operator=(const WireframeActor&) = delete;
		
		virtual void update(ApplicationData appData) override;
		virtual void draw(ApplicationData appData, Graphics graphics) const override;
		
		virtual RectangleF getFrame() const override;
		
		virtual void scaleToFit(const RectangleF&container) override;

		void setSize(const Vector2f&);
		void setSize(float width, float height);
		void setFilled(bool);
		
		const Vector2f& getSize() const;
		bool isFilled() const;
		
		virtual void updateSize() override;
		//NOTE: this function is very inefficient in loops. You should use it for checking single pixels. Do NOT use for pixel level collisions (use PixelIterator)
		virtual bool checkPointCollision(const Vector2f&point) override;
		
	protected:
		virtual void drawActor(ApplicationData&appData, Graphics&graphics, float x, float y, float scale) const;
		
	private:
		bool filled;
		Vector2f size;
		RectangleF framerect;
	};
}
