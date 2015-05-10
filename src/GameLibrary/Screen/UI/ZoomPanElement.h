
#pragma once

#include "../ScreenElement.h"

namespace GameLibrary
{
	class ZoomPanElement : public ScreenElement
	{
	public:
		ZoomPanElement();
		explicit ZoomPanElement(const RectangleD&frame);
		
		void setContentOffset(const Vector2d&offset);
		const Vector2d& getContentOffset() const;
		
		void setZoomScale(double zoomScale);
		double getZoomScale() const;
		
		void zoomOnPoint(const Vector2d&point, double zoomScale);
		void zoomOnPointInFrame(const Vector2d&point, double zoomScale);
		
	protected:
		/*! \copydoc GameLibrary::ScreenElement::drawElements(GameLibrary::ApplicationData,GameLibrary::Graphics)const*/
		virtual void drawElements(ApplicationData appData, Graphics graphics) const override;
		
	private:
		Vector2d contentOffset;
		double zoomScale;
	};
}
