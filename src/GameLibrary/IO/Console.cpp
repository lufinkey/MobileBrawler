
#include "Console.h"

namespace GameLibrary
{
	Console::Console(std::ostream&out)
	{
		outstream = &out;
	}

	void Console::write(const String& output)
	{
		*outstream << output;
	}

	void Console::writeLine(const String& output)
	{
		*outstream << output << std::endl;
	}
}