
#pragma once

#include "UpdateDrawable.h"
#include "AutoLayoutManager.h"
#include "../Exception/IllegalArgumentException.h"
#include "../Exception/IllegalStateException.h"
#include "../Utilities/ArrayList.h"
#include "../Utilities/Pair.h"
#include "../Input/Mouse.h"
#include "../Input/Multitouch.h"
#include <mutex>

namespace GameLibrary
{
	/*! A stackable element that can be added to a Screen*/
	class ScreenElement : public UpdateDrawable
	{
		friend class Screen;
		friend class ScreenManager;
	public:
		/*! default constructor*/
		ScreenElement();
		/*! Constructs an element with a given frame (bounding box).
			\param frame the bounding box of the element*/
		explicit ScreenElement(const RectangleD&frame);
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
			\param frame a RectangleD object representing the element's bounding box within its parent*/
		virtual void setFrame(const RectangleD&frame);
		/*! Gets the actual frame (bounding box) of the element inside of its parent.
			\returns a RectangleD object representing the element's bounding box within its parent*/
		virtual RectangleD getFrame() const override;
		/*! Gets the center coordinates of the frame.
			\returns a Vector2d point*/
		Vector2d getCenter() const;
		
		
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
		
		
		/*! Sets a layout rule to automatically adjust the frame whenever the parent element's frame changes.
		If this element is the child of another element, then the frame will adjust itself accordingly when this function is called.
			\param ruleType the type of layout rule \see GameLibrary::LayoutRuleType
			\param value the value of the rule given, in the specified units
			\param valueType the units of the value parameter \see GameLibrary::LayoutValueType*/
		void setLayoutRule(const LayoutRuleType& ruleType, double value, const LayoutValueType& valueType=LAYOUTVALUE_PIXEL);
		/*! Tells whether any layout rules have been set for this element.
			\returns true if this element has set layout rules, or false if otherwise*/
		bool hasLayoutRules() const;
		/*! Removes any set layout rules from this element.*/
		void removeAllLayoutRules();
		/*! Gets the layout manager for this element.
			\returns a const AutoLayoutManager reference*/
		const AutoLayoutManager& getAutoLayoutManager() const;
		
		
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
			\returns true if this element is visible, or false if otherwise*/
		bool isVisible() const;
		
		/*! Sets whether this element clips its child elements to its frame.
			\param toggle true to make this element clip its child elements to its frame, or false to display its child elements normally*/
		void setClippedToFrame(bool toggle);
		/*! Tells whether this element clips its child elements to its frame.
			\returns true if clipping is enabled, or false if clipping is not enabled*/
		bool isClippedToFrame() const;
		
	protected:
		/*! Updates all the child elements of this element. This function is automatically called from ScreenElement::update.
			\param appData specifies information about the Application drawing the element, such as the Window object, the View transform, etc. \see GameLibrary::ApplicationData*/
		virtual void updateElements(ApplicationData appData);
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
		
		ScreenElement* tellChildrenHandleMouseMove(ApplicationData appData, unsigned int mouseIndex, Vector2d mousepos);
		void tellChildrenElementHandledMouseMove(ApplicationData appData, unsigned int mouseIndex, Vector2d mousepos, ScreenElement* element);
		ScreenElement* tellChildrenHandleMousePress(ApplicationData appData, unsigned int mouseIndex, Mouse::Button button, Vector2d mousepos);
		void tellChildrenElementHandledMousePress(ApplicationData appData, unsigned int mouseIndex, Mouse::Button button, Vector2d mousepos, ScreenElement* element);
		ScreenElement* tellChildrenHandleMouseRelease(ApplicationData appData, unsigned int mouseIndex, Mouse::Button button, Vector2d mousepos);
		void tellChildrenElementHandledMouseRelease(ApplicationData appData, unsigned int mouseIndex, Mouse::Button button, Vector2d mousepos, ScreenElement* element);
		void tellChildrenHandleMouseDisconnect(ApplicationData appData, unsigned int mouseIndex);
		
		ScreenElement* tellChildrenHandleTouchMove(ApplicationData appData, unsigned int touchID, Vector2d touchpos);
		void tellChildrenElementHandledTouchMove(ApplicationData appData, unsigned int touchID, Vector2d touchpos, ScreenElement* element);
		ScreenElement* tellChildrenHandleTouchBegin(ApplicationData appData, unsigned int touchID, Vector2d touchpos);
		void tellChildrenElementHandledTouchBegin(ApplicationData appData, unsigned int touchID, Vector2d touchpos, ScreenElement* element);
		ScreenElement* tellChildrenHandleTouchEnd(ApplicationData appData, unsigned int touchID, Vector2d touchpos);
		void tellChildrenElementHandledTouchEnd(ApplicationData appData, unsigned int touchID, Vector2d touchpos, ScreenElement* element);
		
	private:
		Window*window;
		
		RectangleD frame;
		
		Screen*screen;
		ScreenElement* parentElement;
		ArrayList<ScreenElement*> childElements;
		
		AutoLayoutManager autoLayoutMgr;
		
		bool visible;
		bool clipsToFrame;
		Color backgroundColor;
		
		virtual void setWindow(Window*window);
		void autoLayoutFrame();
		
		virtual ScreenElement* handleMouseMove(const ApplicationData& appData, unsigned int mouseIndex, const Vector2d& mousepos);
		virtual void elementHandledMouseMove(const ApplicationData& appData, unsigned int mouseIndex, const Vector2d& mousepos, ScreenElement* element);
		virtual ScreenElement* handleMousePress(const ApplicationData& appData, unsigned int mouseIndex, Mouse::Button button, const Vector2d& mousepos);
		virtual void elementHandledMousePress(const ApplicationData& appData, unsigned int mouseIndex, Mouse::Button button, const Vector2d& mousepos, ScreenElement* element);
		virtual ScreenElement* handleMouseRelease(const ApplicationData& appData, unsigned int mouseIndex, Mouse::Button button, const Vector2d& mousepos);
		virtual void elementHandledMouseRelease(const ApplicationData& appData, unsigned int mouseIndex, Mouse::Button button, const Vector2d& mousepos, ScreenElement* element);
		virtual void handleMouseDisconnect(const ApplicationData& appData, unsigned int mouseIndex);
		
		virtual ScreenElement* handleTouchMove(const ApplicationData& appData, unsigned int touchID, const Vector2d& touchpos);
		virtual void elementHandledTouchMove(const ApplicationData& appData, unsigned int touchID, const Vector2d& touchpos, ScreenElement* element);
		virtual ScreenElement* handleTouchBegin(const ApplicationData& appData, unsigned int touchID, const Vector2d& touchpos);
		virtual void elementHandledTouchBegin(const ApplicationData& appData, unsigned int touchID, const Vector2d& touchpos, ScreenElement* element);
		virtual ScreenElement* handleTouchEnd(const ApplicationData& appData, unsigned int touchID, const Vector2d& touchpos);
		virtual void elementHandledTouchEnd(const ApplicationData& appData, unsigned int touchID, const Vector2d& touchpos, ScreenElement* element);
	};
}
