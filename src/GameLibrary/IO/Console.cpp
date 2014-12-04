
#include "Console.h"
#include <iostream>

namespace GameLibrary
{
	void Console::write(const String& output)
	{
		std::cout << output;
	}

	void Console::writeLine(const String& output)
	{
		std::cout << output << std::endl;
	}
}