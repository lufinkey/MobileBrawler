
#include "../Application/AssetManager.h"
#include "../Exception/IllegalArgumentException.h"
#include "../Screen/Drawable.h"
#include "../Utilities/ArrayList.h"
#include "../Utilities/String.h"
#include "../Utilities/Geometry/Rectangle.h"

#pragma once

namespace GameLibrary
{
	/*Animation object that holds Animation data for the Actor class*/
	class Animation : public Drawable
	{
	public:
		enum AnimationDirection : byte
		{
			NO_CHANGE,
			FORWARD,
			BACKWARD,
			STOPPED
		};
		typedef enum AnimationDirection AnimationDirection;

		Animation(const Animation&);
		Animation(AssetManager*assetManager, unsigned int fps, const String&file=String());
		Animation(AssetManager*assetManager, unsigned int fps, unsigned int rows, unsigned int cols, const String&file);
		Animation(AssetManager*assetManager, unsigned int fps, unsigned int rows, unsigned int cols, const String&file, const ArrayList<Vector2u>& sequence);
		virtual ~Animation();

		Animation& operator=(const Animation&);

		virtual void update(ApplicationData appData);
		virtual void draw(ApplicationData appData, Graphics graphics) const;

		void clear();

		void mirror(bool);
		void mirrorVertical(bool);
		bool isMirrored() const;
		bool isMirroredVertical() const;

		unsigned int getFrameWidth() const;
		unsigned int getFrameWidth(unsigned int frameNum) const;
		unsigned int getFrameHeight() const;
		unsigned int getFrameHeight(unsigned int frameNum) const;

		void addFrame(AssetManager*assetManager, const String&file);
		void addFrames(AssetManager*assetManager, const String&file, unsigned int rows, unsigned int cols);
		void addFrames(AssetManager*assetManager, const String&file, unsigned int rows, unsigned int cols, const ArrayList<Vector2u>&sequence);

		void setCurrentFrame(unsigned int frameNum);
		unsigned int getCurrentFrame() const;
		unsigned int getTotalFrames() const;

		void setFPS(unsigned int fps);
		unsigned int getFPS() const;

		TextureImage* getImage(unsigned int frameNum) const;
		TextureImage* getImage() const;

		virtual RectangleF getFrame() const;
		RectangleF getFrame(unsigned int frameNum) const;

	private:
		class AnimationFrame
		{
		public:
			String file;
			unsigned int rows;
			unsigned int cols;
			unsigned int x;
			unsigned int y;
			TextureImage* img;

			AnimationFrame();
			AnimationFrame(const AnimationFrame&);
			AnimationFrame(const String&file, TextureImage*img=nullptr);
			AnimationFrame(const String&file, unsigned int rows, unsigned int cols, unsigned int row, unsigned int col, TextureImage*img=nullptr);
			
			Rectangle getSourceRect() const;
		};

		Animation(unsigned int fps);

		unsigned int currentFrame;
		ArrayList<AnimationFrame> frames;

		unsigned int fps;

		bool mirrored;
		bool mirroredVertical;
	};
}
