
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
		void changeAnimation(const String&name, const Animation::AnimationDirection&direction);

		void setWireframeVisible(bool);
		void setWireframeColor(const Color&);

		bool isWireframeVisible() const;
		const Color& getWireframeColor() const;
		
	protected:
		virtual void updateSize();
		virtual bool checkPointCollide(const Vector2f&point);
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
		Animation::AnimationDirection animation_direction;

		bool wireframe_visible;
		Color wireframe_color;
		
		bool firstUpdate;
		long long prevUpdateTime;
	};
}
