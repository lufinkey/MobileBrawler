
#include "BaseActor.h"
#include "Animation.h"
#include "../Exception/IllegalArgumentException.h"

#pragma once

namespace GameLibrary
{
	class Actor : public BaseActor
	{
	public:
		Actor();
		Actor(float x, float y);
		virtual ~Actor();
		
		virtual void update(ApplicationData appData);
		virtual void draw(ApplicationData appData, Graphics graphics) const;

		virtual RectangleF getFrame() const;
		
		virtual void onAnimationFinish(Animation*animation);
		
		void addAnimation(const String&name, Animation*animation, bool destruct=true);
		void removeAnimation(const String&name);
		bool hasAnimation(const String&name) const;
		Animation* getAnimation(const String&name) const;
		void changeAnimation(const String&name, const Animation::Direction&direction);
		
	protected:
		virtual void updateSize();
		//NOTE: this function is very inefficient in loops. You should use it for checking single pixels. Do NOT use for pixel level collisions (use PixelIterator)
		virtual bool checkPointCollision(const Vector2f&point);
		virtual void drawActor(ApplicationData&appData, Graphics&graphics, float x, float y, float scale) const;
		
	private:
		typedef struct
		{
			String name;
			Animation* animation;
			bool destruct;
		} AnimationInfo;
		
		ArrayList<AnimationInfo> animations;
		
		String animation_name;
		Animation* animation_current;
		unsigned int animation_frame;
		long long animation_prevFrameTime;
		Animation::Direction animation_direction;

		Vector2f framesize;
		
		bool firstUpdate;
		long long prevUpdateTime;
	};
}
