
#include "PixelIterator.h"
#include "../Utilities/Math.h"

namespace GameLibrary
{
	PixelIterator::PixelIterator(const Vector2u&dims, const RectangleU&srcrect, const RectangleF&dstrect, const RectangleF&looprect, float xincrement, float yincrement, bool mirrorHorizontal_arg, bool mirrorVertical_arg)
	{
		if(!dstRect.contains(loopRect))
		{
			throw IllegalArgumentException("loopRect must be contained within dstRect");
		}
		if((unsigned int)(srcRect.x + srcRect.width) > dims.x)
		{
			throw IllegalArgumentException("srcRect cannot stretch larger than dimensions");
		}
		else if((unsigned int)(srcRect.y + srcRect.height) > dims.y)
		{
			throw IllegalArgumentException("srcRect cannot stretch larger than dimensions");
		}
		usesTransform = false;
		started = false;
		dimensions = Vector2f((float)dims.x, (float)dims.y);
		srcRect = srcrect;
		srcRectF = RectangleF((float)srcRect.x, (float)srcRect.y, (float)srcRect.width, (float)srcRect.height);
		srcRectRight = srcRectF.x + srcRectF.width;
		srcRectBottom = srcRectF.y + srcRectF.height;
		dstRect = dstrect;
		loopRect = looprect;
		loopRectRel = RectF(loopRect.x-dstRect.x, loopRect.y-dstRect.y, loopRect.x+loopRect.width-dstRect.x, loopRect.y+loopRect.height-dstRect.y);
		ratio.x = srcRectF.width/dstRect.width;
		ratio.y = srcRectF.height/dstRect.height;
		incr.x = xincrement;
		incr.y = yincrement;
		incrpxl.x = incr.x*ratio.x;
		incrpxl.y = incr.y*ratio.y;
		mirrorHorizontal = mirrorHorizontal_arg;
		mirrorVertical = mirrorVertical_arg;
		currentPoint.x = loopRect.x - dstRect.x;
		currentPoint.y = loopRect.y - dstRect.y;
		row = 0;
		lastRowStartIndex = 0;
		currentPixelIndex = calculatePixelIndex();
		lastRowStartIndex = currentPixelIndex;
	}
	
	PixelIterator::PixelIterator(const Vector2u&dims, const RectangleU&srcrect, const RectangleF&dstrect, const RectangleF&looprect, float xincrement, float yincrement, const TransformF&transform, const Vector2f&rat, bool mirrorHorizontal_arg, bool mirrorVertical_arg)
	{
		if(!dstRect.contains(loopRect))
		{
			throw IllegalArgumentException("loopRect must be contained within dstRect");
		}
		if((unsigned int)(srcRect.x + srcRect.width) > dims.x)
		{
			throw IllegalArgumentException("srcRect cannot stretch larger than dimensions");
		}
		else if((unsigned int)(srcRect.y + srcRect.height) > dims.y)
		{
			throw IllegalArgumentException("srcRect cannot stretch larger than dimensions");
		}
		usesTransform = true;
		started = false;
		dimensions = Vector2f((float)dims.x, (float)dims.y);
		srcRect = srcrect;
		srcRectF = RectangleF((float)srcRect.x, (float)srcRect.y, (float)srcRect.width, (float)srcRect.height);
		srcRectRight = srcRectF.x + srcRectF.width;
		srcRectBottom = srcRectF.y + srcRectF.height;
		dstRect = dstrect;
		loopRect = looprect;
		loopRectRel = RectF(loopRect.x-dstRect.x, loopRect.y-dstRect.y, loopRect.x+loopRect.width-dstRect.x, loopRect.y+loopRect.height-dstRect.y);
		ratio.x = rat.x;
		ratio.y = rat.y;
		incr.x = xincrement;
		incr.y = yincrement;
		incrpxl.x = incr.x*ratio.x;
		incrpxl.y = incr.y*ratio.y;
		inverseTransform = transform.getInverse();
		mirrorHorizontal = mirrorHorizontal_arg;
		mirrorVertical = mirrorVertical_arg;
		currentPoint.x = loopRect.x - dstRect.x;
		currentPoint.y = loopRect.y - dstRect.y;
		row = 0;
		lastRowStartIndex = 0;
		currentPixelIndex = calculatePixelIndex();
		lastRowStartIndex = currentPixelIndex;
	}
	
	PixelIterator::PixelIterator(const PixelIterator&iterator)
	{
		dimensions = iterator.dimensions;
		srcRect = iterator.srcRect;
		srcRectF = iterator.srcRectF;
		srcRectRight = iterator.srcRectRight;
		srcRectBottom = iterator.srcRectBottom;
		dstRect = iterator.dstRect;
		loopRect = iterator.loopRect;
		loopRectRel = iterator.loopRectRel;
		inverseTransform = iterator.inverseTransform;
		usesTransform = iterator.usesTransform;
		mirrorHorizontal = iterator.mirrorHorizontal;
		mirrorVertical = iterator.mirrorVertical;
		started = iterator.started;
		currentPoint = iterator.currentPoint;
		currentPixelIndex = iterator.currentPixelIndex;
		lastRowStartIndex = iterator.lastRowStartIndex;
		row = iterator.row;
		incr = iterator.incr;
		incrpxl = iterator.incrpxl;
		ratio = iterator.ratio;
	}
	
	PixelIterator& PixelIterator::operator=(const PixelIterator&iterator)
	{
		dimensions = iterator.dimensions;
		srcRect = iterator.srcRect;
		srcRectF = iterator.srcRectF;
		srcRectRight = iterator.srcRectRight;
		srcRectBottom = iterator.srcRectBottom;
		dstRect = iterator.dstRect;
		loopRect = iterator.loopRect;
		loopRectRel = iterator.loopRectRel;
		inverseTransform = iterator.inverseTransform;
		usesTransform = iterator.usesTransform;
		mirrorHorizontal = iterator.mirrorHorizontal;
		mirrorVertical = iterator.mirrorVertical;
		started = iterator.started;
		currentPoint = iterator.currentPoint;
		currentPixelIndex = iterator.currentPixelIndex;
		lastRowStartIndex = iterator.lastRowStartIndex;
		row = iterator.row;
		incr = iterator.incr;
		incrpxl = iterator.incrpxl;
		ratio = iterator.ratio;
		return *this;
	}
	
	float PixelIterator::calculatePixelIndex()
	{
		float pixelIndex = -1;
		if(usesTransform)
		{
			Vector2f pixelPoint = inverseTransform.transform(currentPoint);
			pixelPoint.x *= ratio.x;
			pixelPoint.y *= ratio.y;
			if(mirrorHorizontal)
			{
				pixelPoint.x = srcRectF.x + (srcRectF.width - (pixelPoint.x-srcRectF.x));
			}
			else
			{
				pixelPoint.x = srcRectF.x + pixelPoint.x;
			}
			if(mirrorVertical)
			{
				pixelPoint.y = srcRectF.y + (srcRectF.height - (pixelPoint.y-srcRectF.y));
			}
			else
			{
				pixelPoint.y = srcRectF.y + pixelPoint.y;
			}
			if(pixelPoint.x < srcRectF.x || pixelPoint.y < srcRectF.y || pixelPoint.x > srcRectRight || pixelPoint.y > srcRectBottom)
			{
				pixelIndex = -1;
			}
			else
			{
				pixelIndex = (dimensions.x*Math::floor(pixelPoint.y))+pixelPoint.x;
			}
		}
		else
		{
			Vector2f pixelPoint(currentPoint.x*ratio.x, currentPoint.y*ratio.y);
			if(mirrorHorizontal)
			{
				pixelPoint.x = srcRectF.x + (srcRectF.width - (pixelPoint.x-srcRectF.x));
			}
			else
			{
				pixelPoint.x = srcRectF.x + pixelPoint.x;
			}
			if(mirrorVertical)
			{
				pixelPoint.y = srcRectF.y + (srcRectF.height - (pixelPoint.y-srcRectF.y));
				row = Math::ceil(pixelPoint.y) - pixelPoint.y;
			}
			else
			{
				pixelPoint.y = srcRectF.y + pixelPoint.y;
				row = pixelPoint.y - Math::floor(pixelPoint.y);
			}
			pixelIndex = (dimensions.x*Math::floor(pixelPoint.y))+pixelPoint.x;
		}
		return pixelIndex;
	}
	
	bool PixelIterator::nextPixelIndex()
	{
		bool running = true;
		if(usesTransform)
		{
			if(started)
			{
				currentPoint.x += incr.x;
				if(currentPoint.x >= loopRectRel.right)
				{
					currentPoint.x = loopRectRel.left;
					currentPoint.y += incr.y;
					if(currentPoint.y >= loopRectRel.bottom)
					{
						currentPoint.y = loopRectRel.top;
						running = false;
					}
				}
				currentPixelIndex = calculatePixelIndex();
			}
			else
			{
				started = true;
			}
		}
		else
		{
			if(started)
			{
				currentPoint.x += incr.x;
				if(mirrorHorizontal)
				{
					currentPixelIndex -= incrpxl.x;
				}
				else
				{
					currentPixelIndex += incrpxl.x;
				}
				if(currentPoint.x >= loopRectRel.right)
				{
					currentPoint.x = loopRectRel.left;
					currentPoint.y += incr.y;
					int lastRow = (int)row;
					row += incrpxl.y;
					int currentRow = (int)row;
					int rowDif = currentRow - lastRow;
					currentPixelIndex = lastRowStartIndex;
					if(rowDif!=0)
					{
						if(mirrorVertical)
						{
							currentPixelIndex -= dimensions.x*((float)rowDif);
						}
						else
						{
							currentPixelIndex += dimensions.x*((float)rowDif);
						}
						lastRowStartIndex = currentPixelIndex;
					}
					if(currentPoint.y >= loopRectRel.bottom)
					{
						currentPoint.y = loopRectRel.top;
						row = 0;
						currentPixelIndex = calculatePixelIndex();
						running = false;
					}
				}
			}
			else
			{
				started = true;
			}
		}
		return running;
	}
	
	float PixelIterator::getCurrentPixelIndex() const
	{
		return currentPixelIndex;
	}
}
