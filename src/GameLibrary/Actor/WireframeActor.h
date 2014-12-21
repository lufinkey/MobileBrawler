
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

		void setSize(const Vector2f&);
		void setSize(float width, float height);
		void setFilled(bool);
		
		const Vector2f& getSize() const;
		bool isFilled() const;
		
	protected:
		virtual void updateSize();
		virtual void drawActor(ApplicationData&appData, Graphics&graphics, float x, float y, float scale) const;
		
	private:
		bool filled;
		Vector2f size;
		RectangleF framerect;
	};
}
