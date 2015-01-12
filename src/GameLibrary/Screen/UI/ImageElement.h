
#pragma once

#include "../ScreenElement.h"

namespace GameLibrary
{
	class ImageElement : public ScreenElement
	{
	private:
		TextureImage* image;
		bool maintainAspectRatio;
		
	protected:
		virtual void drawMain(ApplicationData appData, Graphics graphics) const;
		
	public:
		ImageElement();
		ImageElement(const ImageElement&) = delete;
		ImageElement(const RectangleF&frame);
		ImageElement(const RectangleF&frame, TextureImage*image);
		virtual ~ImageElement();
		
		ImageElement& operator=(const ImageElement&) = delete;

		void setImage(TextureImage*);
		void setMaintainAspectRatio(bool);

		TextureImage* getImage() const;
		bool maintainsAspectRatio() const;
	};
}
