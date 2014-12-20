
#include "../Exception/IllegalArgumentException.h"
#include "../Utilities/Geometry/Vector2.h"
#include "../Window/Window.h"

#pragma once

namespace GameLibrary
{
	class MultitouchEventListener;
	
	class Multitouch
	{
		friend class EventManager;
	public:
		static ArrayList<unsigned int> getTouchIDs(Window*window);

		static bool isTouchActive(Window*window, unsigned int touchID);
		static bool wasTouchActive(Window*window, unsigned int touchID);
		
		static Vector2f getPosition(Window*window, unsigned int touchID);
		static float getX(Window*window, unsigned int touchID);
		static float getY(Window*window, unsigned int touchID);
		
		static Vector2f getPreviousPosition(Window*window, unsigned int touchID);
		static float getPreviousX(Window*window, unsigned int touchID);
		static float getPreviousY(Window*window, unsigned int touchID);

		/*Adds a MultitouchEventListener to handle Multitouch events*/
		static void addEventListener(MultitouchEventListener*);
		/*Removes a previously added MultitouchEventListener*/
		static void removeEventListener(MultitouchEventListener*);
		
	private:
		static void handleTouchMove(Window*window, long long givenID, const Vector2f&pos, const Vector2f&dif);
		static void handleTouchDown(Window*window, long long givenID, const Vector2f&pos);
		static void handleTouchUp(Window*window, long long givenID, const Vector2f&pos);
		
		static void removeWindow(Window*window);
		
		static void update();
	};
	
	class MultitouchEventListener
	{
	public:
		virtual void onMultitouchDown(Window*window, unsigned int touchID, const Vector2f&touchpos);
		virtual void onMultitouchUp(Window*window, unsigned int touchID, const Vector2f&touchpos);
		virtual void onMultitouchMove(Window*window, unsigned int touchID, const Vector2f&touchpos, const Vector2f&touchdif);
		
		/*destructor*/
		virtual ~MultitouchEventListener();
	};
}
