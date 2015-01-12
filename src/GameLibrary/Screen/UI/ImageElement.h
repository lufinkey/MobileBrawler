
#include "../ScreenElement.h"

namespace GameLibrary
{
	class ImageElement : public ScreenElement
	{
	private:
		TextureImage* image;
		bool maintainAspectRatio;
		
	public:
		ImageElement();
		ImageElement(const ImageElement&) = delete;
		ImageElement(const RectangleF&frame);
		ImageElement(const RectangleF&frame, TextureImage*image);
		virtual ~ImageElement();
		
		ImageElement& operator=(const ImageElement&) = delete;
		
		virtual void draw(ApplicationData appData, Graphics graphics) const;

		void setImage(TextureImage*);
		void setMaintainAspectRatio(bool);

		TextureImage* getImage() const;
		bool maintainsAspectRatio() const;
	};
}
