
#pragma once

#include "Actor.h"

namespace GameLibrary
{
	/*! A specialized Actor for drawing frames or boxes. It can also be used to create regions.
	WireframeActor can be thought of as a Rectangle with extra functionality.*/
	class WireframeActor : public Actor
	{
	public:
		/*! default constructor*/
		WireframeActor();
		/*! Constructs a WireframeActor with the specified x and y coordinates. The width and height are set to 0.
			\param x the x coordinate
			\param y the y coordinate*/
		WireframeActor(float x, float y);
		/*! Constructs a WireframeActor with and (x,y) position and a width and height.
			\param x the x coordinate
			\param y the y coordinate
			\param width the width of the wireframe
			\param height the height of the wireframe*/
		WireframeActor(float x, float y, float width, float height);
		/*! virtual destructor*/
		virtual ~WireframeActor();
		
		
		/*! \copydoc GameLibrary::Actor::update(ApplicationData)*/
		virtual void update(ApplicationData appData) override;
		/*! \copydoc GameLibrary::Actor::draw(ApplicationData,Graphics)const*/
		virtual void draw(ApplicationData appData, Graphics graphics) const override;
		
		
		/*! \copydoc GameLibrary::Actor::getFrame()const*/
		virtual RectangleF getFrame() const override;
		
		
		/*! \copydoc GameLibrary::Actor::scaleToFit(const RectangleF&)*/
		virtual void scaleToFit(const RectangleF&container) override;
		
		
		/*! Sets the width and height of the wireframe. Equivelant to Wireframe::setSize(float,float).
			\param size the width (size.x) and height (size.y) of the wireframe*/
		void setSize(const Vector2f&size);
		/*! Sets the width and height of the wireframe. Equivelant to Wireframe::setSize(const Vector2f&).
			\param width the width of the wireframe
			\param height the height of the wireframe*/
		void setSize(float width, float height);
		
		
		/*! Sets whether the wireframe will draw as a solid rectangle, or as a frame. This does not affect the mouse state. Fill is false by default.
			\param filled true to draw as a solid rectangle, false to draw as a frame.*/
		void setFilled(bool filled);
		
		
		/*! Gets the size (width and height) of the wireframe. These values are not affected scale or rotation.
			\returns a Vector2f containing the width (x) and height (y) of the wireframe.*/
		const Vector2f& getSize() const;
		/*! Tells whether the wireframe draws as a solid rectangle, or as a frame. This value has no affect on the mouse state.
			\returns true if the wireframe draws as a solid rectangle, or false if otherwise*/
		bool isFilled() const;
		
		/*! \copydoc GameLibrary::Actor::updateSize()*/
		virtual void updateSize() override;
		/*! \copydoc GameLibrary::Actor::checkPointCollision(const Vector2f&)*/
		virtual bool checkPointCollision(const Vector2f&point) override;
		
	protected:
		/*! Special draw function to draw the WireframeActor with specific properties. These properties are not stored into the WireframeActor. This function is called from WireframeActor::draw
			\param appData specifies information about the Application drawing the WireframeActor, such as the Window object, the View transform, etc. \see GameLibrary::ApplicationData
			\param graphics the graphics object used to draw the WireframeActor
			\param x the x coordinate
			\param y the y coordinate
			\param scale the ratio to size the WireframeActor from its default size*/
		virtual void drawActor(ApplicationData&appData, Graphics&graphics, float x, float y, float scale) const;
		
	private:
		bool filled;
		Vector2f size;
		RectangleF framerect;
	};
}
