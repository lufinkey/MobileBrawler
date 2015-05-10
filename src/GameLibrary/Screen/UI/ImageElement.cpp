
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
		srcrect = nullptr;
		image = img;
		displayMode = displayMd;
	}
	
	ImageElement::ImageElement(TextureImage*img, const ImageElement::DisplayMode&displayMode) : ImageElement(RectangleD(0, 0, 0, 0), img, displayMode)
	{
		//
	}
	
	ImageElement::~ImageElement()
	{
		if(srcrect != nullptr)
		{
			delete srcrect;
			srcrect = nullptr;
		}
	}
	
	void ImageElement::drawMain(ApplicationData appData, Graphics graphics) const
	{
		if(image!=nullptr && isVisible())
		{
			RectangleU srcRect = getImageSourceRect();
			switch(displayMode)
			{
				default:
				case DISPLAY_STRETCH:
				{
					graphics.drawImage(image, getFrame(), srcRect);
				}
				break;
				
				case DISPLAY_FIT:
				{
					RectangleD frame = getFrame();
					double imgwidth = (double)srcRect.width;
					double imgheight = (double)srcRect.height;
					if(imgwidth!=0 && imgheight!=0 && frame.width!=0 && frame.height!=0)
					{
						RectangleD drawFrame(frame.x, frame.y, imgwidth, imgheight);
						drawFrame.scaleToFit(frame);
						graphics.drawImage(image, drawFrame.x, drawFrame.y, drawFrame.width, drawFrame.height, srcRect.x, srcRect.y, srcRect.x+srcRect.width, srcRect.y+srcRect.height);
					}
				}
				break;
				
				case DISPLAY_ZOOM:
				{
					RectangleD frame = getFrame();

					double imgwidth = (double)srcRect.width;
					double imgheight = (double)srcRect.height;
					if(imgwidth!=0 && imgheight!=0 && frame.width!=0 && frame.height!=0)
					{
						RectangleD drawFrame(frame.x, frame.y, imgwidth, imgheight);
						drawFrame.scaleToFill(frame);
						graphics.clip(frame);
						graphics.drawImage(image, drawFrame.x, drawFrame.y, drawFrame.width, drawFrame.height, srcRect.x, srcRect.y, srcRect.x+srcRect.width, srcRect.y+srcRect.height);
					}
				}
				break;
				
				case DISPLAY_REPEAT:
				{
					RectangleD frame = getFrame();
					graphics.clip(frame);
					double imgwidth = (double)srcRect.width;
					double imgheight = (double)srcRect.height;
					unsigned int imageTimesX = (unsigned int)Math::ceil(frame.width/imgwidth);
					unsigned int imageTimesY = (unsigned int)Math::ceil(frame.height/imgheight);
					RectU srcRect2(srcRect);
					for(unsigned int y=0; y<imageTimesY; y++)
					{
						for(unsigned int x=0; x<imageTimesX; x++)
						{
							double imageX = frame.x + (imgwidth*((double)imageTimesX));
							double imageY = frame.y + (imgheight*((double)imageTimesY));
							graphics.drawImage(image, imageX, imageY, imgwidth, imgheight, srcRect2.left, srcRect2.top, srcRect2.right, srcRect2.bottom);
						}
					}
				}
				break;
			}
		}
	}

	void ImageElement::setImage(TextureImage*img)
	{
		image = img;
		if(srcrect != nullptr)
		{
			delete srcrect;
			srcrect = nullptr;
		}
	}
	
	void ImageElement::setDisplayMode(const DisplayMode&mode)
	{
		displayMode = mode;
	}
	
	void ImageElement::setImageSourceRect(const RectangleU&srcRect)
	{
		if(srcrect != nullptr)
		{
			delete srcrect;
			srcrect = nullptr;
		}
		srcrect = new RectangleU(srcRect.x, srcRect.y, srcRect.width, srcRect.height);
	}
	
	TextureImage* ImageElement::getImage() const
	{
		return image;
	}
	
	ImageElement::DisplayMode ImageElement::getDisplayMode() const
	{
		return displayMode;
	}
	
	RectangleU ImageElement::getImageSourceRect() const
	{
		if(image == nullptr)
		{
			return RectangleU(0,0,0,0);
		}
		else if(srcrect == nullptr)
		{
			return RectangleU(0,0,image->getWidth(),image->getHeight());
		}
		else
		{
			return *srcrect;
		}
	}
}
