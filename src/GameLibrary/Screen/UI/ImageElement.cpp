
#include "ImageElement.h"

namespace GameLibrary
{
	ImageElement::ImageElement() : ImageElement(RectangleF(0,0,0,0),nullptr)
	{
		//
	}
	
	ImageElement::ImageElement(const RectangleF&frame) : ImageElement(frame,nullptr)
	{
		//
	}
	
	ImageElement::ImageElement(const RectangleF&frame, TextureImage*img) : ScreenElement(frame)
	{
		image = img;
		maintainAspectRatio = false;
	}
	
	ImageElement::~ImageElement()
	{
		//
	}
	
	void ImageElement::drawMain(ApplicationData appData, Graphics graphics) const
	{
		if(image!=nullptr)
		{
			if(maintainAspectRatio)
			{
				RectangleF frame = getFrame();
				
				float imgwidth = (float)image->getWidth();
				float imgheight = (float)image->getHeight();
				
				if(imgwidth!=0 && imgheight!=0 && frame.width!=0 && frame.height!=0)
				{
					float fixedWidth = frame.width;
					float fixedHeight = frame.height;
					
					if(frame.width > frame.height)
					{
						// frame height is first constraint
						if(frame.height < imgheight)
						{
							fixedHeight = frame.height;
							float ratY = frame.height/imgheight;
							fixedWidth = imgwidth*ratY;
						}
						else if(frame.width < imgwidth)
						{
							fixedWidth = frame.width;
							float ratX = frame.width/imgwidth;
							fixedHeight = imgheight*ratX;
						}
					}
					else
					{
						// frame width is first constraint
						if(frame.width < imgwidth)
						{
							fixedWidth = frame.width;
							float ratX = frame.width/imgwidth;
							fixedHeight = imgheight*ratX;
						}
						else if(frame.height < imgheight)
						{
							fixedHeight = frame.height;
							float ratY = frame.height/imgheight;
							fixedWidth = imgwidth*ratY;
						}
					}
					
					Vector2f offset(0,0);
					offset.x = (frame.width - fixedWidth)/2;
					offset.y = (frame.height - fixedHeight)/2;
					
					graphics.drawImage(image, frame.x+offset.x, frame.y+offset.y, fixedWidth, fixedHeight);
				}

				//TODO add sizing up if the image is smaller than the frame
			}
			else
			{
				graphics.drawImage(image, getFrame());
			}
		}
	}

	void ImageElement::setImage(TextureImage*img)
	{
		image = img;
	}
	
	void ImageElement::setMaintainAspectRatio(bool toggle)
	{
		maintainAspectRatio = toggle;
	}
	
	TextureImage* ImageElement::getImage() const
	{
		return image;
	}
	
	bool ImageElement::maintainsAspectRatio() const
	{
		return maintainAspectRatio;
	}
}
