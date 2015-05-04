
#include "PixelIterator.h"
#include "../Utilities/Math.h"

namespace GameLibrary
{
	PixelIterator::PixelIterator(const Vector2u&dims, const RectangleU&srcrect, const RectangleD&dstrect, const RectangleD&looprect, double xincrement, double yincrement, bool mirrorHorizontal_arg, bool mirrorVertical_arg)
	{
		if(!dstrect.contains(looprect))
		{
			throw IllegalArgumentException("loopRect", "not within bounds of dstRect");
		}
		if((unsigned int)(srcrect.x + srcrect.width) > dims.x)
		{
			throw IllegalArgumentException("srcRect", "not within bounds of dimensions");
		}
		else if((unsigned int)(srcrect.y + srcrect.height) > dims.y)
		{
			throw IllegalArgumentException("srcRect", "not within bounds of dimensions");
		}
		usesTransform = false;
		started = false;
		dimensions = Vector2d((double)dims.x, (double)dims.y);
		srcRect = srcrect;
		srcRectD = RectangleD((double)srcRect.x, (double)srcRect.y, (double)srcRect.width, (double)srcRect.height);
		srcRectRight = srcRectD.x + srcRectD.width;
		srcRectBottom = srcRectD.y + srcRectD.height;
		dstRect = dstrect;
		loopRect = looprect;
		loopRectRel = RectD(loopRect.x-dstRect.x, loopRect.y-dstRect.y, loopRect.x+loopRect.width-dstRect.x, loopRect.y+loopRect.height-dstRect.y);
		ratio.x = srcRectD.width/dstRect.width;
		ratio.y = srcRectD.height/dstRect.height;
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
	
	PixelIterator::PixelIterator(const Vector2u&dims, const RectangleU&srcrect, const RectangleD&dstrect, const RectangleD&looprect, double xincrement, double yincrement, const TransformD&transform, const Vector2d&rat, bool mirrorHorizontal_arg, bool mirrorVertical_arg)
	{
		if(!dstrect.contains(looprect))
		{
			throw IllegalArgumentException("loopRect", "not within bounds of dstRect");
		}
		if((unsigned int)(srcrect.x + srcrect.width) > dims.x)
		{
			throw IllegalArgumentException("srcRect", "not within bounds of dimensions");
		}
		else if((unsigned int)(srcrect.y + srcrect.height) > dims.y)
		{
			throw IllegalArgumentException("srcRect", "not within bounds of dimensions");
		}
		usesTransform = true;
		started = false;
		dimensions = Vector2d((double)dims.x, (double)dims.y);
		srcRect = srcrect;
		srcRectD = RectangleD((double)srcRect.x, (double)srcRect.y, (double)srcRect.width, (double)srcRect.height);
		srcRectRight = srcRectD.x + srcRectD.width;
		srcRectBottom = srcRectD.y + srcRectD.height;
		dstRect = dstrect;
		loopRect = looprect;
		loopRectRel = RectD(loopRect.x-dstRect.x, loopRect.y-dstRect.y, loopRect.x+loopRect.width-dstRect.x, loopRect.y+loopRect.height-dstRect.y);
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
		srcRectD = iterator.srcRectD;
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
		srcRectD = iterator.srcRectD;
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
	
	double PixelIterator::calculatePixelIndex()
	{
		double pixelIndex = -1;
		if(usesTransform)
		{
			Vector2d pixelPoint = inverseTransform.transform(currentPoint);
			pixelPoint.x *= ratio.x;
			pixelPoint.y *= ratio.y;
			if(mirrorHorizontal)
			{
				pixelPoint.x = srcRectD.x + (srcRectD.width - (pixelPoint.x-srcRectD.x));
			}
			else
			{
				pixelPoint.x = srcRectD.x + pixelPoint.x;
			}
			if(mirrorVertical)
			{
				pixelPoint.y = srcRectD.y + (srcRectD.height - (pixelPoint.y-srcRectD.y));
			}
			else
			{
				pixelPoint.y = srcRectD.y + pixelPoint.y;
			}
			if(pixelPoint.x < srcRectD.x || pixelPoint.y < srcRectD.y || pixelPoint.x > srcRectRight || pixelPoint.y > srcRectBottom)
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
			Vector2d pixelPoint(currentPoint.x*ratio.x, currentPoint.y*ratio.y);
			if(mirrorHorizontal)
			{
				pixelPoint.x = srcRectD.x + (srcRectD.width - (pixelPoint.x-srcRectD.x));
			}
			else
			{
				pixelPoint.x = srcRectD.x + pixelPoint.x;
			}
			if(mirrorVertical)
			{
				pixelPoint.y = srcRectD.y + (srcRectD.height - (pixelPoint.y-srcRectD.y));
				row = Math::ceil(pixelPoint.y) - pixelPoint.y;
			}
			else
			{
				pixelPoint.y = srcRectD.y + pixelPoint.y;
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
							currentPixelIndex -= dimensions.x*((double)rowDif);
						}
						else
						{
							currentPixelIndex += dimensions.x*((double)rowDif);
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
	
	double PixelIterator::getCurrentPixelIndex() const
	{
		return currentPixelIndex;
	}
}
