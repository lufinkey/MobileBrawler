
#include "ZoomPanElement.h"

namespace GameLibrary
{
	ZoomPanElement::ZoomPanElement() : ZoomPanElement(RectangleD(0,0,0,0))
	{
		//
	}
	
	ZoomPanElement::ZoomPanElement(const RectangleD&frame) : ScreenElement(frame),
		zoomScale(1), contentOffset(0,0)
	{
		//
	}
	
	void ZoomPanElement::setContentOffset(const Vector2d&offset)
	{
		contentOffset = offset;
	}
	
	const Vector2d& ZoomPanElement::getContentOffset() const
	{
		return contentOffset;
	}
	
	void ZoomPanElement::setZoomScale(double zoom)
	{
		zoomScale = zoom;
	}
	
	double ZoomPanElement::getZoomScale() const
	{
		return zoomScale;
	}
	
	void ZoomPanElement::zoomOnPoint(const Vector2d&point, double zoom)
	{
		RectangleD frame = getFrame();
		double offsetX = (frame.width/2)*zoom;
		double offsetY = (frame.height/2)*zoom;
		contentOffset.x = point.x - offsetX;
		contentOffset.y = point.y - offsetY;
		zoomScale = zoom;
	}
	
	void ZoomPanElement::zoomOnPointInFrame(const Vector2d&point, double zoom)
	{
		Vector2d fixedPoint((point.x-contentOffset.x)/zoom, (point.y-contentOffset.y)/zoom);
		zoomOnPoint(fixedPoint, zoom);
	}
	
	void ZoomPanElement::drawElements(ApplicationData appData, Graphics graphics) const
	{
		graphics.clip(getFrame());
		graphics.translate(contentOffset.x*zoomScale, contentOffset.y*zoomScale);
		graphics.scale(zoomScale, zoomScale);
		ScreenElement::drawElements(appData, graphics);
	}
}
