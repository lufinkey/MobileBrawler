
#pragma once

#include "../ScreenElement.h"

namespace GameLibrary
{
	/*! Displays an image to the Window. This class is non-copyable.*/
	class ImageElement : public ScreenElement
	{
	public:
		/*! The method of displaying the image within the element.*/
		typedef enum
		{
			/*! Stretch the image to fill the frame*/
			DISPLAY_STRETCH,
			/*! Scale the image to be contained within the frame, but maintain the aspect ratio of the image.*/
			DISPLAY_FIT,
			/*! Scale the image to fill the frame, but don't stretch the image. If a part of the image is outside the frame, it is clipped.*/
			DISPLAY_ZOOM
		} DisplayMode;
		
		/*! default constructor; */
		ImageElement();
		/*! \copydoc GameLibrary::ScreenElement::ScreenElement(const RectangleD&frame)*/
		ImageElement(const RectangleD&frame);
		/*! Constructs a screen element with a frame and an image to display with a given display mode
			\param frame the frame (bounding box) of the element
			\param image the image to display inside the element
			\param displayMode the method to use for displaying the image; Default value is DISPLAY_STRETCH*/
		ImageElement(const RectangleD&frame, TextureImage*image, const ImageElement::DisplayMode&displayMode = DISPLAY_STRETCH);
		/*! Constructs a screen element with an image to display with a given display mode
			\param image the image to display inside the element
			\param displayMode the method to use for displaying the image; Default value is DISPLAY_STRETCH*/
		ImageElement(TextureImage*image, const ImageElement::DisplayMode&displayMode = DISPLAY_STRETCH);
		/*! virtual destructor*/
		virtual ~ImageElement();
		
		
		ImageElement(const ImageElement&) = delete;
		ImageElement& operator=(const ImageElement&) = delete;
		
		
		/*! Sets the TextureImage for the element to display.
			\param image the TextureImage to display, or null to not display an image*/
		void setImage(TextureImage*image);
		/*! Sets the display method to display the TextureImage within the element.
			\param mode a constant that dictates how to display the image \see GameLibrary::ImageElement::DisplayMode*/
		void setDisplayMode(const DisplayMode&mode);
		
		
		/*! Gets the current TextureImage being displayed.
			\returns a TextureImage pointer, or null if no image is being displayed*/
		TextureImage* getImage() const;
		/*! Gets the current display method for the TextureImage within the element.
			\returns an ImageElement::DisplayMode constant*/
		DisplayMode getDisplayMode() const;
		
		
	protected:
		/*! \copydoc GameLibrary::ScreenElement::drawMain(GameLibrary::ApplicationData,GameLibrary::Graphics)const*/
		virtual void drawMain(ApplicationData appData, Graphics graphics) const override;
		
	private:
		TextureImage* image;
		DisplayMode displayMode;
	};
}
