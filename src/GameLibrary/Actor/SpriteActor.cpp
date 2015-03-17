
#include "SpriteActor.h"
#include "../Graphics/PixelIterator.h"

namespace GameLibrary
{
	SpriteActor::SpriteActor() : SpriteActor(0,0)
	{
		//
	}
	
	SpriteActor::SpriteActor(double x1, double y1)
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
		else if(animation_current!=nullptr)
		{
			float fps = animation_current->getFPS();
			if(fps!=0)
			{
				long long waitTime = (long long)(1000.0f/fps);
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

			if(animation_current != nullptr)
			{
				animation_current->update(appData);
			}
		}
	}

	void SpriteActor::draw(ApplicationData appData, Graphics graphics) const
	{
		drawActor(appData, graphics, x, y, scale);
	}
	
	void SpriteActor::drawActor(ApplicationData&appData, Graphics&graphics, double x, double y, double scale) const
	{
		if(visible && scale!=0 && animation_current!=nullptr)
		{
			graphics.translate(x, y);
			Graphics boundingBoxGraphics(graphics);
			if(rotation!=0)
			{
				graphics.rotate(rotation);
			}
			Graphics frameGraphics(graphics);
			if(mirroredHorizontal)
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
			actorGraphics.setAlpha((byte)(alpha*255));
			
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
	
	RectangleD SpriteActor::getFrame() const
	{
		return RectangleD(x-(framesize.x/2), y-(framesize.y/2), framesize.x, framesize.y);
	}
	
	void SpriteActor::scaleToFit(const RectangleD&container)
	{
		if(width == 0 || height == 0)
		{
			x = container.x + (container.width/2);
			y = container.y + (container.height/2);
			return;
		}
		RectangleD currentFrame = getFrame();
		RectangleD oldFrame = currentFrame;
		currentFrame.scaleToFit(container);
		double ratio = currentFrame.width/oldFrame.width;
		x = container.x + (container.width/2);
		y = container.y + (container.height/2);
		setScale(getScale()*ratio);
	}
	
	void SpriteActor::onAnimationFinish(Animation*animation)
	{
		//Open for implementation
	}
	
	void SpriteActor::updateSize()
	{
		if(animation_current == nullptr || animation_current->getTotalFrames()==0)
		{
			framesize.x = 0;
			framesize.y = 0;
			width = 0;
			height = 0;
			return;
		}
		
		if(animation_frame > animation_current->getTotalFrames())
		{
			switch(animation_direction)
			{
				case Animation::NO_CHANGE:
				animation_direction = Animation::FORWARD;
				
				case Animation::STOPPED:
				case Animation::FORWARD:
				animation_frame = 0;
				break;
				
				case Animation::BACKWARD:
				animation_frame = animation_current->getTotalFrames()-1;
				break;
			}
		}
		
		RectangleD frame = animation_current->getFrame(animation_frame);
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
			throw IllegalArgumentException("name", "duplicate animation name");
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
			throw IllegalArgumentException("direction", (String)"" + direction);
		}
		
		Animation* animation = getAnimation(name);
		if(animation == nullptr)
		{
			throw IllegalArgumentException("name", "animation does not exist");
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
					default:
					case Animation::NO_CHANGE:
					break;
					
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
	
	void SpriteActor::reloadAnimations(AssetManager*assetManager)
	{
		for(unsigned int i=0; i<animations.size(); i++)
		{
			animations.get(i).animation->reloadFrames(assetManager);
		}
	}
	
	bool SpriteActor::checkPointCollision(const Vector2d&point)
	{
		if(animation_current == nullptr)
		{
			return false;
		}
		RectangleD frame = getFrame();
		if(frame.contains(point))
		{
			Vector2d pointFixed = point;
			pointFixed.x -= x;
			pointFixed.y -= y;
			
			pointFixed = inverseRotationMatrix.transform(pointFixed);
			
			pointFixed.x += width/2;
			pointFixed.y += height/2;
			
			if((mirroredHorizontal && !animation_current->isMirroredHorizontal()) || (!mirroredHorizontal && animation_current->isMirroredHorizontal()))
			{
				pointFixed.x = width - pointFixed.x;
			}
			if((mirroredVertical && !animation_current->isMirroredVertical()) || (!mirroredVertical && animation_current->isMirroredVertical()))
			{
				pointFixed.y = height - pointFixed.y;
			}
			
			double ratX = pointFixed.x/width;
			double ratY = pointFixed.y/height;
			if(ratX < 0 || ratY < 0 || ratX>=1 || ratY>=1)
			{
				return false;
			}
			
			TextureImage* img = animation_current->getImage(animation_frame);
			RectangleI srcRect = animation_current->getImageSourceRect(animation_frame);
			unsigned int pxlX = (unsigned int)(ratX*((double)srcRect.width));
			unsigned int pxlY = (unsigned int)(ratY*((double)srcRect.height));

			return img->checkPixel((unsigned int)srcRect.x+pxlX,(unsigned int)srcRect.y+pxlY);
		}
		return false;
	}
	
	bool SpriteActor::isColliding(SpriteActor*actor) const
	{
		if(actor == nullptr)
		{
			throw IllegalArgumentException("actor", "null");
		}
		else if(animation_current==nullptr || actor->animation_current==nullptr || scale==0 || actor->scale==0)
		{
			return false;
		}
		RectangleD frame = getFrame();
		RectangleD actor_frame = actor->getFrame();
		if(frame.intersects(actor_frame))
		{
			RectangleD overlap = frame.getIntersect(actor_frame);
			
			double incr = 1;
			if(scale < actor->scale)
			{
				incr = scale;
			}
			else
			{
				incr = actor->scale;
			}
			
			TextureImage* img = animation_current->getImage(animation_frame);
			if(img == nullptr)
			{
				throw IllegalStateException("The animation images within SpriteActor have not been loaded through an AssetManager");
			}
			RectangleI srcRect = animation_current->getImageSourceRect(animation_frame);
			RectangleU srcRectU = RectangleU((unsigned int)srcRect.x, (unsigned int)srcRect.y, (unsigned int)srcRect.width, (unsigned int)srcRect.height);
			
			TextureImage* actor_img = actor->animation_current->getImage(actor->animation_frame);
			if(actor_img == nullptr)
			{
				throw IllegalStateException("The animation images within SpriteActor have not been loaded through an AssetManager");
			}
			RectangleI actor_srcRect = actor->animation_current->getImageSourceRect(actor->animation_frame);
			RectangleU actor_srcRectU = RectangleU((unsigned int)actor_srcRect.x, (unsigned int)actor_srcRect.y, (unsigned int)actor_srcRect.width, (unsigned int)actor_srcRect.height);
			
			bool mirrorHorizontal = false;
			if(mirroredHorizontal != animation_current->isMirroredHorizontal())
			{
				mirrorHorizontal = true;
			}
			bool mirrorVertical = false;
			if(mirroredVertical != animation_current->isMirroredVertical())
			{
				mirrorVertical = true;
			}
			
			bool actor_mirrorHorizontal = false;
			if(actor->mirroredHorizontal != actor->animation_current->isMirroredHorizontal())
			{
				actor_mirrorHorizontal = true;
			}
			bool actor_mirrorVertical = false;
			if(actor->mirroredVertical != actor->animation_current->isMirroredVertical())
			{
				actor_mirrorVertical = true;
			}
			
			PixelIterator*pxlIter = nullptr;
			if(rotation == 0)
			{
				Vector2u dimensions(img->getWidth(), img->getHeight());
				pxlIter = new PixelIterator(dimensions, srcRectU, frame, overlap, incr, incr, mirrorHorizontal, mirrorVertical);
			}
			else
			{
				TransformD transform = rotationMatrix;
				transform.translate(-(width/2), -(height/2));
				double ratiox = ((double)srcRect.width)/width;
				double ratioy = ((double)srcRect.height)/height;
				Vector2u dimensions(img->getWidth(), img->getHeight());
				pxlIter = new PixelIterator(dimensions, srcRectU, frame, overlap, incr, incr, transform, Vector2d(ratiox, ratioy), mirrorHorizontal, mirrorVertical);
			}
			PixelIterator& pxlIterRef = *pxlIter;
			
			PixelIterator*actor_pxlIter = nullptr;
			if(actor->rotation == 0)
			{
				Vector2u dimensions(actor_img->getWidth(), actor_img->getHeight());
				actor_pxlIter = new PixelIterator(dimensions, actor_srcRectU, actor_frame, overlap, incr, incr, actor_mirrorHorizontal, actor_mirrorVertical);
			}
			else
			{
				TransformD transform = actor->rotationMatrix;
				transform.translate(-(actor->width/2), -(actor->height/2));
				double ratiox = ((double)actor_srcRect.width)/actor->width;
				double ratioy = ((double)actor_srcRect.height)/actor->height;
				Vector2u dimensions(actor_img->getWidth(), actor_img->getHeight());
				actor_pxlIter = new PixelIterator(dimensions, actor_srcRectU, actor_frame, overlap, incr, incr, transform, Vector2d(ratiox, ratioy), actor_mirrorHorizontal, actor_mirrorVertical);
			}
			PixelIterator& actor_pxlIterRef = *actor_pxlIter;

			bool running = pxlIterRef.nextPixelIndex();
			bool actor_running = actor_pxlIterRef.nextPixelIndex();
			while(running && actor_running)
			{
				double pxlIndex = pxlIterRef.getCurrentPixelIndex();
				double actor_pxlIndex = actor_pxlIterRef.getCurrentPixelIndex();
				bool pxlOn = false;
				if(pxlIndex >= 0)
				{
					pxlOn = img->checkPixel((unsigned int)pxlIndex);
				}
				bool actor_pxlOn = false;
				if(actor_pxlIndex >= 0)
				{
					actor_pxlOn = actor_img->checkPixel((unsigned int)actor_pxlIndex);
				}
				
				if(pxlOn && actor_pxlOn)
				{
					delete pxlIter;
					delete actor_pxlIter;
					return true;
				}
				
				running = pxlIterRef.nextPixelIndex();
				actor_running = actor_pxlIterRef.nextPixelIndex();
			}
			if(running != actor_running)
			{
				delete pxlIter;
				delete actor_pxlIter;
				throw Exception("Unknown collision bug. This exception means there is a bug within the SpriteActor::isColliding function");
			}
			delete pxlIter;
			delete actor_pxlIter;
			return false;
		}
		return false;
	}
}
