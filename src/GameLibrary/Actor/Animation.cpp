
#include "Animation.h"

namespace GameLibrary
{
	Animation::AnimationFrame::AnimationFrame()
	{
		file = "default.png";
		rows = 1;
		cols = 1;
		x = 0;
		y = 0;
	}

	Animation::AnimationFrame::AnimationFrame(const Animation::AnimationFrame&animationFrame)
	{
		file = animationFrame.file;
		rows = animationFrame.rows;
		cols = animationFrame.cols;
		x = animationFrame.x;
		y = animationFrame.y;
	}

	Animation::AnimationFrame::AnimationFrame(const String&filepath, TextureImage*tximg)
	{
		file = filepath;
		rows = 1;
		cols = 1;
		x = 0;
		y = 0;
		img = tximg;
	}

	Animation::AnimationFrame::AnimationFrame(const String&filepath, unsigned int rnum, unsigned int cnum, unsigned int r, unsigned int c, TextureImage*tximg)
	{
		file = filepath;
		rows = rnum;
		cols = cnum;
		x = c;
		y = r;
		img = tximg;
	}

	Animation::Animation(const Animation&animation)
	{
		name = animation.name;
		currentFrame = animation.currentFrame;
		frames = animation.frames;

		fps = animation.fps;
		lastFrameTime = animation.lastFrameTime;
		waitTime = animation.waitTime;

		direction = animation.direction;

		mirrored = animation.mirrored;
		mirroredVertical = animation.mirroredVertical;
	}

	Animation& Animation::operator=(const Animation&animation)
	{
		name = animation.name;
		currentFrame = animation.currentFrame;
		frames = animation.frames;

		fps = animation.fps;
		lastFrameTime = animation.lastFrameTime;
		waitTime = animation.waitTime;

		direction = animation.direction;

		mirrored = animation.mirrored;
		mirroredVertical = animation.mirroredVertical;

		return *this;
	}

	Animation::Animation(const String&name_arg, unsigned int fps_arg)
	{
		name = name_arg;
		fps = fps_arg;
		lastFrameTime = 0;
		if(fps==0)
		{
			waitTime = 0;
		}
		else
		{
			waitTime = 1000/fps;
		}
		direction = FORWARD;
		mirrored = false;
		mirroredVertical = false;
	}

	Animation::Animation(AssetManager*assetManager, const String&name, unsigned int fps, const String&file) : Animation(name,fps)
	{
		addFrame(assetManager, file);
	}

	Animation::Animation(AssetManager*assetManager, const String&name_arg, unsigned int fps_arg, unsigned int rows, unsigned int cols, const String&file) : Animation(name,fps)
	{
		addFrames(assetManager, file, rows, cols);
	}

	Animation::Animation(AssetManager*assetManager, const String&name_arg, unsigned int fps_arg, unsigned int rows, unsigned int cols, const String&file, const ArrayList<Vector2u>& sequence) : Animation(name,fps)
	{
		addFrames(assetManager, file, rows, cols, sequence);
	}

	Animation::~Animation()
	{
		//
	}

	unsigned int Animation::size() const
	{
		return frames.size();
	}

	void Animation::clear()
	{
		frames.clear();
	}

	void Animation::mirror(bool toggle)
	{
		mirrored = toggle;
	}

	void Animation::mirrorVertical(bool toggle)
	{
		mirroredVertical = toggle;
	}

	bool Animation::isMirrored() const
	{
		return mirrored;
	}

	bool Animation::isMirroredVertical() const
	{
		return mirroredVertical;
	}

	unsigned int Animation::getFrameWidth() const
	{
		return getFrameWidth(currentFrame);
	}

	unsigned int Animation::getFrameWidth(unsigned int frameNum) const
	{
		const AnimationFrame& animFrame = frames.get(frameNum);
		TextureImage* img = animFrame.img;
		if(img == nullptr)
		{
			return 0;
		}
		else
		{
			unsigned int imgwidth = img->getWidth();
			return (imgwidth/animFrame.cols);
		}
	}

	unsigned int Animation::getFrameHeight() const
	{
		return getFrameHeight(currentFrame);
	}

	unsigned int Animation::getFrameHeight(unsigned int frameNum) const
	{
		const AnimationFrame& animFrame = frames.get(frameNum);
		TextureImage* img = animFrame.img;
		if(img == nullptr)
		{
			return 0;
		}
		else
		{
			unsigned int imgheight = img->getHeight();
			return (imgheight/animFrame.rows);
		}
	}

	void Animation::addFrame(AssetManager*assetManager, const String&file)
	{
		if(file.length()>0)
		{
			TextureImage* img = nullptr;
			if(assetManager != nullptr && assetManager->loadTexture(file))
			{
				img = assetManager->getTexture(file);
			}
			
			frames.add(AnimationFrame(file, img));
		}
	}

	void Animation::addFrames(AssetManager*assetManager, const String&file, unsigned int rows, unsigned int cols)
	{
		unsigned int total = rows*cols;
		if(total > 0 && file.length()>0)
		{
			TextureImage* img = nullptr;
			if(assetManager != nullptr)
			{
				if(assetManager->loadTexture(file))
				{
					img = assetManager->getTexture(file);
				}
			}

			for(unsigned int x=0; x<cols; x++)
			{
				for(unsigned int y=0; y<rows; y++)
				{
					frames.add(AnimationFrame(file, rows, cols, y, x, img));
				}
			}
		}
	}

	void Animation::addFrames(AssetManager*assetManager, const String&file, unsigned int rows, unsigned int cols, const ArrayList<Vector2u>&sequence)
	{
		unsigned int total = rows*cols;
		if(total > 0 && file.length()>0)
		{
			TextureImage* img = nullptr;
			if(assetManager != nullptr)
			{
				if(assetManager->loadTexture(file))
				{
					img = assetManager->getTexture(file);
				}
			}

			for(unsigned int i=0; i<sequence.size(); i++)
			{
				const Vector2u& point = sequence.get(i);
				if(point.x >= cols || point.y >= rows)
				{
					//TODO replace with more specific exception type
					throw Exception("Animation frame (x,y) cannot be outside of the specified rows/cols");
				}
				else
				{
					frames.add(AnimationFrame(file, rows, cols, point.y, point.x, img));
				}
			}
		}
	}

	void Animation::setCurrentFrame(unsigned int frameNum)
	{
		currentFrame = frameNum;
	}

	unsigned int Animation::getCurrentFrame() const
	{
		return currentFrame;
	}

	void Animation::incrementCurrentFrame()
	{
		switch(direction)
		{
			case FORWARD:
			{
				currentFrame++;
				if(currentFrame >= frames.size())
				{
					currentFrame = 0;
				}
			}
			break;

			case BACKWARD:
			{
				if(currentFrame==0)
				{
					if(frames.size()>0)
					{
						currentFrame = frames.size()-1;
					}
				}
				else
				{
					currentFrame--;
				}
			}
			break;
		}
	}

	void Animation::setDirection(const AnimationDirection&dir)
	{
		if(dir == FORWARD || dir == BACKWARD || dir == STOPPED)
		{
			direction = dir;
		}
		else if(direction!=NO_CHANGE)
		{
			throw IllegalArgumentException((String)"Animation::setDirection cannot take an argument with a value of " + dir);
		}
	}

	void Animation::update(ApplicationData appData)
	{
		//TODO implement update
	}

	void Animation::draw(ApplicationData appData, Graphics graphics) const
	{
		//TODO implement draw
	}

	RectangleF Animation::getFrame() const
	{
		const AnimationFrame& animFrame = frames.get(currentFrame);
		TextureImage* img = animFrame.img;
		if(img == nullptr)
		{
			return RectangleF(0,0,0,0);
		}
		else
		{
			unsigned int imgwidth = img->getWidth();
			unsigned int imgheight = img->getHeight();
			float width = ((float)imgwidth/(float)animFrame.cols);
			float height = ((float)imgheight/(float)animFrame.rows);
			return RectangleF(-(width/2), -(height/2), width, height);
		}
	}
}
