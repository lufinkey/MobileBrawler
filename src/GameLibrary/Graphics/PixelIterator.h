
#pragma once

#include "../Utilities/Geometry/Rectangle.h"
#include "../Utilities/Geometry/Transform.h"
#include "../Exception/IllegalArgumentException.h"

namespace GameLibrary
{
	class PixelIterator
	{
	private:
		RectangleU srcRect;
		RectangleF srcRectF;
		float srcRectRight;
		float srcRectBottom;
		RectangleF dstRect;
		RectangleF loopRect;
		RectF loopRectRel; //relative to dstRect
		float srcLoopRectWidth;

		Transform inverseTransform;
		bool usesTransform;
		bool mirror;
		bool mirrorVertical;
		bool started;
		
		Vector2f currentPoint; //relative to dstRect
		float currentPixelIndex; //relative to the image
		float lastRowStartIndex;
		float row;
		Vector2f incr;
		Vector2f incrpxl;
		Vector2f ratio; // ratio of srcSize/dstSize
		
		float calculatePixelIndex();
		
	public:
		PixelIterator(const RectangleU&srcRect, const RectangleF&dstRect, const RectangleF&loopRect, float xincrement, float yincrement, bool mirror=false, bool mirrorVertical=false);
		PixelIterator(const RectangleU&srcRect, const RectangleF&dstRect, const RectangleF&loopRect, float xincrement, float yincrement, const Transform&transform, const Vector2f&ratio, bool mirror=false, bool mirrorVertical=false);
		PixelIterator(const PixelIterator&);
		~PixelIterator();
		
		PixelIterator& operator=(const PixelIterator&);
		
		bool nextPixelIndex();
		float getCurrentPixelIndex() const;
	};
}
