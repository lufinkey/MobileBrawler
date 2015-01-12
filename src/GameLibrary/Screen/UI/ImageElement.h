
#pragma once

#include "../ScreenElement.h"

namespace GameLibrary
{
	class ImageElement : public ScreenElement
	{
	public:
		typedef enum
		{
			/*stretch the image to fill the frame*/
			DISPLAY_STRETCH,
			/*scale the image to be contained within the frame, but maintain the aspect ratio of the image.*/
			DISPLAY_FIT,
			/*scale the image to fill the frame, but don't stretch the image. If a part of the image is outside the frame, it is clipped.*/
			DISPLAY_ZOOM
		} DisplayMode;

		ImageElement();
		ImageElement(const ImageElement&) = delete;
		ImageElement(const RectangleF&frame);
		ImageElement(const RectangleF&frame, TextureImage*image);
		virtual ~ImageElement();
		
		ImageElement& operator=(const ImageElement&) = delete;

		void setImage(TextureImage*);
		void setDisplayMode(const DisplayMode&);
		
		TextureImage* getImage() const;
		DisplayMode getDisplayMode() const;
		
	protected:
		virtual void drawMain(ApplicationData appData, Graphics graphics) const;
		
	private:
		TextureImage* image;
		DisplayMode displayMode;
	};
}
