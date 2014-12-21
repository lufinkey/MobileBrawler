
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

		animation_current = nullptr;
		animation_frame = 0;
		animation_prevFrameTime = 0;
		animation_direction = Animation::FORWARD;

		wireframe_visible = false;
		wireframe_color = Color::GREEN;

		firstUpdate = true;
		prevUpdateTime = 0;
	}
	
	Actor::~Actor()
	{
		for(unsigned int i=0; i<animations.size(); i++)
		{
			AnimationInfo& info = animations.get(i);
			if(info.destruct)
			{
				delete info.animation;
			}
		}
	}
	
	void Actor::update(ApplicationData appData)
	{
		prevUpdateTime = appData.getTime().getMilliseconds();
		if(firstUpdate)
		{
			if(animations.size()>0)
			{
				animation_prevFrameTime = prevUpdateTime;
			}
		}
		firstUpdate = false;
		
		BaseActor::update(appData);

		//update animation loop
		if(animation_direction == Animation::STOPPED)
		{
			animation_prevFrameTime = prevUpdateTime;
		}
		else
		{
			unsigned int fps = animation_current->getFPS();
			if(fps!=0)
			{
				long long waitTime = 1000/fps;
				long long finishTime = animation_prevFrameTime + waitTime;
				if(finishTime <= prevUpdateTime)
				{
					animation_prevFrameTime = prevUpdateTime;
					if(animation_direction == Animation::FORWARD)
					{
						animation_frame++;
						unsigned int totalFrames = animation_current->getTotalFrames();
						if(animation_frame >= totalFrames)
						{
							animation_frame = 0;
							animation_current->setCurrentFrame(animation_frame);
							onAnimationFinish(animation_current);
						}
						else
						{
							animation_current->setCurrentFrame(animation_frame);
						}
					}
					else if(animation_direction == Animation::BACKWARD)
					{
						if(animation_frame == 0)
						{
							unsigned int totalFrames = animation_current->getTotalFrames();
							if(totalFrames > 0)
							{
								animation_frame = totalFrames-1;
							}
							animation_current->setCurrentFrame(animation_frame);
							onAnimationFinish(animation_current);
						}
						else
						{
							animation_frame--;
							animation_current->setCurrentFrame(animation_frame);
						}
					}
				}
			}
		}
	}

	void Actor::draw(ApplicationData appData, Graphics graphics) const
	{
		drawActor(appData, graphics, x, y, scale);
	}
	
	void Actor::drawActor(ApplicationData&appData, Graphics&graphics, float x, float y, float scale) const
	{
		BaseActor::draw(appData, graphics);

		if(visible)
		{
			graphics.translate(x, y);
			if(rotation!=0)
			{
				graphics.rotate(rotation);
			}
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
			Graphics actorGraphics(graphics);
			actorGraphics.compositeTintColor(color);
			
			animation_current->setCurrentFrame(animation_frame);
			animation_current->draw(appData, actorGraphics);
			
			if(wireframe_visible)
			{
				RectangleF wireframeRect = animation_current->getFrame(animation_frame);
				Graphics wireframeGraphics(graphics);
				wireframeGraphics.setColor(wireframe_color);
				wireframeGraphics.drawRect(wireframeRect.x, wireframeRect.y, wireframeRect.width, wireframeRect.height);
			}
		}
	}
	
	RectangleF Actor::getFrame() const
	{
		return RectangleF(x-(width/2), y-(height/2), width, height);
	}
	
	void Actor::onAnimationFinish(Animation*animation)
	{
		//Open for implementation
	}
	
	void Actor::updateSize()
	{
		RectangleF frame = animation_current->getFrame(animation_frame);
		width = frame.width*scale;
		height = frame.height*scale;
	}
	
	void Actor::addAnimation(const String&name, Animation*animation, bool destruct)
	{
		if(hasAnimation(name))
		{
			throw IllegalArgumentException("Animation with name \"" + name + "\" is already added to this Actor");
		}
		
		AnimationInfo animInfo;
		animInfo.name = name;
		animInfo.animation = animation;
		animInfo.destruct = destruct;
		
		unsigned int prevSize = animations.size();
		
		animations.add(animInfo);
		
		if(prevSize == 0)
		{
			changeAnimation(name, Animation::FORWARD);
		}
	}
	
	void Actor::removeAnimation(const String&name)
	{
		unsigned int totalAnimations = animations.size();
		for(unsigned int i=0; i<totalAnimations; i++)
		{
			AnimationInfo animInfo = animations.get(i);
			if(animInfo.name.equals(name))
			{
				if(animInfo.destruct)
				{
					delete animInfo.animation;
				}
				animations.remove(i);
				return;
			}
		}
	}
	
	bool Actor::hasAnimation(const String&name) const
	{
		unsigned int totalAnimations = animations.size();
		for(unsigned int i=0; i<totalAnimations; i++)
		{
			if(animations.get(i).name.equals(name))
			{
				return true;
			}
		}
		return false;
	}
	
	Animation* Actor::getAnimation(const String&name) const
	{
		unsigned int totalAnimations = animations.size();
		for(unsigned int i=0; i<totalAnimations; i++)
		{
			const AnimationInfo&animInfo = animations.get(i);
			if(animInfo.name.equals(name))
			{
				return animInfo.animation;
			}
		}
		return nullptr;
	}
	
	void Actor::changeAnimation(const String&name, const Animation::AnimationDirection&direction)
	{
		if(direction != Animation::FORWARD && direction != Animation::BACKWARD && direction != Animation::STOPPED && direction != Animation::NO_CHANGE)
		{
			throw IllegalArgumentException((String)"Invalid value " + direction + " for direction argument in Actor::changeAnimation");
		}
		
		Animation* animation = getAnimation(name);
		if(animation == nullptr)
		{
			throw IllegalArgumentException("Animation with name \"" + name + "\" does not exist");
		}
		
		animation_name = name;
		animation_current = animation;
		
		switch(direction)
		{
			case Animation::FORWARD:
			case Animation::STOPPED:
			{
				animation_frame = 0;
				animation_prevFrameTime = prevUpdateTime;
				animation_direction = direction;
			}
			break;
			
			case Animation::BACKWARD:
			{
				unsigned int totalFrames = animation->getTotalFrames();
				if(totalFrames>0)
				{
					animation_frame = (totalFrames-1);
				}
				else
				{
					animation_frame = 0;
				}
				animation_prevFrameTime = prevUpdateTime;
				animation_direction = direction;
			}
			break;
			
			case Animation::NO_CHANGE:
			{
				switch(animation_direction)
				{
					case Animation::FORWARD:
					case Animation::STOPPED:
					{
						if(animation_frame >= animation->getTotalFrames())
						{
							animation_frame = 0;
						}
					}
					break;
					
					case Animation::BACKWARD:
					{
						unsigned int totalFrames = animation->getTotalFrames();
						if(animation_frame >= totalFrames)
						{
							if(totalFrames>0)
							{
								animation_frame = (totalFrames-1);
							}
							else
							{
								animation_frame = 0;
							}
						}
					}
					break;
				}
			}
		}
		
		animation->setCurrentFrame(animation_frame);
		updateSize();
	}
	
	void Actor::setWireframeVisible(bool toggle)
	{
		wireframe_visible = toggle;
	}
	
	void Actor::setWireframeColor(const Color&color)
	{
		wireframe_color = color;
	}
	
	bool Actor::isWireframeVisible() const
	{
		return wireframe_visible;
	}
	
	const Color& Actor::getWireframeColor() const
	{
		return wireframe_color;
	}
	
	bool Actor::checkPointCollide(const Vector2f&point)
	{
		if(animation_current == nullptr)
		{
			return false;
		}
		float halfwidth = width/2;
		float halfheight = height/2;
		float left = x-halfwidth;
		float right = x+halfwidth;
		float top = y-halfheight;
		float bottom = y+halfheight;
		if(point.x>left && point.y>top && point.x<right && point.y<bottom)
		{
			Vector2f pointFixed = point;
			pointFixed.x -= left;
			pointFixed.y -= top;
			
			//TODO add rotation matrix
			
			if((mirrored && !animation_current->isMirrored()) || (!mirrored && animation_current->isMirrored()))
			{
				pointFixed.x = width - pointFixed.x;
			}
			if((mirroredVertical && !animation_current->isMirroredVertical()) || (!mirroredVertical && animation_current->isMirroredVertical()))
			{
				pointFixed.y = height - pointFixed.y;
			}
			
			RectangleF animRect = animation_current->getFrame(animation_frame);
			float w = animRect.width*scale;
			float h = animRect.height*scale;
			
			float ratX = pointFixed.x/w;
			float ratY = pointFixed.y/h;
			if(ratX < 0 || ratY < 0 || ratX>1 || ratY>1)
			{
				return false;
			}
			
			TextureImage* img = animation_current->getImage(animation_frame);
			Rectangle srcRect = animation_current->getImageSourceRect(animation_frame);
			unsigned int pxlX = (unsigned int)(ratX*((float)srcRect.width));
			unsigned int pxlY = (unsigned int)(ratY*((float)srcRect.height));

			bool px = img->checkPixel((unsigned int)srcRect.x+pxlX,(unsigned int)srcRect.y+pxlY);
			if(px)
			{
				return true;
			}
			return false;
		}
		return false;
	}
}
