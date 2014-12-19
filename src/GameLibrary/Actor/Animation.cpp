
#include "Animation.h"

namespace GameLibrary
{
	Animation::AnimationFrame::AnimationFrame()
	{
		file = "";
		rows = 1;
		cols = 1;
		x = 0;
		y = 0;
		img = nullptr;
	}

	Animation::AnimationFrame::AnimationFrame(const Animation::AnimationFrame&animationFrame)
	{
		file = animationFrame.file;
		rows = animationFrame.rows;
		cols = animationFrame.cols;
		x = animationFrame.x;
		y = animationFrame.y;
		img = animationFrame.img;
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

	Rectangle Animation::AnimationFrame::getSourceRect() const
	{
		if(img == nullptr)
		{
			return Rectangle(0,0,0,0);
		}
		else
		{
			unsigned int width = (img->getWidth()/cols);
			unsigned int height = (img->getHeight()/rows);
			return Rectangle((int)(x*width), (int)(y*height), (int)width, (int)height);
		}
	}

	Animation::Animation(const Animation&animation)
	{
		currentFrame = animation.currentFrame;
		frames = animation.frames;
		fps = animation.fps;
		mirrored = animation.mirrored;
		mirroredVertical = animation.mirroredVertical;
	}

	Animation& Animation::operator=(const Animation&animation)
	{
		currentFrame = animation.currentFrame;
		frames = animation.frames;
		fps = animation.fps;
		mirrored = animation.mirrored;
		mirroredVertical = animation.mirroredVertical;

		return *this;
	}

	Animation::Animation(unsigned int fps_arg)
	{
		fps = fps_arg;
		mirrored = false;
		mirroredVertical = false;
	}

	Animation::Animation(AssetManager*assetManager, unsigned int fps, const String&file) : Animation(fps)
	{
		addFrame(assetManager, file);
	}

	Animation::Animation(AssetManager*assetManager, unsigned int fps_arg, unsigned int rows, unsigned int cols, const String&file) : Animation(fps)
	{
		addFrames(assetManager, file, rows, cols);
	}

	Animation::Animation(AssetManager*assetManager, unsigned int fps_arg, unsigned int rows, unsigned int cols, const String&file, const ArrayList<Vector2u>& sequence) : Animation(fps)
	{
		addFrames(assetManager, file, rows, cols, sequence);
	}

	Animation::~Animation()
	{
		//
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

	unsigned int Animation::getTotalFrames() const
	{
		return frames.size();
	}

	void Animation::setFPS(unsigned int framerate)
	{
		fps = framerate;
	}

	unsigned int Animation::getFPS() const
	{
		return fps;
	}

	RectangleF Animation::getFrame() const
	{
		return getFrame(currentFrame);
	}

	RectangleF Animation::getFrame(unsigned int frameNum) const
	{
		const AnimationFrame& animFrame = frames.get(frameNum);
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
			float left = -(width/2);
			float top = -(height/2);
			return RectangleF(top, left, width, height);
		}
	}

	void Animation::update(ApplicationData appData)
	{
		unsigned int updateFrame = currentFrame;
		unsigned int totalFrames = frames.size();
		if(updateFrame > totalFrames)
		{
			updateFrame = (totalFrames-1);
		}
		AnimationFrame& animFrame = frames.get(updateFrame);
		TextureImage* img = appData.getAssetManager()->getTexture(animFrame.file);
		animFrame.img = img;
	}

	void Animation::draw(ApplicationData appData, Graphics graphics) const
	{
		unsigned int drawFrame = currentFrame;
		unsigned int totalFrames = frames.size();
		if(drawFrame > totalFrames)
		{
			drawFrame = (totalFrames-1);
		}
		const AnimationFrame& animFrame = frames.get(drawFrame);

		RectangleF dstRect = getFrame(drawFrame);
		Rectangle srcRect = animFrame.getSourceRect();

		float dst_left = dstRect.x;
		float dst_top = dstRect.y;
		float dst_right = dst_left + dstRect.width;
		float dst_bottom = dst_top + dstRect.height;

		int src_left = srcRect.x;
		int src_top = srcRect.y;
		int src_right = src_left + srcRect.width;
		int src_bottom = src_top + srcRect.height;

		if(mirrored)
		{
			if(mirroredVertical)
			{
				graphics.drawImage(animFrame.img, dst_right, dst_bottom, dst_left, dst_top, src_left, src_top, src_right, src_bottom);
			}
			else
			{
				graphics.drawImage(animFrame.img, dst_right, dst_top, dst_left, dst_bottom, src_left, src_top, src_right, src_bottom);
			}
		}
		else
		{
			if(mirroredVertical)
			{
				graphics.drawImage(animFrame.img, dst_left, dst_bottom, dst_right, dst_top, src_left, src_top, src_right, src_bottom);
			}
			else
			{
				graphics.drawImage(animFrame.img, dst_left, dst_top, dst_right, dst_bottom, src_left, src_top, src_right, src_bottom);
			}
		}
	}
}
