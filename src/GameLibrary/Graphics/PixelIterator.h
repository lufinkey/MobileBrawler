
#pragma once

#include "../Utilities/Geometry/Rectangle.h"
#include "../Utilities/Geometry/Transform.h"
#include "../Exception/IllegalArgumentException.h"

namespace GameLibrary
{
	/*! Iterates through pixel coordinates in a rectangle at a specified speed. Useful for efficiently detecting pixel level collisions.*/
	class PixelIterator
	{
	public:
		/*! Constructs a PixelIterator to loop through a given area.
			\param dimensions the actual size of the image or canvas, in pixels
			\param srcRect the source rectangle of the area being checked
			\param dstRect the destination rectangle of the section of the canvas or image being drawn; Useful if an image or canvas is stretched
			\param loopRect the rectangle to loop through in terms of destination pixels, rather than source pixels
			\param xincrement the amount to increment the x value through each iteration; Value is in terms of destination pixels, rather than source pixels
			\param yincrement the amount to increment the y value through each row iteration; Value is in terms of destination pixels, rather than source pixels
			\param mirrorHorizontal true if the destination image or canvas is mirrored horizontally, and false if otherwise
			\param mirrorVertical true if the destination image or canvas is mirrored vertically, and false if otherwise
			\throws GameLibrary::IllegalArgumentException if loopRect is not contained within dstRect or if srcRect is stretches larger than dimensions*/
		PixelIterator(const Vector2u&dimensions, const RectangleU&srcRect, const RectangleF&dstRect, const RectangleF&loopRect, float xincrement, float yincrement, bool mirrorHorizontal=false, bool mirrorVertical=false);
		/*! Constructs a PixelIterator to loop through a given area.
			\param dimensions the actual size of the image or canvas, in pixels
			\param srcRect the source rectangle of the area being checked
			\param dstRect the destination rectangle of the section of the canvas or image being drawn; Useful if an image or canvas is stretched
			\param loopRect the rectangle to loop through in terms of destination pixels, rather than source pixels
			\param xincrement the amount to increment the x value through each iteration; Value is in terms of destination pixels, rather than source pixels
			\param yincrement the amount to increment the y value through each row iteration; Value is in terms of destination pixels, rather than source pixels
			\param transform the transformation of the desination image or canvas
			\param ratio the ratio of the source rectangle size over the non-transformed destination rectangle size
			\param mirrorHorizontal true if the destination image or canvas is mirrored horizontally, and false if otherwise
			\param mirrorVertical true if the destination image or canvas is mirrored vertically, and false if otherwise
			\throws GameLibrary::IllegalArgumentException if loopRect is not contained within dstRect or if srcRect is stretches larger than dimensions*/
		PixelIterator(const Vector2u&dimensions, const RectangleU&srcRect, const RectangleF&dstRect, const RectangleF&loopRect, float xincrement, float yincrement, const Transform&transform, const Vector2f&ratio, bool mirrorHorizontal=false, bool mirrorVertical=false);
		/*! copy constructor*/
		PixelIterator(const PixelIterator&);
		/*! assignment operator*/
		PixelIterator& operator=(const PixelIterator&);
		
		
		/*! iterates to the next pixel "index".
			\returns true if there is still more area to iterate through, or false if the iterator has finished iterating and has returned to the starting point*/
		bool nextPixelIndex();
		/*! Gets the current pixel "index". This value should be floored and converted to an integer before checking against an image or canvas.
			\returns a float value representing the current iteration through the images pixel indexes; This value will be negative if outside of the bounds of the image or canvas*/
		float getCurrentPixelIndex() const;
		
	private:
		float calculatePixelIndex();
		
		Vector2f dimensions;
		
		RectangleU srcRect;
		RectangleF srcRectF;
		float srcRectRight;
		float srcRectBottom;
		RectangleF dstRect;
		RectangleF loopRect;
		RectF loopRectRel; //relative to dstRect

		Transform inverseTransform;
		bool usesTransform;
		bool mirrorHorizontal;
		bool mirrorVertical;
		bool started;
		
		Vector2f currentPoint; //relative to dstRect
		float currentPixelIndex; //relative to the image
		float lastRowStartIndex;
		float row;
		Vector2f incr;
		Vector2f incrpxl;
		Vector2f ratio; // ratio of srcSize/dstSize
	};
}
