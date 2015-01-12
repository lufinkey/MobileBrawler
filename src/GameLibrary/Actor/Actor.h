
#pragma once

#include "../Screen/Drawable.h"

namespace GameLibrary
{
	class Actor : public Drawable
	{
		friend class SpriteActor;
		friend class TextActor;
		friend class WireframeActor;
	public:
		enum ActorType
		{
			ACTORTYPE_BASE,
			ACTORTYPE_NORMAL,
			ACTORTYPE_WIREFRAME,
			ACTORTYPE_TEXT
		};
		typedef enum ActorType ActorType;
		
		float x;
		float y;
		
		Actor();
		Actor(const Actor&) = delete;
		virtual ~Actor();
		
		Actor& operator=(const Actor&) = delete;
		
		virtual void update(ApplicationData appData);
		virtual void draw(ApplicationData appData, Graphics graphics) const;
		
		virtual RectangleF getFrame() const;
		
		ActorType getActorType() const;
		float getWidth() const;
		float getHeight() const;
		
		void setVisible(bool);
		void setColor(const Color&);
		void rotate(float degrees);
		void setRotation(float degrees);
		void setAlpha(float alpha);
		void setScale(float scale);
		void scaleToFit(const RectangleF&rect);
		void setFrameVisible(bool);
		void setFrameColor(const Color&);
		void setMirrored(bool);
		void setMirroredVertical(bool);
		
		bool isVisible() const;
		const Color& getColor() const;
		float getRotation() const;
		float getAlpha() const;
		float getScale() const;
		bool isFrameVisible() const;
		const Color& getFrameColor() const;
		bool isMirrored() const;
		bool isMirroredVertical() const;
		
		virtual bool isOnScreen(View*view) const;
		
		bool isMouseOver() const;
		bool wasMouseOver() const;
		bool isMousePressed() const;
		bool wasMousePressed() const;
		bool didMousePress() const;
		bool didMouseRelease() const;

		void clearMouseState();

		virtual void onMousePress(Window*window, unsigned int touchID);
		virtual void onMouseRelease(Window*window, unsigned int touchID);
		virtual void onMouseEnter(Window*window, unsigned int touchID);
		virtual void onMouseLeave(Window*window, unsigned int touchID);
		
	protected:
		virtual void updateSize();
		virtual bool checkPointCollision(const Vector2f&point);
		
	private:
		float width;
		float height;
		
		ActorType actorType;
		bool clicked;
		bool prevclicked;
		bool mouseover;
		bool prevmouseover;
		bool didpress;
		bool didrelease;
		bool visible;
		bool mirrored;
		bool mirroredVertical;
		bool frame_visible;
		Color color;
		Color frame_color;
		float rotation;
		float alpha;
		float scale;

		Transform rotationMatrix;
		Transform inverseRotationMatrix;

		typedef struct
		{
			unsigned long touchID;
			bool pressed;
		} MouseTouchData;
		ArrayList<MouseTouchData> currentTouches;

		bool isTouchDataActive(unsigned int touchID);
		bool isTouchDataPressed(unsigned int touchID);
		void applyTouchData(unsigned int touchID, bool pressed);
		void removeTouchData(unsigned int touchID);
		MouseTouchData* getTouchData(unsigned int touchID);
		ArrayList<unsigned int> getDifTouchData(const ArrayList<unsigned int>&touchIDs);

		void updateMouse(ApplicationData&appData);
		void updateTouch(ApplicationData&appData);
		void callMouseEvents(Window*window, const ArrayList<Pair<unsigned int, byte> >& eventCallData);
	};
}
