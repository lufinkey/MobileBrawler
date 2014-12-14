
#include "BaseActor.h"

namespace GameLibrary
{
	class WireframeActor : public BaseActor
	{
	public:
		WireframeActor();
		WireframeActor(float x, float y);
		WireframeActor(float x, float y, float width, float height);
		virtual ~WireframeActor();
		
		virtual void update(ApplicationData appData);
		virtual void draw(ApplicationData appData, Graphics graphics) const;
		
		virtual RectangleF getFrame() const;
		
		void setFilled(bool);
		bool isFilled() const;

	private:
		bool filled;
	};
}
