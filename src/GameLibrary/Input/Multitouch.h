
#pragma once

#include "../Exception/IllegalArgumentException.h"
#include "../Utilities/Geometry/Vector2.h"
#include "../Window/Window.h"

namespace GameLibrary
{
	class MultitouchEventListener;
	
	/*! Represents the Multitouch interface and all touch instances on the Multitouch interface*/
	class Multitouch
	{
		friend class EventManager;
	public:
		/*! Gets a list of currently active touch instance IDs.
			\param window the window containing the touch instances
			\returns an ArrayList of unsigned integers representing unique touch instance IDs*/
		static ArrayList<unsigned int> getTouchIDs(Window*window);
		
		
		/*! Checks whether a given touch instance inside a given window is active.
			\param window the window containing the touch instance
			\param touchID the touch instance ID
			\returns true if the touch instance is active, or false if otherwise*/
		static bool isTouchActive(Window*window, unsigned int touchID);
		/*! Checks whether a given touch instance inside a given window was active in the previous frame.
			\param window the window containing the touch instance
			\param touchID the touch instance ID
			\returns true if the touch instance was active in the previous frame, or false if otherwise*/
		static bool wasTouchActive(Window*window, unsigned int touchID);
		
		
		/*! Gets the current position of a given touch instance inside a given window.
			\param window the window containing the touch instance
			\param touchID the touch instance ID
			\returns the touch instance's coordinates in the current frame, relative to the given Window*/
		static Vector2f getPosition(Window*window, unsigned int touchID);
		/*! Gets the current x coordinate of a given touch instance inside a given window.
			\param window the window containing the touch instance
			\param touchID the touch instance ID
			\returns the touch instance's x coordinate in the current frame, relative to the given Window*/
		static float getX(Window*window, unsigned int touchID);
		/*! Gets the current y coordinate of a given touch instance inside a given window.
			\param window the window containing the touch instance
			\param touchID the touch instance ID
			\returns the touch instance's y coordinate in the current frame, relative to the given Window*/
		static float getY(Window*window, unsigned int touchID);
		
		
		/*! Gets the previous frame's position of a given touch instance inside a given window.
			\param window the window containing the touch instance
			\param touchID the touch instance ID
			\returns the touch instance's coordinates in the previous frame, relative to the given Window*/
		static Vector2f getPreviousPosition(Window*window, unsigned int touchID);
		/*! Gets the previous frame's x coordinate of a given touch instance inside a given window.
			\param window the window containing the touch instance
			\param touchID the touch instance ID
			\returns the touch instance's x coordinate in the previous frame, relative to the given Window*/
		static float getPreviousX(Window*window, unsigned int touchID);
		/*! Gets the previous frame's y coordinate of a given touch instance inside a given window.
			\param window the window containing the touch instance
			\param touchID the touch instance ID
			\returns the touch instance's y coordinate in the previous frame, relative to the given Window*/
		static float getPreviousY(Window*window, unsigned int touchID);
		
		
		/*! Adds a MultitouchEventListener to handle Multitouch events.
			\param eventListener the listener pointer*/
		static void addEventListener(MultitouchEventListener*eventListener);
		/*! Removes a previously added MultitouchEventListener.
			\param eventListener the listener pointer*/
		static void removeEventListener(MultitouchEventListener*eventListener);
		
		
		/*! Checks if a multitouch interface is available and enabled on the current device.
			\returns true if multitouch is available, and the Multitouch class can be used, or false if there is no available multitouch interface on the current device*/
		static bool isAvailable();
		
	private:
		/*! Handles touch instance movement events sent from EventManager.
			\param window the window inside which the touch event occurred
			\param givenID the ID given to the touch instance by the system; This value is independent from touchID
			\param pos the current position of the touch instance, relative to the window
			\param dif the change in the position of the touch instance from the previous position*/
		static void handleTouchMove(Window*window, long long givenID, const Vector2f&pos, const Vector2f&dif);
		/*! Handles touch instance press events sent from EventManager.
			\param window the window inside which the touch event occurred
			\param givenID the ID given to the touch instance by the system; This value is independent from touchID
			\param pos the current position of the touch instance, relative to the window*/
		static void handleTouchDown(Window*window, long long givenID, const Vector2f&pos);
		/*! Handles touch instance release events sent from EventManager.
			\param window the window inside which the touch event occurred
			\param givenID the ID given to the touch instance by the system; This value is independent from touchID
			\param pos the current position of the touch instance, relative to the window*/
		static void handleTouchUp(Window*window, long long givenID, const Vector2f&pos);
		
		
		/*! Removes a Window from the Window list stored in Multitouch
			\param window the window pointer*/
		static void removeWindow(Window*window);
		
		
		/*! Updates all touch instance states. Called once per frame by EventManager from the Application in the main thread.*/
		static void update();
	};
	
	
	/*! Event listener that handles Multitouch events*/
	class MultitouchEventListener
	{
	public:
		/*! virtual destructor*/
		virtual ~MultitouchEventListener(){}
		/*! Called when a touch instance is created on a Window.
			\param window the window that contains the touch instance
			\param touchID the touch instance ID
			\param touchpos the touch instance coordinates, relative to the window*/
		virtual void onMultitouchDown(Window*window, unsigned int touchID, const Vector2f&touchpos){}
		/*! Called when a touch instance is destroyed on a Window.
			\param window the window that contained the touch instance
			\param touchID the touch instance ID
			\param touchpos the last touch instance coordinates, relative to the window*/
		virtual void onMultitouchUp(Window*window, unsigned int touchID, const Vector2f&touchpos){}
		/*! Called when a touch instance changes position inside a Window.
			\param window the window that contains the touch instance
			\param touchID the touch instance ID
			\param touchpos the current touch instance coordinates, relative to the window
			\param touchdif the change in the position of the touch instance from the previous position*/
		virtual void onMultitouchMove(Window*window, unsigned int touchID, const Vector2f&touchpos, const Vector2f&touchdif){}
	};
}
