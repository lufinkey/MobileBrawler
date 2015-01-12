
#include "SpriteActor.h"

namespace GameLibrary
{
	SpriteActor::SpriteActor() : SpriteActor(0,0)
	{
		//
	}
	
	SpriteActor::SpriteActor(float x1, float y1)
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
	
	SpriteActor::~SpriteActor()
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
	
	void SpriteActor::update(ApplicationData appData)
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
		
		Actor::update(appData);

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

	void SpriteActor::draw(ApplicationData appData, Graphics graphics) const
	{
		drawActor(appData, graphics, x, y, scale);
	}
	
	void SpriteActor::drawActor(ApplicationData&appData, Graphics&graphics, float x, float y, float scale) const
	{
		if(visible && scale!=0)
		{
			graphics.translate(x, y);
			Graphics boundingBoxGraphics(graphics);
			if(rotation!=0)
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
			actorGraphics.compositeTintColor(color);
			
			animation_current->setCurrentFrame(animation_frame);
			animation_current->draw(appData, actorGraphics);
			
			if(frame_visible)
			{
				frameGraphics.setColor(frame_color);
				frameGraphics.drawRect(-(width/2), -(height/2), width, height);
				boundingBoxGraphics.setColor(frame_color);
				boundingBoxGraphics.drawRect(-(framesize.x/2), -(framesize.y/2), framesize.x, framesize.y);
			}
		}
	}
	
	RectangleF SpriteActor::getFrame() const
	{
		return RectangleF(x-(framesize.x/2), y-(framesize.y/2), framesize.x, framesize.y);
	}
	
	void SpriteActor::scaleToFit(const RectangleF&container)
	{
		RectangleF currentFrame = getFrame();
		currentFrame.scaleToFit(container);
		float ratio = container.width/currentFrame.width;
		setScale(getScale()*ratio);

		x = container.width/2;
		y = container.height/2;
	}
	
	void SpriteActor::onAnimationFinish(Animation*animation)
	{
		//Open for implementation
	}
	
	void SpriteActor::updateSize()
	{
		RectangleF frame = animation_current->getFrame(animation_frame);
		frame.x*=scale;
		frame.y*=scale;
		frame.width*=scale;
		frame.height*=scale;

		width = frame.width;
		height = frame.height;

		frame = rotationMatrix.transform(frame);
		
		framesize.x = frame.width;
		framesize.y = frame.height;
	}
	
	void SpriteActor::addAnimation(const String&name, Animation*animation, bool destruct)
	{
		if(hasAnimation(name))
		{
			throw IllegalArgumentException("Animation with name \"" + name + "\" is already added to this SpriteActor");
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
	
	void SpriteActor::removeAnimation(const String&name)
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
	
	bool SpriteActor::hasAnimation(const String&name) const
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
	
	Animation* SpriteActor::getAnimation(const String&name) const
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
	
	void SpriteActor::changeAnimation(const String&name, const Animation::Direction&direction)
	{
		if(direction != Animation::FORWARD && direction != Animation::BACKWARD && direction != Animation::STOPPED && direction != Animation::NO_CHANGE)
		{
			throw IllegalArgumentException((String)"Invalid value " + direction + " for direction argument in SpriteActor::changeAnimation");
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
	
	bool SpriteActor::checkPointCollision(const Vector2f&point)
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
			pointFixed.x -= x;
			pointFixed.y -= y;
			
			pointFixed = inverseRotationMatrix.transform(pointFixed);

			pointFixed.x += width/2;
			pointFixed.y += height/2;
			
			if((mirrored && !animation_current->isMirrored()) || (!mirrored && animation_current->isMirrored()))
			{
				pointFixed.x = width - pointFixed.x;
			}
			if((mirroredVertical && !animation_current->isMirroredVertical()) || (!mirroredVertical && animation_current->isMirroredVertical()))
			{
				pointFixed.y = height - pointFixed.y;
			}
			
			float ratX = pointFixed.x/width;
			float ratY = pointFixed.y/height;
			if(ratX < 0 || ratY < 0 || ratX>1 || ratY>1)
			{
				return false;
			}
			
			TextureImage* img = animation_current->getImage(animation_frame);
			RectangleI srcRect = animation_current->getImageSourceRect(animation_frame);
			unsigned int pxlX = (unsigned int)(ratX*((float)srcRect.width));
			unsigned int pxlY = (unsigned int)(ratY*((float)srcRect.height));

			return img->checkPixel((unsigned int)srcRect.x+pxlX,(unsigned int)srcRect.y+pxlY);
		}
		return false;
	}
}
