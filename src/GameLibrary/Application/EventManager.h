
#include "../Types.h"
#include "../Utilities/ArrayList.h"

#pragma once

namespace GameLibrary
{
	class Application;

	class EventManager
	{
		friend class Keyboard;
		friend class Mouse;
		friend class Window;
	private:
		static const ArrayList<Window*>& getWindows();
		static void*getWindowMutexPtr();
		static Window*getWindowFromID(unsigned int windowID);
		static void*getDataFromWindow(Window*window);

		static void addWindow(Window*window);
		static void removeWindow(Window*window);

	public:
		static void update(Application*application);
	};
}