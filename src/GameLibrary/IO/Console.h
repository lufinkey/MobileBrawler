
#include "../Utilities/String.h"
#include <iostream>

#pragma once

namespace GameLibrary
{
	class Console
	{
	private:
		std::ostream* outstream;

	public:
		Console(std::ostream&);

		void write(const String&);
		void writeLine(const String&);
	};
}