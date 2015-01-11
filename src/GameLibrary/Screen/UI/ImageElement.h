
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
		ImageElement(const RectangleF&frame);
		ImageElement(const RectangleF&frame, TextureImage*image);
		virtual ~ImageElement();
		
		virtual void draw(ApplicationData appData, Graphics graphics) const;

		void setImage(TextureImage*);
		void setMaintainAspectRatio(bool);

		TextureImage* getImage() const;
		bool maintainsAspectRatio() const;
	};
}
