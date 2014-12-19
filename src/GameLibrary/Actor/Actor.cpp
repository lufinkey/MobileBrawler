
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
		BaseActor::update(appData);
		//TODO implement update
	}

	void Actor::draw(ApplicationData appData, Graphics graphics) const
	{
		BaseActor::draw(appData, graphics);
		
		graphics.translate(x+(width / 2), y+(height/2));
		graphics.compositeTintColor(color);
		graphics.rotate(rotation);
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

		animation_current->setCurrentFrame(animation_frame);
		animation_current->draw(appData, graphics);
	}

	void Actor::updateSize()
	{
		RectangleF frame = animation_current->getFrame(animation_frame);
		width = frame.width*scale;
		height = frame.height*scale;
	}

	RectangleF Actor::getFrame() const
	{
		return RectangleF(x-(width/2), y-(height/2), width, height);
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

		animations.add(animInfo);
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
}
