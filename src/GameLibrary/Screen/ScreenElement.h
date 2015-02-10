
#pragma once

#include "Drawable.h"
#include "../Exception/IllegalArgumentException.h"
#include "../Exception/IllegalStateException.h"
#include "../Utilities/ArrayList.h"
#include "../Utilities/Pair.h"
#include <mutex>

namespace GameLibrary
{
	/*! A stackable element that can be added to a Screen*/
	class ScreenElement : public Drawable
	{
		friend class Screen;
		friend class ScreenManager;
	public:
		/*! default constructor*/
		ScreenElement();
		/*! Constructs an element with a given frame (bounding box).
			\param frame the bounding box of the element*/
		ScreenElement(const RectangleF&frame);
		/*! virtual destructor*/
		virtual ~ScreenElement();
		
		
		ScreenElement(const ScreenElement&) = delete;
		ScreenElement& operator=(const ScreenElement&) = delete;
		
		
		/*! Updates any properties of the element, and updates all the child elements.
			\param appData specifies information about the Application updating the element, such as the Window object, the View transform, etc. \see GameLibrary::ApplicationData*/
		virtual void update(ApplicationData appData) override;
		/*! Draws the element and all of its child elements. This function calls drawBackground, drawMain, and drawElements respectively.
			\param appData specifies information about the Application drawing the element, such as the Window object, the View transform, etc. \see GameLibrary::ApplicationData
			\param graphics the Graphics object used to draw the element*/
		virtual void draw(ApplicationData appData, Graphics graphics) const override;
		
		
		/*! Sets the actual frame (bounding box) of the element inside of its parent.
			\param frame a RectangleF object representing the element's bounding box within its parent*/
		virtual void setFrame(const RectangleF&frame);
		/*! Gets the actual frame (bounding box) of the element inside of its parent.
			\returns a RectangleF object representing the element's bounding box within its parent*/
		virtual RectangleF getFrame() const override;
		/*! Gets the center coordinates of the frame.
			\returns a Vector2f point*/
		Vector2f getCenter() const;
		
		
		/*! Adds a child element to this element.
			\param element a ScreenElement pointer
			\throws GameLibrary::IllegalArgumentException if element is null, or if the element is already a child of another ScreenElement*/
		void addChildElement(ScreenElement*element);
		/*! Removes this element from its parent element, or returns if it has no parent element.
			\throws GameLibrary::IllegalStateException if this element is not stored within its parent element*/
		void removeFromParentElement();
		/*! Brings a child element to the front of the element list.
			\param element a ScreenElement pointer
			\throws GameLibrary::IllegalArgumentException if element is null, or if the element is not a child of this element
			\throws GameLibrary::IllegalStateException if this element is not stored within its parent element*/
		void bringChildElementToFront(ScreenElement*element);
		/*! Sends a child element to the back of the element list.
			\param element a ScreenElement pointer
			\throws GameLibrary::IllegalArgumentException if element is null, or if the element is not a child of this element
			\throws GameLibrary::IllegalStateException if this element is not stored within its parent element*/
		void sendChildElementToBack(ScreenElement*element);
		
		
		/*! Gets the list of child elements of this element.
			\returns a const ArrayList reference of ScreenElement pointers*/
		const ArrayList<ScreenElement*>& getChildElements() const;
		/*! Gets the parent element of this element.
			\returns a ScreenElement pointer*/
		ScreenElement* getParentElement() const;
		
		
		/*! Sets the background color of this element.
			\param color a Color value*/
		void setBackgroundColor(const Color&color);
		/*! Gets the background of this element.
			\returns a const Color value reference*/
		const Color& getBackgroundColor() const;
		
		
		/*! Sets this element's visibility, and optionally sets all its children's visibility.
			\param toggle true to make this element visible, or false to make this element invisible
			\param applyToChildren applies the visibility property to all children of this element; Default value is false*/
		void setVisible(bool toggle, bool applyToChildren=false);
		/*! Tells whether this element's visibility is toggled.
			\returns true if this element is visible, or false if otherwise.*/
		bool isVisible() const;
		
	protected:
		/*! Draws the background color of the element. This function is automatically called from ScreenElement::draw.
			\param appData specifies information about the Application drawing the element, such as the Window object, the View transform, etc. \see GameLibrary::ApplicationData
			\param graphics the Graphics object used to draw the element*/
		virtual void drawBackground(ApplicationData appData, Graphics graphics) const;
		/*! Draws the main content of the element. This does nothing by default, and is intended to be overridden. This function is automatically called from ScreenElement::draw.
			\param appData specifies information about the Application drawing the element, such as the Window object, the View transform, etc. \see GameLibrary::ApplicationData
			\param graphics the Graphics object used to draw the element*/
		virtual void drawMain(ApplicationData appData, Graphics graphics) const;
		/*! Draws all the child elements of this element. This function is automatically called from ScreenElement::draw.
			\param appData specifies information about the Application drawing the element, such as the Window object, the View transform, etc. \see GameLibrary::ApplicationData
			\param graphics the Graphics object used to draw the element*/
		virtual void drawElements(ApplicationData appData, Graphics graphics) const;
		
		
		/*! Called when this element is removed from an element that is stored in a Screen, which is presented on, or is itself, a root screen.
			\param window the Window pointer*/
		virtual void onRemoveFromWindow(Window*window);
		/*! Called when this element is added to an element that is stored in a Screen, which is presented on, or is itself, a root screen.
			\param window the Window pointer*/
		virtual void onAddToWindow(Window*window);
		
	private:
		Window*window;

		RectangleF frame;

		Screen*screen;
		ScreenElement* parentElement;
		ArrayList<ScreenElement*> childElements;
		ArrayList<ScreenElement*> removedChildElements;

		mutable bool updatingElements;

		bool visible;
		Color backgroundColor;

		virtual void setWindow(Window*window);
	};
}
