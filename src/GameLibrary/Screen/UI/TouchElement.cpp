
#include "TouchElement.h"

namespace GameLibrary
{
	TouchElementEvent::TouchElementEvent(TouchElement* target, const ApplicationData& appData, unsigned int touchID, const Vector2d& pos, bool mouse)
		: target(target), appData(appData), touchID(touchID), pos(pos), mouse(mouse) {}
	
	TouchElement* TouchElementEvent::getTarget() const { return target; }
	const ApplicationData& TouchElementEvent::getApplicationData() const { return appData; }
	unsigned int TouchElementEvent::getTouchID() const { return touchID; }
	const Vector2d& TouchElementEvent::getPosition() const { return pos; }
	bool TouchElementEvent::isMouseEvent() const { return mouse; }
	
	TouchElement::TouchElement() : TouchElement(RectangleD(0, 0, 0, 0))
	{
		//
	}
	
	TouchElement::TouchElement(const RectangleD& frame) : ScreenElement(frame),
		touchEnabled(true)
	{
		//
	}
	
	void TouchElement::update(ApplicationData appData)
	{
		ScreenElement::update(appData);
		if(!isVisibleInHeirarchy())
		{
			for(size_t i=(touches.size()-1); i!=SIZE_MAX; i--)
			{
				TouchData& touchData = touches[i];
				cancelTouch(appData, touchData.touchID, touchData.pos, touchData.mouse);
			}
		}
	}
	
	void TouchElement::onMouseEnter(const TouchElementEvent& evt) {}
	void TouchElement::onMouseLeave(const TouchElementEvent& evt) {}
	void TouchElement::onTouchCancel(const TouchElementEvent& evt) {}
	void TouchElement::onTouchDown(const TouchElementEvent& evt) {}
	void TouchElement::onTouchUpInside(const TouchElementEvent& evt) {}
	void TouchElement::onTouchUpOutside(const TouchElementEvent& evt) {}
	void TouchElement::onTouchMoveInside(const TouchElementEvent& evt) {}
	void TouchElement::onTouchMoveOutside(const TouchElementEvent& evt) {}
	
	bool TouchElement::checkPointCollision(const Vector2d& point)
	{
		if(isVisibleInHeirarchy())
		{
			RectangleD frame = getFrame();
			if(frame.contains(point))
			{
				return true;
			}
		}
		return false;
	}
	
	void TouchElement::setTouchEnabled(bool toggle)
	{
		touchEnabled = toggle;
	}
	
	bool TouchElement::isTouchEnabled() const
	{
		return touchEnabled;
	}
	
	
	TouchElement::TouchData* TouchElement::getTouch(unsigned int touchID)
	{
		for(size_t touches_size=touches.size(), i=0; i<touches_size; i++)
		{
			TouchData& touch = touches[i];
			if(touch.touchID==touchID)
			{
				return &touch;
			}
		}
		return nullptr;
	}
	
	TouchElement::TouchData* TouchElement::addTouch(unsigned int touchID, const Vector2d& pos, bool inside, bool pressedInside, bool mouse)
	{
		for(size_t touches_size=touches.size(), i=0; i<touches_size; i++)
		{
			TouchData& touchData = touches[i];
			if(touchData.touchID==touchID)
			{
				touchData.touchID = touchID;
				touchData.pos = pos;
				touchData.inside = inside;
				touchData.pressedInside = pressedInside;
				touchData.mouse = mouse;
				return &touchData;
			}
		}
		TouchData touchData;
		touchData.touchID = touchID;
		touchData.pos = pos;
		touchData.inside = inside;
		touchData.pressedInside = pressedInside;
		touchData.mouse = mouse;
		touches.add(touchData);
		return &touches[touches.size()-1];
	}
	
	void TouchElement::removeTouch(unsigned int touchID)
	{
		for(size_t touches_size=touches.size(), i=0; i<touches_size; i++)
		{
			if(touches[i].touchID==touchID)
			{
				touches.remove(i);
				return;
			}
		}
	}
	
	void TouchElement::cancelTouch(const ApplicationData& appData, unsigned int touchID, const Vector2d& touchpos, bool mouse)
	{
		TouchData* touchData = getTouch(touchID);
		if(touchData!=nullptr)
		{
			if(touchData->pressedInside)
			{
				if(mouse)
				{
					if(touchData->inside)
					{
						onMouseLeave(TouchElementEvent(this, appData, touchID, touchpos, mouse));
					}
				}
				onTouchCancel(TouchElementEvent(this, appData, touchID, touchpos, mouse));
			}
			else
			{
				if(mouse)
				{
					if(touchData->inside)
					{
						onMouseLeave(TouchElementEvent(this, appData, touchID, touchpos, mouse));
					}
				}
			}
			removeTouch(touchID);
		}
	}
	
	
	
	ScreenElement* TouchElement::handleMouseMove(const ApplicationData& appData, unsigned int mouseIndex, const Vector2d& mousepos)
	{
		TouchData* touchData = getTouch(mouseIndex);
		if(touchData==nullptr)
		{
			ScreenElement* handler = tellChildrenHandleMouseMove(appData, mouseIndex, mousepos);
			if(handler!=nullptr)
			{
				return handler;
			}
			else if(checkPointCollision(mousepos))
			{
				touchData = addTouch(mouseIndex, mousepos, true, false, true);
				onMouseEnter(TouchElementEvent(this, appData, mouseIndex, mousepos, true));
				return this;
			}
			return nullptr;
		}
		else if(touchData->pressedInside)
		{
			if(checkPointCollision(mousepos))
			{
				bool wasinside = touchData->inside;
				touchData->pos = mousepos;
				touchData->inside = true;
				if(!wasinside)
				{
					onMouseEnter(TouchElementEvent(this, appData, mouseIndex, mousepos, true));
				}
				onTouchMoveInside(TouchElementEvent(this, appData, mouseIndex, mousepos, true));
			}
			else
			{
				bool wasinside = touchData->inside;
				touchData->pos = mousepos;
				touchData->inside = false;
				if(wasinside)
				{
					onMouseLeave(TouchElementEvent(this, appData, mouseIndex, mousepos, true));
				}
				onTouchMoveOutside(TouchElementEvent(this, appData, mouseIndex, mousepos, true));
			}
			tellChildrenElementHandledMouseMove(appData, mouseIndex, mousepos, this);
			return this;
		}
		else if(!checkPointCollision(mousepos))
		{
			removeTouch(mouseIndex);
			onMouseLeave(TouchElementEvent(this, appData, mouseIndex, mousepos, true));
		}
		ScreenElement* handler = tellChildrenHandleMouseMove(appData, mouseIndex, mousepos);
		if(handler!=nullptr && touchData->inside)
		{
			cancelTouch(appData, mouseIndex, mousepos, true);
		}
		return handler;
	}
	
	void TouchElement::elementHandledMouseMove(const ApplicationData& appData, unsigned int mouseIndex, const Vector2d& mousepos, ScreenElement* element)
	{
		tellChildrenElementHandledMouseMove(appData, mouseIndex, mousepos, element);
		cancelTouch(appData, mouseIndex, mousepos, true);
	}
	
	ScreenElement* TouchElement::handleMousePress(const ApplicationData& appData, unsigned int mouseIndex, Mouse::Button button, const Vector2d& mousepos)
	{
		TouchData* touchData = getTouch(mouseIndex);
		if(touchData==nullptr)
		{
			ScreenElement* handler = tellChildrenHandleMousePress(appData, mouseIndex, button, mousepos);
			if(handler!=nullptr)
			{
				return handler;
			}
			else if(checkPointCollision(mousepos))
			{
				touchData = addTouch(mouseIndex, mousepos, true, true, true);
				onMouseEnter(TouchElementEvent(this, appData, mouseIndex, mousepos, true));
				onTouchDown(TouchElementEvent(this, appData, mouseIndex, mousepos, true));
				return this;
			}
			return nullptr;
		}
		else if(button==Mouse::BUTTON_LEFT && checkPointCollision(mousepos))
		{
			touchData->pressedInside = true;
			touchData->pos = mousepos;
			onTouchDown(TouchElementEvent(this, appData, mouseIndex, mousepos, true));
			tellChildrenElementHandledMousePress(appData, mouseIndex, button, mousepos, this);
			return this;
		}
		ScreenElement* handler = tellChildrenHandleMousePress(appData, mouseIndex, button, mousepos);
		if(handler!=nullptr && touchData->inside)
		{
			cancelTouch(appData, mouseIndex, mousepos, true);
		}
		return handler;
	}
	
	void TouchElement::elementHandledMousePress(const ApplicationData& appData, unsigned int mouseIndex, Mouse::Button button, const Vector2d& mousepos, ScreenElement* element)
	{
		tellChildrenElementHandledMousePress(appData, mouseIndex, button, mousepos, element);
		cancelTouch(appData, mouseIndex, mousepos, true);
	}
	
	ScreenElement* TouchElement::handleMouseRelease(const ApplicationData& appData, unsigned int mouseIndex, Mouse::Button button, const Vector2d& mousepos)
	{
		TouchData* touchData = getTouch(mouseIndex);
		if(touchData==nullptr)
		{
			return tellChildrenHandleMouseRelease(appData, mouseIndex, button, mousepos);
		}
		else if(touchData->pressedInside)
		{
			touchData->pressedInside = false;
			touchData->pos = mousepos;
			if(touchData->inside)
			{
				onTouchUpInside(TouchElementEvent(this, appData, mouseIndex, mousepos, true));
			}
			else
			{
				onTouchUpOutside(TouchElementEvent(this, appData, mouseIndex, mousepos, true));
			}
			removeTouch(mouseIndex);
			tellChildrenElementHandledMouseRelease(appData, mouseIndex, button, mousepos, this);
			return this;
		}
		ScreenElement* handler = tellChildrenHandleMouseRelease(appData, mouseIndex, button, mousepos);
		if(handler!=nullptr && touchData->inside)
		{
			cancelTouch(appData, mouseIndex, mousepos, true);
		}
		return handler;
	}
	
	void TouchElement::elementHandledMouseRelease(const ApplicationData& appData, unsigned int mouseIndex, Mouse::Button button, const Vector2d& mousepos, ScreenElement* element)
	{
		tellChildrenElementHandledMouseRelease(appData, mouseIndex, button, mousepos, element);
		cancelTouch(appData, mouseIndex, mousepos, true);
	}
	
	void TouchElement::handleMouseDisconnect(const ApplicationData& appData, unsigned int mouseIndex)
	{
		tellChildrenHandleMouseDisconnect(appData, mouseIndex);
		TouchData* touchData = getTouch(mouseIndex);
		if(touchData!=nullptr)
		{
			cancelTouch(appData, mouseIndex, touchData->pos, true);
		}
	}
	
	
	
	ScreenElement* TouchElement::handleTouchMove(const ApplicationData& appData, unsigned int touchID, const Vector2d& touchpos)
	{
		TouchData* touchData = getTouch(touchID);
		if(touchData==nullptr)
		{
			return tellChildrenHandleTouchMove(appData, touchID, touchpos);
		}
		else if(touchData->pressedInside)
		{
			if(checkPointCollision(touchpos))
			{
				touchData->pos = touchpos;
				touchData->inside = true;
				onTouchMoveInside(TouchElementEvent(this, appData, touchID, touchpos, false));
			}
			else
			{
				touchData->pos = touchpos;
				touchData->inside = false;
				onTouchMoveOutside(TouchElementEvent(this, appData, touchID, touchpos, false));
			}
			tellChildrenElementHandledTouchMove(appData, touchID, touchpos, this);
			return this;
		}
		else if(!checkPointCollision(touchpos))
		{
			removeTouch(touchID);
		}
		ScreenElement* handler = tellChildrenHandleMouseMove(appData, touchID, touchpos);
		if(handler!=nullptr && touchData->inside)
		{
			cancelTouch(appData, touchID, touchpos, false);
		}
		return handler;
	}
	
	void TouchElement::elementHandledTouchMove(const ApplicationData& appData, unsigned int touchID, const Vector2d& touchpos, ScreenElement* element)
	{
		tellChildrenElementHandledTouchMove(appData, touchID, touchpos, element);
		cancelTouch(appData, touchID, touchpos, false);
	}
	
	ScreenElement* TouchElement::handleTouchBegin(const ApplicationData& appData, unsigned int touchID, const Vector2d& touchpos)
	{
		ScreenElement* handler = tellChildrenHandleTouchBegin(appData, touchID, touchpos);
		if(handler!=nullptr)
		{
			removeTouch(touchID);
			return handler;
		}
		else if(checkPointCollision(touchpos))
		{
			TouchData* touchData = addTouch(touchID, touchpos, true, true, false);
			onTouchDown(TouchElementEvent(this, appData, touchID, touchpos, false));
			return this;
		}
		return nullptr;
	}
	
	void TouchElement::elementHandledTouchBegin(const ApplicationData& appData, unsigned int touchID, const Vector2d& touchpos, ScreenElement* element)
	{
		tellChildrenElementHandledTouchBegin(appData, touchID, touchpos, element);
		cancelTouch(appData, touchID, touchpos, false);
	}
	
	ScreenElement* TouchElement::handleTouchEnd(const ApplicationData& appData, unsigned int touchID, const Vector2d& touchpos)
	{
		TouchData* touchData = getTouch(touchID);
		if(touchData==nullptr)
		{
			return tellChildrenHandleTouchEnd(appData, touchID, touchpos);
		}
		else if(touchData->pressedInside)
		{
			if(checkPointCollision(touchpos))
			{
				touchData->pos = touchpos;
				touchData->inside = true;
				onTouchUpInside(TouchElementEvent(this, appData, touchID, touchpos, false));
			}
			else
			{
				touchData->pos = touchpos;
				touchData->inside = false;
				onTouchUpOutside(TouchElementEvent(this, appData, touchID, touchpos, false));
			}
			tellChildrenElementHandledTouchEnd(appData, touchID, touchpos, this);
			removeTouch(touchID);
			return this;
		}
		else
		{
			removeTouch(touchID);
		}
		return tellChildrenHandleTouchEnd(appData, touchID, touchpos);
	}
	
	void TouchElement::elementHandledTouchEnd(const ApplicationData& appData, unsigned int touchID, const Vector2d& touchpos, ScreenElement* element)
	{
		tellChildrenElementHandledTouchEnd(appData, touchID, touchpos, element);
		cancelTouch(appData, touchID, touchpos, false);
	}
}
