
#include "ImageElement.h"

namespace GameLibrary
{
	ImageElement::ImageElement() : ImageElement(RectangleD(0,0,0,0),nullptr)
	{
		//
	}
	
	ImageElement::ImageElement(const RectangleD&frame) : ImageElement(frame,nullptr)
	{
		//
	}
	
	ImageElement::ImageElement(const RectangleD&frame, TextureImage*img, const ImageElement::DisplayMode&displayMd) : ScreenElement(frame)
	{
		image = img;
		displayMode = displayMd;
	}
	
	ImageElement::ImageElement(TextureImage*img, const ImageElement::DisplayMode&displayMode) : ImageElement(RectangleD(0, 0, 0, 0), img, displayMode)
	{
		//
	}
	
	ImageElement::~ImageElement()
	{
		//
	}
	
	void ImageElement::drawMain(ApplicationData appData, Graphics graphics) const
	{
		if(image!=nullptr && isVisible())
		{
			switch(displayMode)
			{
				case DISPLAY_FIT:
				{
					RectangleD frame = getFrame();
					double imgwidth = (double)image->getWidth();
					double imgheight = (double)image->getHeight();
					if(imgwidth!=0 && imgheight!=0 && frame.width!=0 && frame.height!=0)
					{
						RectangleD drawFrame(frame.x, frame.y, imgwidth, imgheight);
						drawFrame.scaleToFit(frame);
						graphics.drawImage(image, drawFrame.x, drawFrame.y, drawFrame.width, drawFrame.height);
					}
				}
				break;
				
				case DISPLAY_ZOOM:
				{
					RectangleD frame = getFrame();

					double imgwidth = (double)image->getWidth();
					double imgheight = (double)image->getHeight();
					if(imgwidth!=0 && imgheight!=0 && frame.width!=0 && frame.height!=0)
					{
						RectangleD drawFrame(frame.x, frame.y, imgwidth, imgheight);
						drawFrame.scaleToFill(frame);
						graphics.clip(frame);
						graphics.drawImage(image, drawFrame.x, drawFrame.y, drawFrame.width, drawFrame.height);
					}
				}
				break;
				
				case DISPLAY_STRETCH:
				default:
				{
					graphics.drawImage(image, getFrame());
				}
				break;
			}
		}
	}

	void ImageElement::setImage(TextureImage*img)
	{
		image = img;
	}
	
	void ImageElement::setDisplayMode(const DisplayMode&mode)
	{
		displayMode = mode;
	}
	
	TextureImage* ImageElement::getImage() const
	{
		return image;
	}
	
	ImageElement::DisplayMode ImageElement::getDisplayMode() const
	{
		return displayMode;
	}
}
