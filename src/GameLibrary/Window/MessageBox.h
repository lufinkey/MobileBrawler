
#pragma once

#include "Window.h"

namespace GameLibrary
{
	class MessageBox
	{
	public:
		static unsigned int show(Window*parent, const String&title, const String&message);
		static unsigned int show(Window*parent, const String&title, const String&message, const ArrayList<String>&options);
	};
}
