
#pragma once

#include "../Screen/Drawable.h"

namespace GameLibrary
{
	/*! An overrideable implementation of GameLibrary::Drawable that provides the necessities to create a dynamic, movable, scalable, rotatable object that can be updated and drawn.*/
	class Actor : public Drawable
	{
		friend class SpriteActor;
		friend class TextActor;
		friend class WireframeActor;
	public:
		/*! x coordinate of the Actor. The x coordinate is 0 by default.*/
		float x;
		/*! y coordinate of the Actor. The x coordinate is 0 by default.*/
		float y;
		
		
		/*! default constructor*/
		Actor();
		/*! virtual destructor*/
		virtual ~Actor();
		
		
		/*! Updates certain properties of the Actor, such as mouse state, and calls Actor events.
			\param appData specifies information about the Application updating the Actor, such as the Window object, the View transform, etc. \see GameLibrary::ApplicationData*/
		virtual void update(ApplicationData appData) override;
		/*! Draws the Actor to the screen using the specified Graphics object
			\param appData specifies information about the Application drawing the Actor, such as the Window object, the View transform, etc. \see GameLibrary::ApplicationData
			\param graphics the graphics object used to draw the Actor*/
		virtual void draw(ApplicationData appData, Graphics graphics) const override;
		
		
		/*! Gets the actual bounding box of the Actor. The bounding box resizes based on rotation, scaling, and other transformations.
			\returns a RectangleF object representing the Actor's bounding box*/
		virtual RectangleF getFrame() const override;
		
		
		/*! Scales and repositions the Actor to fit within the specified container
			\param container the frame to fit the Actor into.
			\note this function will not work correctly if the Actor's scale value is set to 0*/
		virtual void scaleToFit(const RectangleF&container);
		/*! Scales the Actor to fit within the specified size
			\param the size to fit the Actor within
			\note this function will not work correctly if the Actor's scale value is set to 0*/
		void scaleToFit(const Vector2f&size);
		
		
		/*! Gets the width of the Actor object. This value is affected by scale, but is not affected by rotation.
			\returns a float representing the width of the Actor
			\note this is NOT the same as getting the width from Actor::getFrame()*/
		float getWidth() const;
		/*! Gets the height of the Actor object This value is affected by scale, but is not affected by rotation.
			\returns a float representing the width of the Actor
			\note this is NOT the same as getting the width from Actor::getFrame()*/
		float getHeight() const;
		
		
		/*! Sets whether the Actor is visible when drawn or not. This does not affect whether the mouse can detect the Actor. Actor is visible by default.
			\param visible true makes the actor visible, false makes the actor invisible*/
		void setVisible(bool visible);
		/*! Sets the color of the Actor. This has a slightly different effect on different subclasses of Actor. Color is white {r=255; g=255; b=255; a=255} by default.
			\link GameLibrary::SpriteActor - composites the color on the sprite
			\link GameLibrary::TextActor - sets the text color
			\link GameLibrary::WireframeActor - sets the wireframe color
			\see GameLibrary::Color
			\param color the color to set the Actor*/
		void setColor(const Color&color);
		/*! Rotates the actor by the specified amount of degrees with the origin at its (x,y) position. Rotation is 0 by default.
			\see GameLibrary::Actor::x
			\see GameLibrary::Actor::y
			\param degrees the rotation, in degrees, to rotate the Actor*/
		void rotate(float degrees);
		/*! Sets the rotation of the Actor to the specified amount of degrees with the origin at its (x,y) position. Rotation does affect mouse states. Rotation is 0 by default.
			\see GameLibrary::Actor::x
			\see GameLibrary::Actor::y
			\param degrees the rotation, in degrees, to set the Actor's rotation*/
		void setRotation(float degrees);
		/*! Sets the transparency level of the Actor. This does not affect whether the mouse can detect the Actor. Alpha is 1 by default (fully visible).
			\param alpha the alpha level, from 0 (fully invisible) to 1 (fully visible)*/
		void setAlpha(float alpha);
		/*! Sets the scale of the Actor with the origin at its (x,y) position. This does affect mouse states. Scale is 1 by default.
			\see GameLibrary::Actor::x
			\see GameLibrary::Actor::y
			\param scale the ratio to scale the Actor from its default size*/
		void setScale(float scale);
		/*! Sets the frame (bounding box) and the border of the Actor to be drawn on top of the Actor when GameLibrary::Actor::draw is called. This is good for testing. Frame is not visible by default.
			\param visible true makes the frame and border visible, false makes the frame and border invisible*/
		void setFrameVisible(bool visible);
		/*! Sets the color of the frame (bounding box) and the border of the Actor. Frame and border color are green {r=0; g=255; b=0; a=255} by default.
			\see GameLibrary::Actor::setFrameVisible
			\param color the color to draw the frame and border*/
		void setFrameColor(const Color&color);
		/*! Sets whether the Actor is mirrored horizontally or not. If the Actor is mirrored, it will be drawn inverted horizontally. This does affect mouse states. Horizontal mirroring is false by default.
			\param mirror true makes the Actor drawn inverted horizontally, and false makes the Actor drawn correctly horizontally*/
		void setMirroredHorizontal(bool mirror);
		/*! Sets whether the Actor is mirrored vertically or not. If the Actor is mirrored, it will be drawn inverted vertically. This does affect mouse states. Vertical mirroring is false by default.
			\param mirror true makes the Actor drawn inverted horizontally, and false makes the Actor drawn correctly horizontally*/
		void setMirroredVertical(bool mirror);
		
		
		/*! Tells whether the Actor has been set visible. Visibility is true by default.
			\see GameLibrary::Actor::setVisible
			\returns true means the Actor has been set visible, false means the Actor has been set invisible*/
		bool isVisible() const;
		/*! Gets the color of the Actor.  Color is white {r=255; g=255; b=255; a=255} by default.
			\see GameLibrary::Actor::setColor
			\returns a const reference to a Color object representing the Actor's color*/
		const Color& getColor() const;
		/*! Gets the Actor's rotation, in degrees, on its (x,y) origin. Rotation is 0 by default.
			\see GameLibrary::Actor::setRotation
			\returns a float value representing the Actor's rotation in degrees*/
		float getRotation() const;
		/*! Gets the Actor's alpha value. Alpha is 1 by default (fully visible).
			\see GameLibrary::Actor::setAlpha
			\returns a float representing the alpha level, from 0 (fully invisible) to 1 (fully visible)*/
		float getAlpha() const;
		/*! Gets the Actor's scale ratio. Scale is 1 by default.
			\see GameLibrary::Actor::setScale
			\returns a float representing the ratio the Actor has been scaled*/
		float getScale() const;
		/*! Tells whether the Actor's frame (bounding box) and border have been set visible. Frame and border visibility is false by default.
			\see GameLibrary::Actor::setFrameVisible
			\returns true if the Actor's frame and border are visible, and false if the frame and border are invisible*/
		bool isFrameVisible() const;
		/*! Gets the color of the Actor's frame (bounding box) and border. Frame and border color are green {r=0; g=255; b=0; a=255} by default.
			\see GameLibrary::Actor::setFrameColor
			\returns a const reference to a Color object representing the Actor's frame and border color*/
		const Color& getFrameColor() const;
		/*! Tells whether the Actor is drawn horizontally inverted. Horizontal mirroring is false by default.
			\see GameLibrary::Actor::setMirroredHorizontal
			\returns true if the Actor is mirrored horizontally, false if otherwise.*/
		bool isMirroredHorizontal() const;
		/*! Tells whether the Actor is drawn vertically inverted. Vertical mirroring is false by default.
			\see GameLibrary::Actor::setMirroredVertical
			\returns true if the Actor is mirrored vertically, false if otherwise.*/
		bool isMirroredVertical() const;
		
		
		/*! Tells whether the Mouse or a Multitouch input was hovering over the Actor in the most recent update call. This function does not recheck the mouse. The Actor's mouse state gets updated every time GameLibrary::Actor::update is called.
			\see GameLibrary::Actor::update
			\returns true if a Mouse or Multitouch input was hovering over the Actor in the most recent update call, and false if otherwise.*/
		bool isMouseOver() const;
		/*! Tells whether the Mouse or a Multitouch input was hovering over the Actor in the previous (before the most recent) update call. This function does not recheck the mouse. The Actor's mouse state gets updated every time GameLibrary::Actor::update is called.
			\see GameLibrary::Actor::update
			\returns true if a Mouse or Multitouch input was hovering over the Actor in the previous update call, and false if otherwise.*/
		bool wasMouseOver() const;
		/*! Tells whether the Mouse or a Multitouch input was pressing the Actor in the most recent update call. This function does not recheck the mouse. The Actor's mouse state gets updated every time GameLibrary::Actor::update is called.
			\see GameLibrary::Actor::update
			\returns true if a Mouse or Multitouch input was pressing the Actor in the most recent update call, and false if otherwise.*/
		bool isMousePressed() const;
		/*! Tells whether the Mouse or a Multitouch input was pressing the Actor in the previous (before the most recent) call. This function does not recheck the mouse. The Actor's mouse state gets updated every time GameLibrary::Actor::update is called.
			\see GameLibrary::Actor::update
			\returns true if a Mouse or Multitouch input was pressing the Actor in the previous update call, and false if otherwise.*/
		bool wasMousePressed() const;
		/*! Tells whether the Actor was just pressed in the most recent update call. This function does not recheck the mouse. The Actor's mouse state gets updated every time GameLibrary::Actor::update is called.
			\see GameLibrary::Actor::update
			\returns true if a Mouse or Multitouch input just pressed the Actor in the most recent update call, and false if otherwise.*/
		bool didMousePress() const;
		/*! Tells whether the Actor was just released in the most recent update call. This function does not recheck the mouse. The Actor's mouse state gets updated every time GameLibrary::Actor::update is called.
			\see GameLibrary::Actor::update
			\returns true if a Mouse or Multitouch input just released the Actor in the most recent update call, and false if otherwise.
			\note the Actor may still be pressed. This function just checks to see if any touchID or mouseIndex released the Actor.*/
		bool didMouseRelease() const;
		
		
		/*! Clears all the stored mouse and multitouch data from the Actor.
			\note This function does NOT set any of the mouse states (isMousePressed, isMouseReleased, etc.) to false.*/
		void clearMouseState();
		
		
		/*! Called when a Mouse or Multitouch input presses the Actor. This function is called within the Actor's update function. \see GameLibrary::Actor::update
			\param appData specifies information about the Application updating the Actor, such as the Window object, the View transform, etc. \see GameLibrary::ApplicationData
			\param touchID the touchID or mouseIndex of the input. If Multitouch::isEnabled() returns true, touchID represents a multitouch id. Otherwise, touchID represents a mouse index. \see GameLibrary::Mouse \see GameLibrary::Multitouch*/
		virtual void onMousePress(ApplicationData appData, unsigned int touchID);
		/*! Called when a Mouse or Multitouch input releases the Actor. This function is called within the Actor's update function. \see GameLibrary::Actor::update
			\param appData specifies information about the Application updating the Actor, such as the Window object, the View transform, etc. \see GameLibrary::ApplicationData
			\param touchID the touchID or mouseIndex of the input. If Multitouch::isEnabled() returns true, touchID represents a multitouch id. Otherwise, touchID represents a mouse index. \see GameLibrary::Mouse \see GameLibrary::Multitouch*/
		virtual void onMouseRelease(ApplicationData appData, unsigned int touchID);
		/*! Called when a Mouse or Multitouch input enters (hovers over) the Actor. This function is called within the Actor's update function. \see GameLibrary::Actor::update
			\param appData specifies information about the Application updating the Actor, such as the Window object, the View transform, etc. \see GameLibrary::ApplicationData
			\param touchID the touchID or mouseIndex of the input. If Multitouch::isEnabled() returns true, touchID represents a multitouch id. Otherwise, touchID represents a mouse index. \see GameLibrary::Mouse \see GameLibrary::Multitouch*/
		virtual void onMouseEnter(ApplicationData appData, unsigned int touchID);
		/*! Called when a Mouse or Multitouch input leaves (stops hovering over) the Actor. This function is called within the Actor's update function. \see GameLibrary::Actor::update
			\param appData specifies information about the Application updating the Actor, such as the Window object, the View transform, etc. \see GameLibrary::ApplicationData
			\param touchID the touchID or mouseIndex of the input. If Multitouch::isEnabled() returns true, touchID represents a multitouch id. Otherwise, touchID represents a mouse index. \see GameLibrary::Mouse \see GameLibrary::Multitouch*/
		virtual void onMouseLeave(ApplicationData appData, unsigned int touchID);
		
		
		/*! Updates the Actor's size, based on its properties (scale, rotation, etc.) and stores it. Called by the Actor when new properties have been set through their function in Actor.*/
		virtual void updateSize();
		/*! Checks whether a specified point is colliding with the Actor.
			\param point an (x,y) coordinate to check.
			\returns true if the point collides with the Actor, false if otherwise.
			\note this function is inefficient in loops. It should be used for checking single pixels, and not for pixel level collisions.*/
		virtual bool checkPointCollision(const Vector2f&point);
		
	private:
		float width;
		float height;
		
		bool clicked;
		bool prevclicked;
		bool mouseover;
		bool prevmouseover;
		bool didpress;
		bool didrelease;
		bool visible;
		bool mirroredHorizontal;
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
			unsigned int touchID;
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
		void callMouseEvents(ApplicationData&appData, const ArrayList<Pair<unsigned int, byte> >& eventCallData);
	};
}
