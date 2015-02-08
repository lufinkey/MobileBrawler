
#pragma once

#include "../Utilities/String.h"

namespace GameLibrary
{
	/*! Used to log output or error information to the console*/
	class Console
	{
	public:
		/*! Writes output to the console
			\param output an output string*/
		static void write(const String&output);
		/*! Writes output to the console and goes to a new line
			\param output an output string*/
		static void writeLine(const String&output);
		/*! Writes an error to the console
			\param error an error string*/
		static void writeError(const String&error);
		/*! Writes an error to the console and goes to a new line
			\param error an error string*/
		static void writeErrorLine(const String&error);
	};
}