
#include "BaseActor.h"
#include "../Input/Mouse.h"
#include "../Input/Multitouch.h"
#include "../Utilities/PlatformChecks.h"

namespace GameLibrary
{
	BaseActor::BaseActor()
	{
		actorType = ACTORTYPE_BASE;
		x = 0;
		y = 0;
		width = 0;
		height = 0;
		
		clicked = false;
		prevclicked = false;
		mouseover = false;
		prevmouseover = false;
		visible = true;
		mirrored = false;
		mirroredVertical = false;
		frame_visible = false;
		color = Color::WHITE;
		frame_color = Color::GREEN;
		rotation = 0;
		alpha = 1;
		scale = 1;
	}
	
	BaseActor::~BaseActor()
	{
		//
	}
	
	void BaseActor::update(ApplicationData appData)
	{
		prevclicked = clicked;
		prevmouseover = mouseover;
		
		#if defined(TARGETPLATFORM_MOBILE)
			updateTouch(appData);
		#else
			updateMouse(appData);
		#endif
	}
	
	void BaseActor::draw(ApplicationData appData, Graphics graphics) const
	{
		//Open for implementation
	}
	
	RectangleF BaseActor::getFrame() const
	{
		return RectangleF(x, y, width, height);
	}
	
	BaseActor::ActorType BaseActor::getActorType() const
	{
		return actorType;
	}
	
	float BaseActor::getWidth() const
	{
		return width;
	}
	
	float BaseActor::getHeight() const
	{
		return height;
	}
	
	void BaseActor::setVisible(bool toggle)
	{
		visible = toggle;
	}
	
	void BaseActor::setColor(const Color&c)
	{
		color = c;
	}
	
	void BaseActor::rotate(float degrees)
	{
		if(degrees!=0)
		{
			rotation += degrees;
			rotationMatrix.rotate(degrees,0,0);
			inverseRotationMatrix = rotationMatrix.getInverse();
			updateSize();
		}
	}
	
	void BaseActor::setRotation(float degrees)
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
	
	void BaseActor::setAlpha(float a)
	{
		alpha = a;
	}
	
	void BaseActor::setScale(float s)
	{
		scale = s;
		updateSize();
	}

	void BaseActor::setFrameVisible(bool toggle)
	{
		frame_visible = toggle;
	}
	
	void BaseActor::setFrameColor(const Color&color)
	{
		frame_color = color;
	}
	
	void BaseActor::setMirrored(bool toggle)
	{
		mirrored = toggle;
		updateSize();
	}
	
	void BaseActor::setMirroredVertical(bool toggle)
	{
		mirroredVertical = toggle;
		updateSize();
	}
	
	bool BaseActor::isVisible() const
	{
		return visible;
	}
	
	const Color& BaseActor::getColor() const
	{
		return color;
	}
	
	float BaseActor::getRotation() const
	{
		return rotation;
	}
	
	float BaseActor::getAlpha() const
	{
		return alpha;
	}
	
	float BaseActor::getScale() const
	{
		return scale;
	}

	bool BaseActor::isFrameVisible() const
	{
		return frame_visible;
	}
	
	const Color& BaseActor::getFrameColor() const
	{
		return frame_color;
	}
	
	bool BaseActor::isMirrored() const
	{
		return mirrored;
	}
	
	bool BaseActor::isMirroredVertical() const
	{
		return mirroredVertical;
	}
	
	bool BaseActor::isOnScreen(View*view) const
	{
		return true;
	}
	
	bool BaseActor::isMouseOver() const
	{
		return mouseover;
	}
	
	bool BaseActor::wasMouseOver() const
	{
		return prevmouseover;
	}
	
	bool BaseActor::isMousePressed() const
	{
		return clicked;
	}
	
	bool BaseActor::wasMousePressed() const
	{
		return prevclicked;
	}
	
	void BaseActor::updateSize()
	{
		width = 0;
		height = 0;
	}

	bool BaseActor::checkPointCollision(const Vector2f&point)
	{
		return false;
	}
	
	void BaseActor::onMousePress(Window*window, unsigned int touchID)
	{
		//Open for implementation
	}

	void BaseActor::onMouseRelease(Window*window, unsigned int touchID)
	{
		//Open for implementation
	}

	void BaseActor::onMouseEnter(Window*window, unsigned int touchID)
	{
		//Open for implementation
	}

	void BaseActor::onMouseLeave(Window*window, unsigned int touchID)
	{
		//Open for implementation
	}

	bool BaseActor::isTouchDataActive(unsigned int touchID)
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

	bool BaseActor::isTouchDataPressed(unsigned int touchID)
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

	void BaseActor::applyTouchData(unsigned int touchID, bool pressed)
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

	void BaseActor::removeTouchData(unsigned int touchID)
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

	BaseActor::MouseTouchData* BaseActor::getTouchData(unsigned int touchID)
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

	ArrayList<unsigned int> BaseActor::getDifTouchData(const ArrayList<unsigned int>& touchIDs)
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
	
	void BaseActor::updateMouse(ApplicationData&appData)
	{
		Window* window = appData.getWindow();
		Transform& mouseTransform = appData.getTransform();
		
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
				mouseEventCalls.add(Pair<unsigned int, byte>(touchID, EVENTCALL_MOUSERELEASE));
			}
		}

		for(unsigned int i=0; i<touchIDs.size(); i++)
		{
			unsigned int touchID = touchIDs.get(i);
			Vector2f mousepos = Mouse::getPosition(window, touchID);
			Vector2f transformedPos = mouseTransform.transformPoint(mousepos);
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

		callMouseEvents(window, mouseEventCalls);
	}
	
	void BaseActor::updateTouch(ApplicationData&appData)
	{
		Window* window = appData.getWindow();
		Transform& mouseTransform = appData.getTransform();
		
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
				mouseEventCalls.add(Pair<unsigned int, byte>(touchID, EVENTCALL_MOUSERELEASE));
			}
		}

		for(unsigned int i=0; i<touchIDs.size(); i++)
		{
			unsigned int touchID = i;
			Vector2f touchpos = Mouse::getPosition(window, touchID);
			Vector2f transformedPos = mouseTransform.transformPoint(touchpos);
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
					applyTouchData(touchID, false);
				}
				removeTouchData(touchID);
			}
		}
		
		callMouseEvents(window, mouseEventCalls);
	}

	void BaseActor::callMouseEvents(Window*window, const ArrayList<Pair<unsigned int, byte> >& eventCallData)
	{
		for(unsigned int i=0; i<eventCallData.size(); i++)
		{
			const Pair<unsigned int, byte>& eventData = eventCallData.get(i);
			switch(eventData.second)
			{
				case EVENTCALL_MOUSEENTER:
				onMouseEnter(window, eventData.second);
				break;

				case EVENTCALL_MOUSELEAVE:
				onMouseLeave(window, eventData.second);
				break;

				case EVENTCALL_MOUSEPRESS:
				onMousePress(window, eventData.second);
				break;

				case EVENTCALL_MOUSERELEASE:
				onMouseRelease(window, eventData.second);
				break;
			}
		}
	}
	
	#undef EVENTCALL_MOUSEENTER
	#undef EVENTCALL_MOUSELEAVE
	#undef EVENTCALL_MOUSEPRESS
	#undef EVENTCALL_MOUSERELEASE
}