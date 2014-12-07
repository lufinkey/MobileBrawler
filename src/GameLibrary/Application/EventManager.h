
#include "../Types.h"
#include "../Utilities/ArrayList.h"

#pragma once

namespace GameLibrary
{
	class EventManager
	{
		friend class Application;
		friend class Keyboard;
		friend class Mouse;
		friend class Window;
	private:
		static const ArrayList<Window*>& getWindows();
		static void*getWindowMutexPtr();
		static Window*getWindowFromData(void*windata);
		static void*getDataFromWindow(Window*window);

		static void addWindow(Window*window);
		static void removeWindow(Window*window);

		static void update();
	};
}