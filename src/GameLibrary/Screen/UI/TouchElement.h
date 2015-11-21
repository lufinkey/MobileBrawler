
#pragma once

#include "../ScreenElement.h"

namespace GameLibrary
{
	class TouchElement;
	
	class TouchElementEvent
	{
	public:
		/*! Constructs a TouchElementEvent object*/
		TouchElementEvent(TouchElement* target, const ApplicationData& appData, unsigned int touchID, const Vector2d& pos, bool mouse);
		
		/*! Gives the target of the mouse event. The target is the ScreenElement which the event was performed on.
		\returns a ScreenElement pointer*/
		TouchElement* getTarget() const;
		/*! Gives information about the Application updating the ScreenElement, such as the Window object, the View transform, etc. \see GameLibrary::ApplicationData
		\returns a const ApplicationData object reference*/
		const ApplicationData& getApplicationData() const;
		/*! Gives the touchID or mouseIndex of the input. If Multitouch::isAvailable() returns true, touchID represents a multitouch id. Otherwise, touchID represents a mouse index. \see GameLibrary::Mouse \see GameLibrary::Multitouch
		\returns an unsigned int representing an index or id*/
		unsigned int getTouchID() const;
		/*! Gives the position of the touch or mouse pointer (if applicable), which is relative to the element's parent's frame ([0,0] is the same as [parentFrame.x, parentFrame.y])
			\returns a 2 dimensional vector with the x and y coordinates*/
		const Vector2d& getPosition() const;
		/*! Tells whether this event is a Mouse event or a Multitouch event
		\returns true if Multitouch event, false if Mouse event*/
		bool isMouseEvent() const;

	private:
		TouchElement* target;
		ApplicationData appData;
		unsigned int touchID;
		Vector2d pos;
		//TODO add support for button attribute, representing the button changed during this event
		bool mouse;
	};
	
	class TouchElement : public ScreenElement
	{
	public:
		/*! default constructor*/
		TouchElement();
		/*! \copydoc GameLibrary::ScreenElement::ScreenElement(const RectangleD&frame)*/
		explicit TouchElement(const RectangleD&frame);
		
		virtual void onMouseEnter(const TouchElementEvent& evt);
		virtual void onMouseLeave(const TouchElementEvent& evt);
		
		virtual void onTouchCancel(const TouchElementEvent& evt);
		
		virtual void onTouchDown(const TouchElementEvent& evt);
		virtual void onTouchUpInside(const TouchElementEvent& evt);
		virtual void onTouchUpOutside(const TouchElementEvent& evt);
		
		virtual void onTouchMoveInside(const TouchElementEvent& evt);
		virtual void onTouchMoveOutside(const TouchElementEvent& evt);
		
		virtual bool checkPointCollision(const Vector2d& point);
		
		void setTouchEnabled(bool toggle);
		bool isTouchEnabled() const;
		
	private:
		virtual ScreenElement* handleMouseMove(const ApplicationData& appData, unsigned int mouseIndex, const Vector2d& mousepos) override;
		virtual void elementHandledMouseMove(const ApplicationData& appData, unsigned int mouseIndex, const Vector2d& mousepos, ScreenElement* element) override;
		virtual ScreenElement* handleMousePress(const ApplicationData& appData, unsigned int mouseIndex, Mouse::Button button, const Vector2d& mousepos) override;
		virtual void elementHandledMousePress(const ApplicationData& appData, unsigned int mouseIndex, Mouse::Button button, const Vector2d& mousepos, ScreenElement* element) override;
		virtual ScreenElement* handleMouseRelease(const ApplicationData& appData, unsigned int mouseIndex, Mouse::Button button, const Vector2d& mousepos) override;
		virtual void elementHandledMouseRelease(const ApplicationData& appData, unsigned int mouseIndex, Mouse::Button button, const Vector2d& mousepos, ScreenElement* element) override;
		virtual void handleMouseDisconnect(const ApplicationData& appData, unsigned int mouseIndex) override;
		
		virtual ScreenElement* handleTouchMove(const ApplicationData& appData, unsigned int touchID, const Vector2d& touchpos) override;
		virtual void elementHandledTouchMove(const ApplicationData& appData, unsigned int touchID, const Vector2d& touchpos, ScreenElement* element) override;
		virtual ScreenElement* handleTouchBegin(const ApplicationData& appData, unsigned int touchID, const Vector2d& touchpos) override;
		virtual void elementHandledTouchBegin(const ApplicationData& appData, unsigned int touchID, const Vector2d& touchpos, ScreenElement* element) override;
		virtual ScreenElement* handleTouchEnd(const ApplicationData& appData, unsigned int touchID, const Vector2d& touchpos) override;
		virtual void elementHandledTouchEnd(const ApplicationData& appData, unsigned int touchID, const Vector2d& touchpos, ScreenElement* element) override;
		
		bool touchEnabled;
		
		typedef struct
		{
			unsigned int touchID;
			bool inside;
			bool pressedInside;
			Vector2d pos;
		} TouchData;
		ArrayList<TouchData> touches;
		
		TouchData* getTouch(unsigned int touchID);
		TouchData* addTouch(unsigned int touchID, bool inside, bool pressedInside, const Vector2d& pos);
		void removeTouch(unsigned int touchID);
		void cancelTouch(const ApplicationData& appData, unsigned int touchID, const Vector2d& touchpos, bool mouse);
	};
}
