
#pragma once

#include "../Utilities/String.h"

namespace GameLibrary
{
	class Console
	{
	public:
		static void write(const String&);
		static void writeLine(const String&);
		static void writeError(const String&);
		static void writeErrorLine(const String&);
	};
}