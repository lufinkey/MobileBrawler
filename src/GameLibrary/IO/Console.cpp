
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

	void Console::writeError(const String& output)
	{
		std::cerr << output;
	}

	void Console::writeErrorLine(const String& output)
	{
		std::cerr << output << std::endl;
	}
}