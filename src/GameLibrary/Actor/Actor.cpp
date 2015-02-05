
#include "Actor.h"
#include "../Input/Mouse.h"
#include "../Input/Multitouch.h"
#include "../Utilities/PlatformChecks.h"

namespace GameLibrary
{
	Actor::Actor()
	{
		x = 0;
		y = 0;
		width = 0;
		height = 0;
		
		clicked = false;
		prevclicked = false;
		mouseover = false;
		prevmouseover = false;
		didpress = false;
		didrelease = false;
		visible = true;
		mirroredHorizontal = false;
		mirroredVertical = false;
		frame_visible = false;
		color = Color::WHITE;
		frame_color = Color::GREEN;
		rotation = 0;
		alpha = 1;
		scale = 1;
	}
	
	Actor::~Actor()
	{
		//
	}
	
	void Actor::update(ApplicationData appData)
	{
		didpress = false;
		didrelease = false;
		prevclicked = clicked;
		prevmouseover = mouseover;

		if(Multitouch::isEnabled())
		{
			updateTouch(appData);
		}
		else
		{
			updateMouse(appData);
		}
	}
	
	void Actor::draw(ApplicationData appData, Graphics graphics) const
	{
		//Open for implementation
	}
	
	RectangleF Actor::getFrame() const
	{
		return RectangleF(x, y, width, height);
	}
	
	void Actor::scaleToFit(const RectangleF&container)
	{
		if(width == 0 || height == 0)
		{
			x = container.x + (container.width/2);
			y = container.y + (container.height/2);
			return;
		}
		RectangleF currentFrame = getFrame();
		RectangleF oldFrame = currentFrame;
		currentFrame.scaleToFit(container);
		float ratio = currentFrame.width/oldFrame.width;
		setScale(getScale()*ratio);
		RectangleF newFrame = getFrame();
		x = container.x + ((container.width-newFrame.width)/2);
		y = container.y + ((container.height-newFrame.height)/2);
	}
	
	void Actor::scaleToFit(const Vector2f& size)
	{
		if(width == 0 || height == 0)
		{
			return;
		}
		RectangleF container(0,0,size.x,size.y);
		RectangleF currentFrame = getFrame();
		RectangleF oldFrame = currentFrame;
		currentFrame.scaleToFit(container);
		float ratio = currentFrame.width/oldFrame.width;
		setScale(getScale()*ratio);
	}
	
	float Actor::getWidth() const
	{
		return width;
	}
	
	float Actor::getHeight() const
	{
		return height;
	}
	
	void Actor::setVisible(bool toggle)
	{
		visible = toggle;
	}
	
	void Actor::setColor(const Color&c)
	{
		color = c;
	}
	
	void Actor::rotate(float degrees)
	{
		if(degrees!=0)
		{
			rotation += degrees;
			rotationMatrix.rotate(degrees,0,0);
			inverseRotationMatrix = rotationMatrix.getInverse();
			updateSize();
		}
	}
	
	void Actor::setRotation(float degrees)
	{
		if(degrees!=rotation)
		{
			rotation = degrees;
			rotationMatrix.reset();
			if(degrees!=0)
			{
				rotationMatrix.rotate(degrees,0,0);
			}
			inverseRotationMatrix = rotationMatrix.getInverse();
			updateSize();
		}
	}
	
	void Actor::setAlpha(float a)
	{
		alpha = a;
	}
	
	void Actor::setScale(float s)
	{
		scale = s;
		updateSize();
	}

	void Actor::setFrameVisible(bool toggle)
	{
		frame_visible = toggle;
	}
	
	void Actor::setFrameColor(const Color&color)
	{
		frame_color = color;
	}
	
	void Actor::setMirroredHorizontal(bool toggle)
	{
		mirroredHorizontal = toggle;
		updateSize();
	}
	
	void Actor::setMirroredVertical(bool toggle)
	{
		mirroredVertical = toggle;
		updateSize();
	}
	
	bool Actor::isVisible() const
	{
		return visible;
	}
	
	const Color& Actor::getColor() const
	{
		return color;
	}
	
	float Actor::getRotation() const
	{
		return rotation;
	}
	
	float Actor::getAlpha() const
	{
		return alpha;
	}
	
	float Actor::getScale() const
	{
		return scale;
	}

	bool Actor::isFrameVisible() const
	{
		return frame_visible;
	}
	
	const Color& Actor::getFrameColor() const
	{
		return frame_color;
	}
	
	bool Actor::isMirroredHorizontal() const
	{
		return mirroredHorizontal;
	}
	
	bool Actor::isMirroredVertical() const
	{
		return mirroredVertical;
	}
	
	bool Actor::isMouseOver() const
	{
		return mouseover;
	}
	
	bool Actor::wasMouseOver() const
	{
		return prevmouseover;
	}
	
	bool Actor::isMousePressed() const
	{
		return clicked;
	}
	
	bool Actor::wasMousePressed() const
	{
		return prevclicked;
	}
	
	bool Actor::didMousePress() const
	{
		return didpress;
	}

	bool Actor::didMouseRelease() const
	{
		return didrelease;
	}

	void Actor::clearMouseState()
	{
		currentTouches.clear();
	}
	
	void Actor::updateSize()
	{
		width = 0;
		height = 0;
	}

	bool Actor::checkPointCollision(const Vector2f&point)
	{
		return false;
	}
	
	void Actor::onMousePress(ApplicationData appData, unsigned int touchID)
	{
		//Open for implementation
	}

	void Actor::onMouseRelease(ApplicationData appData, unsigned int touchID)
	{
		//Open for implementation
	}

	void Actor::onMouseEnter(ApplicationData appData, unsigned int touchID)
	{
		//Open for implementation
	}

	void Actor::onMouseLeave(ApplicationData appData, unsigned int touchID)
	{
		//Open for implementation
	}

	bool Actor::isTouchDataActive(unsigned int touchID)
	{
		for(unsigned int i=0; i<currentTouches.size(); i++)
		{
			if(currentTouches.get(i).touchID == touchID)
			{
				return true;
			}
		}
		return false;
	}

	bool Actor::isTouchDataPressed(unsigned int touchID)
	{
		for(unsigned int i=0; i<currentTouches.size(); i++)
		{
			MouseTouchData& touchData = currentTouches.get(i);
			if(touchData.touchID == touchID)
			{
				return touchData.pressed;
			}
		}
		return false;
	}

	void Actor::applyTouchData(unsigned int touchID, bool pressed)
	{
		for(unsigned int i=0; i<currentTouches.size(); i++)
		{
			MouseTouchData& touchData = currentTouches.get(i);
			if(touchData.touchID == touchID)
			{
				touchData.pressed = pressed;
				return;
			}
		}
		MouseTouchData touchData;
		touchData.touchID = touchID;
		touchData.pressed = pressed;
		currentTouches.add(touchData);
	}

	void Actor::removeTouchData(unsigned int touchID)
	{
		for(unsigned int i=0; i<currentTouches.size(); i++)
		{
			MouseTouchData& touchData = currentTouches.get(i);
			if(touchData.touchID == touchID)
			{
				currentTouches.remove(i);
				return;
			}
		}
	}

	Actor::MouseTouchData* Actor::getTouchData(unsigned int touchID)
	{
		for(unsigned int i=0; i<currentTouches.size(); i++)
		{
			MouseTouchData& touchData = currentTouches.get(i);
			if(touchData.touchID == touchID)
			{
				return &touchData;
			}
		}
		return nullptr;
	}

	ArrayList<unsigned int> Actor::getDifTouchData(const ArrayList<unsigned int>& touchIDs)
	{
		ArrayList<unsigned int> unlisted;
		for(unsigned int i=0; i<currentTouches.size(); i++)
		{
			MouseTouchData& touchData = currentTouches.get(i);
			bool found = false;
			for(unsigned j=0; j<touchIDs.size(); j++)
			{
				if(touchIDs.get(i) == touchData.touchID)
				{
					found = true;
					j = touchIDs.size();
				}
			}
			
			if(!found)
			{
				unlisted.add(touchData.touchID);
			}
		}
		return unlisted;
	}
	
	#define EVENTCALL_MOUSEENTER 1
	#define EVENTCALL_MOUSELEAVE 2
	#define EVENTCALL_MOUSEPRESS 3
	#define EVENTCALL_MOUSERELEASE 4
	
	void Actor::updateMouse(ApplicationData&appData)
	{
		Window* window = appData.getWindow();
		Transform mouseTransform = appData.getTransform().getInverse();
		
		mouseover = false;
		clicked = false;
		ArrayList<Pair<unsigned int,byte> > mouseEventCalls;
		
		ArrayList<unsigned int> touchIDs;
		unsigned int mouseInstances = Mouse::getTotalMouseInstances(window);
		for(unsigned int i=0; i<mouseInstances; i++)
		{
			touchIDs.add(i);
		}

		ArrayList<unsigned int> unlistedIDs = getDifTouchData(touchIDs);
		for(unsigned int i = 0; i < unlistedIDs.size(); i++)
		{
			unsigned int touchID = unlistedIDs.get(i);
			MouseTouchData* touchData = getTouchData(touchID);
			if(touchData != nullptr)
			{
				removeTouchData(touchID);
				mouseEventCalls.add(Pair<unsigned int, byte>(touchID, EVENTCALL_MOUSERELEASE));
			}
		}

		for(unsigned int i=0; i<touchIDs.size(); i++)
		{
			unsigned int touchID = touchIDs.get(i);
			Vector2f mousepos = Mouse::getPosition(window, touchID);
			Vector2f transformedPos = mouseTransform.transform(mousepos);
			if(checkPointCollision(transformedPos))
			{
				mouseover = true;
				if(isTouchDataPressed(touchID))
				{
					if(Mouse::isButtonPressed(window, touchID, Mouse::BUTTON_LEFT))
					{
						applyTouchData(touchID, true);
						clicked = true;
					}
					else
					{
						applyTouchData(touchID, false);
						mouseEventCalls.add(Pair<unsigned int, byte>(touchID, EVENTCALL_MOUSERELEASE));
					}
				}
				else if(isTouchDataActive(touchID))
				{
					if(Mouse::isButtonPressed(window, touchID, Mouse::BUTTON_LEFT))
					{
						applyTouchData(touchID, true);
						clicked = true;
						if(!Mouse::wasButtonPressed(window, touchID, Mouse::BUTTON_LEFT))
						{
							mouseEventCalls.add(Pair<unsigned int, byte>(touchID, EVENTCALL_MOUSEPRESS));
						}
					}
					else
					{
						applyTouchData(touchID, false);
						if(Mouse::wasButtonPressed(window, touchID, Mouse::BUTTON_LEFT))
						{
							mouseEventCalls.add(Pair<unsigned int, byte>(touchID, EVENTCALL_MOUSERELEASE));
						}
					}
				}
				else
				{
					mouseEventCalls.add(Pair<unsigned int, byte>(touchID, EVENTCALL_MOUSEENTER));
					if(Mouse::isButtonPressed(window, touchID, Mouse::BUTTON_LEFT) && !Mouse::wasButtonPressed(window, touchID, Mouse::BUTTON_LEFT))
					{
						applyTouchData(touchID, true);
						clicked = true;
						mouseEventCalls.add(Pair<unsigned int, byte>(touchID, EVENTCALL_MOUSEPRESS));
					}
					else
					{
						applyTouchData(touchID, false);
					}
				}
			}
			else
			{
				if(isTouchDataPressed(touchID))
				{
					mouseEventCalls.add(Pair<unsigned int, byte>(touchID, EVENTCALL_MOUSELEAVE));
					if(!Mouse::isButtonPressed(window, touchID, Mouse::BUTTON_LEFT))
					{
						mouseEventCalls.add(Pair<unsigned int, byte>(touchID, EVENTCALL_MOUSERELEASE));
					}
				}
				else if(isTouchDataActive(touchID))
				{
					mouseEventCalls.add(Pair<unsigned int, byte>(touchID, EVENTCALL_MOUSELEAVE));
				}
				removeTouchData(touchID);
			}
		}

		callMouseEvents(appData, mouseEventCalls);
	}
	
	void Actor::updateTouch(ApplicationData&appData)
	{
		Window* window = appData.getWindow();
		Transform mouseTransform = appData.getTransform().getInverse();
		
		mouseover = false;
		clicked = false;
		ArrayList<Pair<unsigned int,byte> > mouseEventCalls;
		
		ArrayList<unsigned int> touchIDs = Multitouch::getTouchIDs(window);
		
		ArrayList<unsigned int> unlistedIDs = getDifTouchData(touchIDs);
		for(unsigned int i = 0; i < unlistedIDs.size(); i++)
		{
			unsigned int touchID = unlistedIDs.get(i);
			MouseTouchData* touchData = getTouchData(touchID);
			if(touchData != nullptr)
			{
				removeTouchData(touchID);
				mouseEventCalls.add(Pair<unsigned int, byte>(touchID, EVENTCALL_MOUSERELEASE));
			}
		}
		
		for(unsigned int i=0; i<touchIDs.size(); i++)
		{
			unsigned int touchID = touchIDs.get(i);
			Vector2f touchpos = Multitouch::getPosition(window, touchID);
			Vector2f transformedPos = mouseTransform.transform(touchpos);
			if(checkPointCollision(transformedPos))
			{
				mouseover = true;
				if(isTouchDataActive(touchID))
				{
					applyTouchData(touchID, true);
					clicked = true;
				}
				else
				{
					if(!Multitouch::wasTouchActive(window, touchID))
					{
						applyTouchData(touchID, true);
						clicked = true;
						mouseEventCalls.add(Pair<unsigned int, byte>(touchID, EVENTCALL_MOUSEPRESS));
					}
					else
					{
						applyTouchData(touchID, true);
						clicked = true;
						mouseEventCalls.add(Pair<unsigned int, byte>(touchID, EVENTCALL_MOUSEENTER));
					}
				}
			}
			else
			{
				if(isTouchDataActive(touchID))
				{
					applyTouchData(touchID, false);
					mouseEventCalls.add(Pair<unsigned int, byte>(touchID, EVENTCALL_MOUSELEAVE));
				}
				else
				{
					//applyTouchData(touchID, false);
				}
				removeTouchData(touchID);
			}
		}
		
		callMouseEvents(appData, mouseEventCalls);
	}

	void Actor::callMouseEvents(ApplicationData&appData, const ArrayList<Pair<unsigned int, byte> >& eventCallData)
	{
		bool didmousepress = false;
		bool didmouserelease = false;
		for(unsigned int i=0; i<eventCallData.size(); i++)
		{
			const Pair<unsigned int, byte>& eventData = eventCallData.get(i);
			switch(eventData.second)
			{
				case EVENTCALL_MOUSEENTER:
				onMouseEnter(appData, eventData.first);
				break;

				case EVENTCALL_MOUSELEAVE:
				onMouseLeave(appData, eventData.first);
				break;

				case EVENTCALL_MOUSEPRESS:
				didmousepress = true;
				onMousePress(appData, eventData.first);
				break;

				case EVENTCALL_MOUSERELEASE:
				didmouserelease = true;
				onMouseRelease(appData, eventData.first);
				break;
			}
		}
		
		didpress = didmousepress;
		didrelease = didmouserelease;
		
		/*unsigned int pressedTouches = 0;
		for(unsigned int i=0; i<currentTouches.size(); i++)
		{
			if(currentTouches.get(i).pressed)
			{
				pressedTouches++;
			}
		}
		if(pressedTouches == 0)
		{
			didpress = false;
		}
		else
		{
			didrelease = false;
		}*/
	}
	
	#undef EVENTCALL_MOUSEENTER
	#undef EVENTCALL_MOUSELEAVE
	#undef EVENTCALL_MOUSEPRESS
	#undef EVENTCALL_MOUSERELEASE
}