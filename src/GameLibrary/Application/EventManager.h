
#include "../Types.h"
#include "../Utilities/ArrayList.h"

#pragma once

namespace GameLibrary
{
	class EventManager
	{
		friend class Application;
		friend class Window;
	private:
		static ArrayList<Window*> windows;
		static void addWindow(Window*window);
		static void removeWindow(Window*window);

		static void update();
	};
}