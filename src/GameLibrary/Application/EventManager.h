
#pragma once

#include "../Types.h"
#include "../Utilities/ArrayList.h"

namespace GameLibrary
{
	class Application;
	
	
	/*! Manages Application and Window events. Automatically called in the Application loop.*/
	class EventManager
	{
		friend class Keyboard;
		friend class Mouse;
		friend class Multitouch;
		friend class Window;
	private:
		static const ArrayList<Window*>& getWindows();
		static void*getWindowMutexPtr();
		static Window*getWindowFromID(unsigned int windowID);
		static void*getDataFromWindow(Window*window);
		
		static void addWindow(Window*window);
		static void removeWindow(Window*window);
		
	public:
		/*! Polls all the queued events of the current Application.
			\param application the current Application*/
		static void update(Application*application);
	};
}