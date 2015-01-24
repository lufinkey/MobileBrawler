
#pragma once

#include "../Application/AssetManager.h"
#include "../Exception/IllegalArgumentException.h"
#include "../Screen/Drawable.h"
#include "../Utilities/ArrayList.h"
#include "../Utilities/String.h"
#include "../Utilities/Geometry/Rectangle.h"

namespace GameLibrary
{
	/*Animation object that holds Animation data for the SpriteActor class*/
	class Animation : public Drawable
	{
	public:
		enum Direction
		{
			NO_CHANGE,
			FORWARD,
			BACKWARD,
			STOPPED
		};
		typedef enum Direction Direction;

		Animation(const Animation&);
		Animation(unsigned int fps);
		Animation(unsigned int fps, AssetManager*assetManager, const String&file);
		Animation(unsigned int fps, unsigned int rows, unsigned int cols, AssetManager*assetManager, const String&file);
		Animation(unsigned int fps, unsigned int rows, unsigned int cols, AssetManager*assetManager, const String&file, const ArrayList<Vector2u>& sequence);
		virtual ~Animation();

		Animation& operator=(const Animation&);

		virtual void update(ApplicationData appData) override;
		virtual void draw(ApplicationData appData, Graphics graphics) const override;
		
		void reloadFrames(AssetManager*assetManager);

		void clear();

		void setMirrored(bool);
		void setMirroredVertical(bool);
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
		RectangleI getImageSourceRect(unsigned int frameNum) const;
		RectangleI getImageSourceRect() const;

		virtual RectangleF getFrame() const override;
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
			
			RectangleI getSourceRect() const;
		};

		unsigned int currentFrame;
		ArrayList<AnimationFrame> frames;

		unsigned int fps;

		bool mirrored;
		bool mirroredVertical;
	};
}
