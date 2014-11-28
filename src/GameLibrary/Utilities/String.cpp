
#define _CRT_SECURE_NO_WARNINGS

#include "String.h"
#include <string>
#include <iostream>
#include <sstream>
#include <vector>
#include <iomanip>
#include <stdlib.h>
#include "stdio.h"
#include <cmath>

#ifdef STRING_USES_GAMELIBRARY
	#include "../Exception/NumberFormatException.h"
	#include "../Exception/Utilities/StringOutOfBoundsException.h"
#else
	StringException::StringException(const StringException&exception) : std::exception(exception)
	{
		message = exception.message;
	}

	StringException::StringException(const std::string&reason)
	{
		message = reason;
	}

	virtual ~StringException()
	{
		//
	}

	virtual const char* what() const
	{
		return message.c_str();
	}
#endif

#ifdef STRING_USES_GAMELIBRARY
namespace GameLibrary
{
#endif
	long long string_powll(const long long base, const int exp)
	{
		if(exp==0)
		{
			return 1;
		}
		
		long long result = base;
		int absExp = std::abs(exp);
		
		for(int i=1; i<absExp; i++)
		{
			result = result*base;
		}
		
		if(exp<0)
		{
			result = 1/result;
		}
		
		return result;
	}

	unsigned long long string_powull(const unsigned long long base, const int exp)
	{
		if(exp==0)
		{
			return 1;
		}
		
		unsigned long long result = base;
		int absExp = std::abs(exp);
		
		for(int i=1; i<absExp; i++)
		{
			result = result*base;
		}
		
		if(exp<0)
		{
			result = 1/result;
		}
		
		return result;
	}

	bool String::asBool(const String&str)
	{
		if(str.total == 0)
		{
#ifdef STRING_USES_GAMELIBRARY
			throw NumberFormatException("bool", "String is empty");
#else
			throw StringException("Unable to convert String to type bool: String is empty");
#endif
		}

		bool onlyNums = true;
		bool hasNum = false;
		bool hasDecimal = false;

		for(unsigned int i=0; i<str.length(); i++)
		{
			char c = str.charAt(i);
			if(!(c>='0' && c<='9'))
			{
				if(c=='.')
				{
					if(onlyNums && hasDecimal)
					{
#ifdef STRING_USES_GAMELIBRARY
						throw NumberFormatException("bool", "Too many decimal points");
#else
						throw StringException("Unable to convert to type bool: Too many decimal points");
#endif
					}
					else if(onlyNums)
					{
						hasDecimal = true;
					}
				}
				else if(hasNum)
				{
#ifdef STRING_USES_GAMELIBRARY
					throw NumberFormatException("bool", "Invalid string. Bool should either be true, false, or a number");
#else
					throw StringException("Unable to convert to type bool: Invalid string. Bool should either be true, false, or a number");
#endif
				}
				else
				{
					onlyNums = false;
				}
			}
			else
			{
				hasNum = true;
			}
		}

		if(onlyNums)
		{
			if(hasDecimal)
			{
				double d = asDouble(str);
				if(d!=0)
				{
					return true;
				}
				else
				{
					return false;
				}
			}
			else
			{
				long l = asLong(str);
				if(l!=0)
				{
					return true;
				}
				else
				{
					return false;
				}
			}
		}
		else if(hasNum)
		{
#ifdef STRING_USES_GAMELIBRARY
			throw NumberFormatException("bool", "Invalid string. Bool should either be true, false, or a number");
#else
			throw StringException("Unable to convert to type bool: Invalid string. Bool should either be true, false, or a number");
#endif
		}
		else
		{
			if(str.equals("true") || str.equals("TRUE") || str.equals("on") || str.equals("ON") || str.equals("yes") || str.equals("YES"))
			{
				return true;
			}
			else if(str.equals("false") || str.equals("FALSE") || str.equals("off") || str.equals("OFF") || str.equals("no") || str.equals("NO"))
			{
				return false;
			}
			else
			{
#ifdef STRING_USES_GAMELIBRARY
			throw NumberFormatException("bool", "Invalid string. Bool should either be true, false, or a number");
#else
			throw StringException("Unable to convert to type bool: Invalid string. Bool should either be true, false, or a number");
#endif
			}
		}
	}

	int String::asInt(const String&str)
	{
		if(str.total == 0)
		{
#ifdef STRING_USES_GAMELIBRARY
			throw NumberFormatException("int", "String is empty");
#else
			throw StringException("Unable to convert to type int: String is empty");
#endif
		}

		for(unsigned int i=0; i<str.total; i++)
		{
			char c = str.charAt(i);
			if(!((c>='0' && c<='9') || (c=='-' && i==0) || (c=='+' && i==0)))
			{
#ifdef STRING_USES_GAMELIBRARY
				throw NumberFormatException("int", (String)"Unexpected character \'" + c + '\'');
#else
				throw StringException((std::string)"Unable to convert to type int: Unexpected character  + c + '\'');
#endif
			}
		}

		int mult = 1;
		unsigned int startIndex = 0;
		if(str.charAt(0)=='-')
		{
			mult = -1;
			startIndex = 1;
		}
		else if(str.charAt(0)=='+')
		{
			mult = 1;
			startIndex = 1;
		}

		int counter = 0;
		int totalVal = 0;

		for(unsigned int i=(str.total-1); i>=startIndex; i--)
		{
			char c = str.charAt(i);
			int value = (int)(c - '0');
			if(counter==0)
			{
				totalVal += value;
			}
			else
			{
				totalVal += (value*(int)std::pow((float)10,counter));
			}
			counter++;

			if(i == startIndex)
			{
				return totalVal*mult;
			}
		}

		return totalVal*mult;
	}

	long String::asLong(const String&str)
	{
		if(str.total == 0)
		{
#ifdef STRING_USES_GAMELIBRARY
			throw NumberFormatException("long", "String is empty");
#else
			throw StringException("Unable to convert to type long: String is empty");
#endif
		}

		for(unsigned int i=0; i<str.total; i++)
		{
			char c = str.charAt(i);
			if(!((c>='0' && c<='9') || (c=='-' && i==0) || (c=='+' && i==0)))
			{
#ifdef STRING_USES_GAMELIBRARY
				throw NumberFormatException("long", (String)"Unexpected character \'" + c + '\'');
#else
				throw StringException((std::string)"Unable to convert to type long: Unexpected character \'" + c + '\'');
#endif
			}
		}

		int mult = 1;
		unsigned int startIndex = 0;
		if(str.charAt(0)=='-')
		{
			mult = -1;
			startIndex = 1;
		}
		else if(str.charAt(0)=='+')
		{
			mult = 1;
			startIndex = 1;
		}

		int counter = 0;
		long totalVal = 0;

		for(unsigned int i=(str.total-1); i>=startIndex; i--)
		{
			char c = str.charAt(i);
			int value = (int)(c - '0');
			if(counter==0)
			{
				totalVal += value;
			}
			else
			{
				totalVal += ((long)value*(long)std::pow((long double)10,(int)counter));
			}
			counter++;

			if(i == startIndex)
			{
				return totalVal*mult;
			}
		}

		return totalVal*mult;
	}

	short String::asShort(const String&str)
	{
		if(str.total == 0)
		{
#ifdef STRING_USES_GAMELIBRARY
			throw NumberFormatException("short", "String is empty");
#else
			throw StringException("Unable to convert to type short: String is empty");
#endif
		}

		for(unsigned int i=0; i<str.total; i++)
		{
			char c = str.charAt(i);
			if(!((c>='0' && c<='9') || (c=='-' && i==0) || (c=='+' && i==0)))
			{
#ifdef STRING_USES_GAMELIBRARY
				throw NumberFormatException("short", (String)"Unexpected character \'" + c + '\'');
#else
				throw StringException((std::string)"Unable to convert to type short: Unexpected character \'" + c + '\'');
#endif
			}
		}
		
		int mult = 1;
		unsigned int startIndex = 0;
		if(str.charAt(0)=='-')
		{
			mult = -1;
			startIndex = 1;
		}
		else if(str.charAt(0)=='+')
		{
			mult = 1;
			startIndex = 1;
		}
		
		int counter = 0;
		short totalVal = 0;
		
		for(unsigned int i=(str.total-1); i>=startIndex; i--)
		{
			char c = str.charAt(i);
			int value = (short)(c - '0');
			if(counter==0)
			{
				totalVal += value;
			}
			else
			{
				totalVal += ((short)value*(short)std::pow((float)10,(int)counter));
			}
			counter++;

			if(i == startIndex)
			{
				return (short)(totalVal*mult);
			}
		}
		
		return (short)(totalVal*mult);
	}

	float String::asFloat(const String&str)
	{
		if(str.total == 0)
		{
#ifdef STRING_USES_GAMELIBRARY
			throw NumberFormatException("float", "String is empty");
#else
			throw StringException("Unable to convert to type float: String is empty");
#endif
		}

		bool hasDecimal = false;
		unsigned int decimalIndex = str.total;

		for(unsigned int i=0; i<str.total; i++)
		{
			char c = str.charAt(i);
			if(!((c>='0' && c<='9') || (c=='-' && i==0) || (c=='+' && i==0)))
			{
				if(c=='.')
				{
					if(hasDecimal)
					{
#ifdef STRING_USES_GAMELIBRARY
				throw NumberFormatException("float", (String)"Too many decimal points");
#else
				throw StringException("Unable to convert to type float: Too many decimal points");
#endif
					}
					else
					{
						hasDecimal = true;
						decimalIndex = i;
					}
				}
#ifdef STRING_USES_GAMELIBRARY
				throw NumberFormatException("float", (String)"Unexpected character \'" + c + '\'');
#else
				throw StringException((std::string)"Unable to convert to type float: Unexpected character \'" + c + '\'');
#endif
			}
		}

		int mult = 1;
		unsigned int startIndex = 0;
		if(str.charAt(0)=='-')
		{
			mult = -1;
			startIndex = 1;
		}
		else if(str.charAt(0)=='+')
		{
			mult = 1;
			startIndex = 1;
		}

		int counter = -1;
		float totalVal = 0;

		for(unsigned int i=(decimalIndex+1); i<str.total; i++)
		{
			char c = str.charAt(i);
			int value = (int)(c - '0');
			totalVal += (float)(value*std::pow((float)10,counter));
			counter--;
		}

		counter = 0;

		for(unsigned int i=(decimalIndex-1); i>=startIndex; i--)
		{
			char c = str.charAt(i);
			int value = (int)(c - '0');
			if(counter==0)
			{
				totalVal += value;
			}
			else
			{
				totalVal += (float)(value*(int)std::pow((float)10,counter));
			}
			counter++;

			if(i == startIndex)
			{
				return totalVal*mult;
			}
		}

		return totalVal*mult;
	}

	double String::asDouble(const String&str)
	{
		if(str.total == 0)
		{
#ifdef STRING_USES_GAMELIBRARY
			throw NumberFormatException("double", "String is empty");
#else
			throw StringException("Unable to convert to type double: String is empty");
#endif
		}

		bool hasDecimal = false;
		unsigned int decimalIndex = str.total;

		for(unsigned int i=0; i<str.total; i++)
		{
			char c = str.charAt(i);
			if(!((c>='0' && c<='9') || (c=='-' && i==0) || (c=='+' && i==0)))
			{
				if(c=='.')
				{
					if(hasDecimal)
					{
#ifdef STRING_USES_GAMELIBRARY
				throw NumberFormatException("double", "Too many decimal points");
#else
				throw StringException("Unable to convert to type double: Too many decimal points");
#endif
					}
					else
					{
						hasDecimal = true;
						decimalIndex = i;
					}
				}
				else
				{
#ifdef STRING_USES_GAMELIBRARY
				throw NumberFormatException("double", (String)"Unexpected character \'" + c + '\'');
#else
				throw StringException((std::string)"Unable to convert to type double: Unexpected character \'" + c + '\'');
#endif
				}
			}
		}

		int mult = 1;
		unsigned int startIndex = 0;
		if(str.charAt(0)=='-')
		{
			mult = -1;
			startIndex = 1;
		}
		else if(str.charAt(0)=='+')
		{
			mult = 1;
			startIndex = 1;
		}
		
		int counter = -1;
		double totalVal = 0;

		for(unsigned int i=(decimalIndex+1); i<str.total; i++)
		{
			char c = str.charAt(i);
			int value = (int)(c - '0');
			totalVal += (double)(value*std::pow((double)10,counter));
			counter--;
		}

		counter = 0;

		for(unsigned int i=(decimalIndex-1); i>=startIndex; i--)
		{
			char c = str.charAt(i);
			int value = (int)(c - '0');
			if(counter==0)
			{
				totalVal += value;
			}
			else
			{
				totalVal += (value*(double)std::pow((double)10,counter));
			}
			counter++;

			if(i == startIndex)
			{
				return totalVal*mult;
			}
		}

		return totalVal*mult;
	}

	long long String::asLongLong(const String&str)
	{
		if(str.total == 0)
		{
#ifdef STRING_USES_GAMELIBRARY
			throw NumberFormatException("long long", "String is empty");
#else
			throw StringException("Unable to convert to type long long: String is empty");
#endif
		}

		for(unsigned int i=0; i<str.total; i++)
		{
			char c = str.charAt(i);
			if(!((c>='0' && c<='9') || (c=='-' && i==0) || (c=='+' && i==0)))
			{
#ifdef STRING_USES_GAMELIBRARY
				throw NumberFormatException("long long", (String)"Unexpected character \'" + c + '\'');
#else
				throw StringException((std::string)"Unable to convert to type long long: Unexpected character \'" + c + '\'');
#endif
			}
		}
		
		int mult = 1;
		unsigned int startIndex = 0;
		if(str.charAt(0)=='-')
		{
			mult = -1;
			startIndex = 1;
		}
		else if(str.charAt(0)=='+')
		{
			mult = 1;
			startIndex = 1;
		}
		
		int counter = 0;
		long long totalVal = 0;
		
		for(unsigned int i=(str.total-1); i>=startIndex; i--)
		{
			char c = str.charAt(i);
			int value = (int)(c - '0');
			if(counter==0)
			{
				totalVal += value;
			}
			else
			{
				totalVal += ((long long)value*(long long)string_powll((long long)10,(int)counter));
			}
			counter++;

			if(i == startIndex)
			{
				return (long long)(totalVal*mult);
			}
		}
		
		return (long long)(totalVal*mult);
	}

	unsigned int String::asUInt(const String&str)
	{
		if(str.total == 0)
		{
#ifdef STRING_USES_GAMELIBRARY
			throw NumberFormatException("unsigned int", "String is empty");
#else
			throw StringException("Unable to convert to type unsigned int: String is empty");
#endif
		}

		for(unsigned int i=0; i<str.total; i++)
		{
			char c = str.charAt(i);
			if(!(c>='0' && c<='9'))
			{
#ifdef STRING_USES_GAMELIBRARY
				throw NumberFormatException("unsigned int", (String)"Unexpected character \'" + c + '\'');
#else
				throw StringException((std::string)"Unable to convert to type unsigned int: Unexpected character \'" + c + '\'');
#endif
			}
		}
		
		unsigned int startIndex = 0;
		
		int counter = 0;
		unsigned int totalVal = 0;
		
		for(unsigned int i=(str.total-1); i>=startIndex; i--)
		{
			char c = str.charAt(i);
			unsigned int value = (unsigned int)(c - '0');
			if(counter==0)
			{
				totalVal += value;
			}
			else
			{
				totalVal += ((unsigned int)value*(unsigned int)std::pow((float)10,counter));
			}
			counter++;

			if(i == startIndex)
			{
				return totalVal;
			}
		}
		
		return totalVal;
	}

	unsigned char String::asUChar(const String&str)
	{
		if(str.total == 0)
		{
#ifdef STRING_USES_GAMELIBRARY
			throw NumberFormatException("unsigned char", "String is empty");
#else
			throw StringException("Unable to convert to type unsigned char: String is empty");
#endif
		}

		for(unsigned int i=0; i<str.total; i++)
		{
			char c = str.charAt(i);
			if(!(c>='0' && c<='9'))
			{
#ifdef STRING_USES_GAMELIBRARY
				throw NumberFormatException("unsigned char", (String)"Unexpected character \'" + c + '\'');
#else
				throw StringException((std::string)"Unable to convert to type unsigned char: Unexpected character \'" + c + '\'');
#endif
			}
		}
		
		unsigned int startIndex = 0;
		
		int counter = 0;
		unsigned char totalVal = 0;
		
		for(unsigned int i=(str.total-1); i>=startIndex; i--)
		{
			char c = str.charAt(i);
			unsigned char value = (unsigned char)(c - '0');
			if(counter==0)
			{
				totalVal += value;
			}
			else
			{
				totalVal += ((unsigned char)value*(unsigned char)std::pow((float)10,counter));
			}
			counter++;

			if(i == startIndex)
			{
				return totalVal;
			}
		}
		
		return totalVal;
	}

	unsigned long String::asULong(const String&str)
	{
		if(str.total == 0)
		{
#ifdef STRING_USES_GAMELIBRARY
			throw NumberFormatException("unsigned long", "String is empty");
#else
			throw StringException("Unable to convert to type unsigned long: String is empty");
#endif
		}

		for(unsigned int i=0; i<str.total; i++)
		{
			char c = str.charAt(i);
			if(!(c>='0' && c<='9'))
			{
#ifdef STRING_USES_GAMELIBRARY
				throw NumberFormatException("unsigned long", (String)"Unexpected character \'" + c + '\'');
#else
				throw StringException((std::string)"Unable to convert to type unsigned long: Unexpected character \'" + c + '\'');
#endif
			}
		}
		
		unsigned int startIndex = 0;
		
		int counter = 0;
		unsigned long totalVal = 0;
		
		for(unsigned int i=(str.total-1); i>=startIndex; i--)
		{
			char c = str.charAt(i);
			unsigned int value = (unsigned int)(c - '0');
			if(counter==0)
			{
				totalVal += value;
			}
			else
			{
				totalVal += ((unsigned long)value*(unsigned long)std::pow((long double)10,(int)counter));
			}
			counter++;

			if(i == startIndex)
			{
				return totalVal;
			}
		}
		
		return totalVal;
	}

	unsigned short String::asUShort(const String&str)
	{
		if(str.total == 0)
		{
#ifdef STRING_USES_GAMELIBRARY
			throw NumberFormatException("unsigned short", "String is empty");
#else
			throw StringException("Unable to convert to type unsigned short: String is empty");
#endif
		}

		for(unsigned int i=0; i<str.total; i++)
		{
			char c = str.charAt(i);
			if(!(c>='0' && c<='9'))
			{
#ifdef STRING_USES_GAMELIBRARY
				throw NumberFormatException("unsigned short", (String)"Unexpected character \'" + c + '\'');
#else
				throw StringException((std::string)"Unable to convert to type unsigned short: Unexpected character \'" + c + '\'');
#endif
			}
		}
		
		unsigned int startIndex = 0;
		
		int counter = 0;
		unsigned short totalVal = 0;
		
		for(unsigned int i=(str.total-1); i>=startIndex; i--)
		{
			char c = str.charAt(i);
			unsigned short value = (unsigned short)(c - '0');
			if(counter==0)
			{
				totalVal += value;
			}
			else
			{
				totalVal += ((unsigned short)value*(unsigned short)std::pow((float)10,(int)counter));
			}
			counter++;

			if(i == startIndex)
			{
				return totalVal;
			}
		}
		
		return totalVal;
	}

	unsigned long long String::asULongLong(const String&str)
	{
		if(str.total == 0)
		{
#ifdef STRING_USES_GAMELIBRARY
			throw NumberFormatException("unsigned long long", "String is empty");
#else
			throw StringException("Unable to convert to type unsigned long long: String is empty");
#endif
		}

		for(unsigned int i=0; i<str.total; i++)
		{
			char c = str.charAt(i);
			if(!(c>='0' && c<='9'))
			{
#ifdef STRING_USES_GAMELIBRARY
				throw NumberFormatException("unsigned long long", (String)"Unexpected character \'" + c + '\'');
#else
				throw StringException((std::string)"Unable to convert to type unsigned long long: Unexpected character \'" + c + '\'');
#endif
			}
		}
		
		unsigned int startIndex = 0;
		
		int counter = 0;
		unsigned long long totalVal = 0;
		
		for(unsigned int i=(str.total-1); i>=startIndex; i--)
		{
			char c = str.charAt(i);
			unsigned int value = (unsigned int)(c - '0');
			if(counter==0)
			{
				totalVal += value;
			}
			else
			{
				totalVal += ((unsigned long long)value*(unsigned long long)string_powull((unsigned long long)10,(int)counter));
			}
			counter++;

			if(i == startIndex)
			{
				return totalVal;
			}
		}
		
		return totalVal;
	}

	char String::asLowerCaseChar(char c)
	{
		if(c >= 'A' && c <= 'Z')
		{
			return c + ('a' - 'A');
		}
		return c;
	}

	char String::asUpperCaseChar(char c)
	{
		if(c >= 'a' && c <= 'z')
		{
			return c - ('a' - 'A');
		}
		return c;
	}

	std::string String::intToString(int num)
	{
		std::stringstream ss;
		ss << num;
		std::string s(ss.str());
		return s;
	}

	std::string String::uintToString(unsigned int num)
	{
		std::stringstream ss;
		ss << num;
		std::string s(ss.str());
		return s;
	}

	std::string String::floatToString(float num)
	{
		char buffer[20];
		sprintf(buffer, "%g", (double)num);
		return std::string(buffer);
	}

	std::string String::doubleToString(double num)
	{
		char buffer[20];
		sprintf(buffer, "%g", (double)num);
		return std::string(buffer);
	}

	std::string String::longToString(long num)
	{
		std::stringstream ss;
		ss << num;
		std::string s(ss.str());
		return s;
	}

	String::String()
	{
		total = 0;
		characters = (char*)std::calloc(1,1);
		characters[0] = '\0';
	}

	String::String(const String& str)
	{
		total = str.length();
		characters = (char*)std::calloc(total+1,1);
		for(unsigned int i=0; i<total; i++)
		{
			characters[i] = str.characters[i];
		}

		characters[total] = '\0';
	}

	String::String(const std::string&str)
	{
		total = str.length();
		characters = (char*)std::calloc(total+1,1);
		for(unsigned int i=0; i<total; i++)
		{
			characters[i] = str.at(i);
		}

		characters[total] = '\0';
	}

	String::String(const char*str)
	{
		total = std::strlen(str);
		characters = (char*)std::calloc(total+1,1);
		for(unsigned int i=0; i<total; i++)
		{
			characters[i] = str[i];
		}

		characters[total] = '\0';
	}

	String::String(const wchar_t*str)
	{
		total = std::wcslen(str);
		characters = (char*)std::calloc(total+1,1);

		std::wcstombs(characters,str,total+1);

		characters[total] = '\0';
	}

	String::String(const std::wstring&str)
	{
		total = str.length();
		characters = (char*)std::calloc(total+1,1);

		std::wcstombs(characters,str.c_str(),total+1);
		
		characters[total] = '\0';
	}

	String::String(bool b)
	{
		if(b)
		{
			characters = (char*)std::calloc(5,1);
			characters[0] = 't';
			characters[1] = 'r';
			characters[2] = 'u';
			characters[3] = 'e';
			characters[4] = '\0';
			total = 4;
		}
		else
		{
			characters = (char*)std::calloc(6,1);
			characters[0] = 'f';
			characters[1] = 'a';
			characters[2] = 'l';
			characters[3] = 's';
			characters[4] = 'e';
			characters[5] = '\0';
			total = 5;
		}
	}

	String::String(char c)
	{
		total = 1;
		characters = (char*)std::calloc(total+1,1);

		characters[0] = c;
		characters[1] = '\0';
	}

	String::String(unsigned char num)
	{
		std::string str = String::intToString((int)num);
		total = str.length();
		characters = (char*)std::calloc(total+1,1);

		for(unsigned int i=0; i<total; i++)
		{
			characters[i] = str.at(i);
		}

		characters[total] = '\0';
	}

	String::String(int num)
	{
		std::string str = String::intToString(num);
		total = str.length();
		characters = (char*)std::calloc(total+1,1);

		for(unsigned int i=0; i<total; i++)
		{
			characters[i] = str.at(i);
		}

		characters[total] = '\0';
	}

	String::String(unsigned int num)
	{
		std::string str = String::uintToString(num);
		total = str.length();
		characters = (char*)std::calloc(total+1,1);

		for(unsigned int i=0; i<total; i++)
		{
			characters[i] = str.at(i);
		}

		characters[total] = '\0';
	}

	String::String(float num)
	{
		std::string str = String::floatToString(num);
		total = str.length();
		characters = (char*)std::calloc(total+1,1);

		for(unsigned int i=0; i<total; i++)
		{
			characters[i] = str.at(i);
		}

		characters[total] = '\0';
	}

	String::String(double num)
	{
		std::string str = String::doubleToString(num);
		total = str.length();
		characters = (char*)std::calloc(total+1,1);

		for(unsigned int i=0; i<total; i++)
		{
			characters[i] = str.at(i);
		}

		characters[total] = '\0';
	}

	String::String(long num)
	{
		std::string str = String::longToString(num);
		total = str.length();
		characters = (char*)std::calloc(total+1,1);

		for(unsigned int i=0; i<total; i++)
		{
			characters[i] = str.at(i);
		}

		characters[total] = '\0';
	}

	String::~String()
	{
		std::free(characters);
		characters = NULL;
	}

	std::wstring String::wstring() const
	{
		wchar_t*str = new wchar_t[total+1];
		std::mbstowcs(str,characters,total+1);
		std::wstring newStr(str);
		delete[] str;
		return newStr;
	}

	String::operator char*()
	{
		return characters;
	}

	String::operator const char*()
	{
		return characters;
	}

	String::operator std::string()
	{
		return std::string(characters);
	}

	String::operator std::wstring()
	{
		wchar_t*str = new wchar_t[total+1];
		std::mbstowcs(str,characters,total+1);
		std::wstring newStr(str);
		delete[] str;
		return newStr;
	}

	String::operator char*() const
	{
		return characters;
	}

	String::operator const char*() const
	{
		return characters;
	}

	String::operator std::string() const
	{
		return std::string(characters);
	}

	String::operator std::wstring() const
	{
		wchar_t*str = new wchar_t[total+1];
		std::mbstowcs(str,characters,total+1);
		std::wstring newStr(str);
		delete[] str;
		return newStr;
	}

	String String::operator+(const String& str) const
	{
		String newStr;
		unsigned int total2 = total + str.length();
		newStr.characters = (char*)std::realloc(newStr.characters, total2+1);
		newStr.total = total2;
		for(unsigned int i=0; i<total; i++)
		{
			newStr.characters[i] = characters[i];
		}
		unsigned int counter = 0;
		for(unsigned int i=total; i<total2; i++)
		{
			newStr.characters[i] = str.characters[counter];
			counter++;
		}
		newStr.characters[total2] = '\0';
		return newStr;
	}

	String String::operator+(const std::string& str) const
	{
		String newStr;
		unsigned int total2 = total + str.length();
		newStr.characters = (char*)std::realloc(newStr.characters, total2+1);
		newStr.total = total2;
		for(unsigned int i=0; i<total; i++)
		{
			newStr.characters[i] = characters[i];
		}
		unsigned int counter = 0;
		for(unsigned int i=total; i<total2; i++)
		{
			newStr.characters[i] = str.at(counter);
			counter++;
		}
		newStr.characters[total2] = '\0';
		return newStr;
	}

	String String::operator+(const char*str) const
	{
		String newStr;
		unsigned int total2 = total + strlen(str);
		newStr.characters = (char*)std::realloc(newStr.characters, total2+1);
		newStr.total = total2;
		for(unsigned int i=0; i<total; i++)
		{
			newStr.characters[i] = characters[i];
		}
		unsigned int counter = 0;
		for(unsigned int i=total; i<total2; i++)
		{
			newStr.characters[i] = str[counter];
			counter++;
		}
		newStr.characters[total2] = '\0';
		return newStr;
	}

	String String::operator+(const wchar_t*str) const
	{
		String newStr;
		String str2(str);
		unsigned int total2 = total + str2.length();
		newStr.characters = (char*)std::realloc(newStr.characters, total2+1);
		newStr.total = total2;
		for(unsigned int i=0; i<total; i++)
		{
			newStr.characters[i] = characters[i];
		}
		unsigned int counter = 0;
		for(unsigned int i=total; i<total2; i++)
		{
			newStr.characters[i] = str2.characters[counter];
			counter++;
		}
		newStr.characters[total2] = '\0';
		return newStr;
	}

	String String::operator+(const std::wstring& str) const
	{
		String newStr;
		String str2(str);
		unsigned int total2 = total + str2.length();
		newStr.characters = (char*)std::realloc(newStr.characters, total2+1);
		newStr.total = total2;
		for(unsigned int i=0; i<total; i++)
		{
			newStr.characters[i] = characters[i];
		}
		unsigned int counter = 0;
		for(unsigned int i=total; i<total2; i++)
		{
			newStr.characters[i] = str2.characters[counter];
			counter++;
		}
		newStr.characters[total2] = '\0';
		return newStr;
	}

	String String::operator+(bool b) const
	{
		String newStr = characters;
		if(b)
		{
			newStr += "true";
		}
		else
		{
			newStr += "false";
		}
		return newStr;
	}

	String String::operator+(char c) const
	{
		String newStr;
		unsigned int total2 = total+1;
		newStr.characters = (char*)std::realloc(newStr.characters, total2+1);
		newStr.total = total2;
		for(unsigned int i=0; i<total; i++)
		{
			newStr.characters[i] = characters[i];
		}
		newStr.characters[total] = c;
		newStr.characters[total+1] = '\0';
		return newStr;
	}

	String String::operator+(unsigned char num) const
	{
		String newStr;
		std::string str = String::intToString((int)num);
		unsigned int total2 = total + str.length();
		newStr.characters = (char*)std::realloc(newStr.characters, total2+1);
		newStr.total = total2;
		for(unsigned int i=0; i<total; i++)
		{
			newStr.characters[i] = characters[i];
		}
		unsigned int counter = 0;
		for(unsigned int i=total; i<total2; i++)
		{
			newStr.characters[i] = str.at(counter);
			counter++;
		}
		newStr.characters[total2] = '\0';
		return newStr;
	}

	String String::operator+(int num) const
	{
		String newStr;
		std::string str = String::intToString(num);
		unsigned int total2 = total + str.length();
		newStr.characters = (char*)std::realloc(newStr.characters, total2+1);
		newStr.total = total2;
		for(unsigned int i=0; i<total; i++)
		{
			newStr.characters[i] = characters[i];
		}
		unsigned int counter = 0;
		for(unsigned int i=total; i<total2; i++)
		{
			newStr.characters[i] = str.at(counter);
			counter++;
		}
		newStr.characters[total2] = '\0';
		return newStr;
	}

	String String::operator+(unsigned int num) const
	{
		String newStr;
		std::string str = String::uintToString(num);
		unsigned int total2 = total + str.length();
		newStr.characters = (char*)std::realloc(newStr.characters, total2+1);
		newStr.total = total2;
		for(unsigned int i=0; i<total; i++)
		{
			newStr.characters[i] = characters[i];
		}
		unsigned int counter = 0;
		for(unsigned int i=total; i<total2; i++)
		{
			newStr.characters[i] = str.at(counter);
			counter++;
		}
		newStr.characters[total2] = '\0';
		return newStr;
	}

	String String::operator+(long num) const
	{
		String newStr;
		std::string str = String::longToString(num);
		unsigned int total2 = total + str.length();
		newStr.characters = (char*)std::realloc(newStr.characters, total2+1);
		newStr.total = total2;
		for(unsigned int i=0; i<total; i++)
		{
			newStr.characters[i] = characters[i];
		}
		unsigned int counter = 0;
		for(unsigned int i=total; i<total2; i++)
		{
			newStr.characters[i] = str.at(counter);
			counter++;
		}
		newStr.characters[total2] = '\0';
		return newStr;
	}

	String String::operator+(float num) const
	{
		String newStr;
		std::string str = String::floatToString(num);
		unsigned int total2 = total + str.length();
		newStr.characters = (char*)std::realloc(newStr.characters, total2+1);
		newStr.total = total2;
		for(unsigned int i=0; i<total; i++)
		{
			newStr.characters[i] = characters[i];
		}
		unsigned int counter = 0;
		for(unsigned int i=total; i<total2; i++)
		{
			newStr.characters[i] = str.at(counter);
			counter++;
		}
		newStr.characters[total2] = '\0';
		return newStr;
	}

	String String::operator+(double num) const
	{
		String newStr;
		std::string str = String::doubleToString(num);
		unsigned int total2 = total + str.length();
		newStr.characters = (char*)std::realloc(newStr.characters, total2+1);
		newStr.total = total2;
		for(unsigned int i=0; i<total; i++)
		{
			newStr.characters[i] = characters[i];
		}
		unsigned int counter = 0;
		for(unsigned int i=total; i<total2; i++)
		{
			newStr.characters[i] = str.at(counter);
			counter++;
		}
		newStr.characters[total2] = '\0';
		return newStr;
	}

	String& String::operator+=(const String& str)
	{
		unsigned int total2 = total + str.length();
		characters = (char*)std::realloc(characters, total2+1);
		unsigned int counter = 0;
		for(unsigned int i=total; i<total2; i++)
		{
			characters[i] = str.characters[counter];
			counter++;
		}
		total = total2;
		characters[total2] = '\0';
		return *this;
	}

	String& String::operator+=(const std::string& str)
	{
		unsigned int total2 = total + str.length();
		characters = (char*)std::realloc(characters, total2+1);
		unsigned int counter = 0;
		for(unsigned int i=total; i<total2; i++)
		{
			characters[i] = str.at(counter);
			counter++;
		}
		total = total2;
		characters[total2] = '\0';
		return *this;
	}

	String& String::operator+=(const char*str)
	{
		unsigned int total2 = total + strlen(str);
		characters = (char*)std::realloc(characters, total2+1);
		unsigned int counter = 0;
		for(unsigned int i=total; i<total2; i++)
		{
			characters[i] = str[counter];
			counter++;
		}
		total = total2;
		characters[total2] = '\0';
		return *this;
	}

	String& String::operator+=(const wchar_t*str)
	{
		String str2(str);
		unsigned int total2 = total + str2.length();
		characters = (char*)std::realloc(characters, total2+1);
		unsigned int counter = 0;
		for(unsigned int i=total; i<total2; i++)
		{
			characters[i] = str2.characters[counter];
			counter++;
		}
		total = total2;
		characters[total2] = '\0';
		return *this;
	}

	String& String::operator+=(const std::wstring& str)
	{
		String str2(str);
		unsigned int total2 = total + str2.length();
		characters = (char*)std::realloc(characters, total2+1);
		unsigned int counter = 0;
		for(unsigned int i=total; i<total2; i++)
		{
			characters[i] = str2.characters[counter];
			counter++;
		}
		total = total2;
		characters[total2] = '\0';
		return *this;
	}

	String& String::operator+=(bool b)
	{
		if(b)
		{
			characters = (char*)std::realloc(characters, total+5);
			characters[total]   = 't';
			characters[total+1] = 'r';
			characters[total+2] = 'u';
			characters[total+3] = 'e';
			characters[total+4] = '\0';
			total += 4;
		}
		else
		{
			characters = (char*)std::realloc(characters, total+6);
			characters[total]   = 'f';
			characters[total+1] = 'a';
			characters[total+2] = 'l';
			characters[total+3] = 's';
			characters[total+4] = 'e';
			characters[total+5] = '\0';
			total += 5;
		}
		return *this;
	}

	String& String::operator+=(char c)
	{
		unsigned int total2 = total+1;
		characters = (char*)std::realloc(characters, total2+1);
		characters[total]=c;
		characters[total2]='\0';
		total = total2;
		return *this;
	}

	String& String::operator+=(unsigned char num)
	{
		std::string str2 = String::intToString((int)num);
		unsigned int total2 = total + str2.length();
		characters = (char*)std::realloc(characters, total2+1);
		unsigned int counter = 0;
		for(unsigned int i=total; i<total2; i++)
		{
			characters[i] = str2.at(counter);
			counter++;
		}
		total = total2;
		characters[total2] = '\0';
		return *this;
	}

	String& String::operator+=(int num)
	{
		std::string str2 = String::intToString(num);
		unsigned int total2 = total + str2.length();
		characters = (char*)std::realloc(characters, total2+1);
		unsigned int counter = 0;
		for(unsigned int i=total; i<total2; i++)
		{
			characters[i] = str2.at(counter);
			counter++;
		}
		total = total2;
		characters[total2] = '\0';
		return *this;
	}

	String& String::operator+=(unsigned int num)
	{
		std::string str2 = String::uintToString(num);
		unsigned int total2 = total + str2.length();
		characters = (char*)std::realloc(characters, total2+1);
		unsigned int counter = 0;
		for(unsigned int i=total; i<total2; i++)
		{
			characters[i] = str2.at(counter);
			counter++;
		}
		total = total2;
		characters[total2] = '\0';
		return *this;
	}

	String& String::operator+=(long num)
	{
		std::string str2 = String::longToString(num);
		unsigned int total2 = total + str2.length();
		characters = (char*)std::realloc(characters, total2+1);
		unsigned int counter = 0;
		for(unsigned int i=total; i<total2; i++)
		{
			characters[i] = str2.at(counter);
			counter++;
		}
		total = total2;
		characters[total2] = '\0';
		return *this;
	}

	String& String::operator+=(float num)
	{
		std::string str2 = String::floatToString(num);
		unsigned int total2 = total + str2.length();
		characters = (char*)std::realloc(characters, total2+1);
		unsigned int counter = 0;
		for(unsigned int i=total; i<total2; i++)
		{
			characters[i] = str2.at(counter);
			counter++;
		}
		total = total2;
		characters[total2] = '\0';
		return *this;
	}

	String& String::operator+=(double num)
	{
		std::string str2 = String::doubleToString(num);
		unsigned int total2 = total + str2.length();
		characters = (char*)std::realloc(characters, total2+1);
		unsigned int counter = 0;
		for(unsigned int i=total; i<total2; i++)
		{
			characters[i] = str2.at(counter);
			counter++;
		}
		total = total2;
		characters[total2] = '\0';
		return *this;
	}

	String& String::operator=(const String& str)
	{
		unsigned int total2 = str.length();
		characters = (char*)std::realloc(characters, total2+1);
		total = total2;
		for(unsigned int i=0; i<total2; i++)
		{
			characters[i] = str.characters[i];
		}
		characters[total2] = '\0';
		return *this;
	}

	String& String::operator=(const std::string& str)
	{
		unsigned int total2 = str.length();
		characters = (char*)std::realloc(characters, total2+1);
		total = total2;
		for(unsigned int i=0; i<total2; i++)
		{
			characters[i] = str.at(i);
		}
		characters[total2] = '\0';
		return *this;
	}

	String& String::operator=(const char*str)
	{
		unsigned int total2 = strlen(str);
		characters = (char*)std::realloc(characters, total2+1);
		total = total2;
		for(unsigned int i=0; i<total2; i++)
		{
			characters[i] = str[i];
		}
		characters[total2] = '\0';
		return *this;
	}

	String& String::operator=(const wchar_t*str)
	{
		String str2(str);
		unsigned int total2 = str2.length();
		characters = (char*)std::realloc(characters, total2+1);
		total = total2;
		for(unsigned int i=0; i<total2; i++)
		{
			characters[i] = str2.characters[i];
		}
		characters[total2] = '\0';
		return *this;
	}

	String& String::operator=(const std::wstring& str)
	{
		String str2(str);
		unsigned int total2 = str2.length();
		characters = (char*)std::realloc(characters, total2+1);
		total = total2;
		for(unsigned int i=0; i<total2; i++)
		{
			characters[i] = str2.characters[i];
		}
		characters[total2] = '\0';
		return *this;
	}

	String& String::operator=(bool b)
	{
		if(b)
		{
			characters = (char*)std::realloc(characters, 5);
			characters[0] = 't';
			characters[1] = 'r';
			characters[2] = 'u';
			characters[3] = 'e';
			characters[4] = '\0';
			total = 4;
		}
		else
		{
			characters = (char*)std::realloc(characters, 6);
			characters[0] = 'f';
			characters[1] = 'a';
			characters[2] = 'l';
			characters[3] = 's';
			characters[4] = 'e';
			characters[5] = '\0';
			total = 5;
		}
		return *this;
	}

	String& String::operator=(char c)
	{
		unsigned int total2 = 1;
		characters = (char*)std::realloc(characters, total2+1);
		total = total2;
		characters[0] = c;
		characters[1] = '\0';
		return *this;
	}

	String& String::operator=(unsigned char num)
	{
		std::string str2 = String::intToString((int)num);
		unsigned int total2 = str2.length();
		characters = (char*)std::realloc(characters, total2+1);
		total = total2;
		for(unsigned int i=0; i<total2; i++)
		{
			characters[i] = str2.at(i);
		}
		characters[total2] = '\0';
		return *this;
	}

	String& String::operator=(int num)
	{
		std::string str2 = String::intToString(num);
		unsigned int total2 = str2.length();
		characters = (char*)std::realloc(characters, total2+1);
		total = total2;
		for(unsigned int i=0; i<total2; i++)
		{
			characters[i] = str2.at(i);
		}
		characters[total2] = '\0';
		return *this;
	}

	String& String::operator=(unsigned int num)
	{
		std::string str2 = String::uintToString(num);
		unsigned int total2 = str2.length();
		characters = (char*)std::realloc(characters, total2+1);
		total = total2;
		for(unsigned int i=0; i<total2; i++)
		{
			characters[i] = str2.at(i);
		}
		characters[total2] = '\0';
		return *this;
	}

	String& String::operator=(long num)
	{
		std::string str2 = String::longToString(num);
		unsigned int total2 = str2.length();
		characters = (char*)std::realloc(characters, total2+1);
		total = total2;
		for(unsigned int i=0; i<total2; i++)
		{
			characters[i] = str2.at(i);
		}
		characters[total2] = '\0';
		return *this;
	}

	String& String::operator=(float num)
	{
		std::string str2 = String::floatToString(num);
		unsigned int total2 = str2.length();
		characters = (char*)std::realloc(characters, total2+1);
		total = total2;
		for(unsigned int i=0; i<total2; i++)
		{
			characters[i] = str2.at(i);
		}
		characters[total2] = '\0';
		return *this;
	}

	String& String::operator=(double num)
	{
		std::string str2 = String::doubleToString(num);
		unsigned int total2 = str2.length();
		characters = (char*)std::realloc(characters, total2+1);
		total = total2;
		for(unsigned int i=0; i<total2; i++)
		{
			characters[i] = str2.at(i);
		}
		characters[total2] = '\0';
		return *this;
	}

	bool String::operator==(const String& cmp) const
	{
		return equals(cmp);
	}

	bool String::operator==(const char*cmp) const
	{
		return equals(cmp);
	}

	std::ostream& operator<<(std::ostream& stream, const String& str)
	{
		return stream << str.characters << "";
	}

	bool String::equals(const String& cmp) const
	{
		if(cmp.total==total)
		{
			for(unsigned int i=0; i<total; i++)
			{
				if(characters[i] != cmp.characters[i])
				{
					return false;
				}
			}
			return true;
		}
		return false;
	}

	bool String::equals(const char*cmp) const
	{
		if(cmp!=NULL)
		{
			int cmpLength = std::strlen(cmp);
			if(cmpLength==total)
			{
				for(unsigned int i=0; i<total; i++)
				{
					if(characters[i] != cmp[i])
					{
						return false;
					}
				}
				return true;
			}
			return false;
		}
		return false;
	}

#define STRINGCMP_CHARTYPE_SYMBOL 0
#define STRINGCMP_CHARTYPE_ZERO 1
#define STRINGCMP_CHARTYPE_NUMBER 2
#define STRINGCMP_CHARTYPE_UPPERCASE_LETTER 3
#define STRINGCMP_CHARTYPE_LOWERCASE_LETTER 4

	unsigned char StringCmp_getCharType(const char&c)
	{
		if(c=='0')
		{
			return STRINGCMP_CHARTYPE_ZERO;
		}
		else if(c>='1' && c<='9')
		{
			return STRINGCMP_CHARTYPE_NUMBER;
		}
		else if(c>='A' && c<='Z')
		{
			return STRINGCMP_CHARTYPE_UPPERCASE_LETTER;
		}
		else if(c>='a' && c<='z')
		{
			return STRINGCMP_CHARTYPE_LOWERCASE_LETTER;
		}
		return STRINGCMP_CHARTYPE_SYMBOL;
	}

	int String::compare(const String&cmp) const
	{
		unsigned int amount = 0;
		if(cmp.total>total)
		{
			amount = total;
		}
		else
		{
			amount = cmp.total;
		}
		
		bool hasCap1 = false;
		bool hasCap2 = false;
		
		for(unsigned int i=0; i<amount; i++)
		{
			char c1 = characters[i];
			char c2 = cmp.characters[i];
			
			unsigned char type1 = StringCmp_getCharType(c1);
			unsigned char type2 = StringCmp_getCharType(c2);
			
			if(type1==type2)
			{
				if(c1<c2)
				{
					return 1;
				}
				else if(c2<c1)
				{
					return -1;
				}
			}
			else
			{
				if(type1==STRINGCMP_CHARTYPE_UPPERCASE_LETTER && type2==STRINGCMP_CHARTYPE_LOWERCASE_LETTER)
				{
					char c1mod = c1 - 'A';
					char c2mod = c2 - 'a';
					
					if(c1mod<c2mod)
					{
						return 1;
					}
					else if(c2mod<c1mod)
					{
						return -1;
					}
					else
					{
						if(!hasCap1 && !hasCap2)
						{
							hasCap1 = true;
						}
					}
				}
				else if(type1==STRINGCMP_CHARTYPE_LOWERCASE_LETTER && type2==STRINGCMP_CHARTYPE_UPPERCASE_LETTER)
				{
					char c1mod = c1 - 'a';
					char c2mod = c2 - 'A';
					
					if(c1mod<c2mod)
					{
						return 1;
					}
					else if(c2mod<c1mod)
					{
						return -1;
					}
					else
					{
						if(!hasCap1 && !hasCap2)
						{
							hasCap2 = true;
						}
					}
				}
				else
				{
					if(type1<type2)
					{
						return 1;
					}
					else if(type2<type1)
					{
						return -1;
					}
				}
			}
		}
		
		if(total < cmp.length())
		{
			return 1;
		}
		else if(cmp.length() < total)
		{
			return -1;
		}
		else
		{
			if(hasCap1)
			{
				return 1;
			}
			else if(hasCap2)
			{
				return -1;
			}
			return 0;
		}
	}
	
	void String::clear()
	{
		characters = (char*)std::realloc(characters, 1);
		characters[0] = '\0';
		total = 0;
	}
	
	unsigned int String::length() const
	{
		return total;
	}
	
	char String::charAt(unsigned int index) const
	{
		if(index >= total)
		{
#ifdef STRING_USES_GAMELIBRARY
			throw StringOutOfBoundsException(index, total);
#else
			throw StringException("index " + index + " is out of bounds in String with a length of " + total);
#endif
		}
		return characters[index];
	}
	
	String String::replace(char find, char replace) const
	{
		String replacedStr(*this);
		for(unsigned int i=0; i<total; i++)
		{
			if(replacedStr.characters[i] == find)
			{
				replacedStr.characters[i] = replace;
			}
		}
		return replacedStr;
	}
	
	String String::replace(const String&find, const String&rep) const
	{
		if(find.total==0)
		{
			return *this;
		}
		else if(find.total > total)
		{
			return *this;
		}
		
		std::vector<unsigned int> indexes;
		unsigned int indexTotal = 0;
		
		unsigned int finish = total - find.total;
		
		for(unsigned int i=0; i<=finish; i++)
		{
			if(characters[i]==find.characters[0])
			{
				bool match = true;
				for(unsigned int j=1; j<find.total; j++)
				{
					if(characters[i+j] != find.characters[j])
					{
						match = false;
						j = find.total;
					}
				}
				
				if(match)
				{
					indexes.resize(indexTotal+1);
					indexes[indexTotal] = i;
					indexTotal++;
					i += (find.total-1);
				}
			}
		}
		
		if(indexes.size()>0)
		{
			String newStr(*this);

			bool posDif = false;
			unsigned int dif;
			if(rep.total >= find.total)
			{
				posDif = true;
				dif = rep.total - find.total;
			}
			else
			{
				posDif = false;
				dif = find.total - rep.total;
			}

			unsigned int totalSize = 0;
			if(posDif)
			{
				totalSize = newStr.total + (indexes.size()*dif);
			}
			else
			{
				totalSize = newStr.total - (indexes.size()*dif);
			}
			
			if(rep.total>find.total)
			{
				newStr.characters = (char*)std::realloc(newStr.characters, totalSize+1);
				newStr.characters[totalSize] = '\0';
				
				unsigned int counterNew = totalSize;
				unsigned int counterOld = newStr.total;
				unsigned int lastIndex = newStr.total;

				bool firstLoop = true;
				unsigned int i=(indexes.size()-1);
				while(i > 0 || (firstLoop && i == 0))
				{
					if(!firstLoop)
					{
						i--;
					}

					bool posOffset = false;
					unsigned int offset = 0;
					unsigned int lastIndexEnd = (indexes[i]+find.total);
					if(lastIndex >= lastIndexEnd)
					{
						posOffset = true;
						offset = lastIndex - lastIndexEnd + 1;
					}
					else
					{
						posOffset = false;
						offset = lastIndexEnd - lastIndex + 1;
					}

					lastIndex = indexes[i];
					if(posOffset)
					{
						for(unsigned int j=0; j<offset; j++)
						{
							newStr.characters[counterNew] = newStr.characters[counterOld];
							counterNew--;
							counterOld--;
						}
					}

					counterNew-=(rep.total-1);
					counterOld-=(find.total-1);

					if(i==0 && counterOld!=0)
					{
						bool firstCounterLoop = true;
						while(counterOld>0 || (firstCounterLoop && counterOld==0))
						{
							if(!firstCounterLoop)
							{
								counterNew--;
								counterOld--;
							}

							newStr.characters[counterNew] = newStr.characters[counterOld];
							
							firstCounterLoop = false;
						}
					}

					firstLoop = false;
				}

				newStr.total = totalSize;
			}
			else if(rep.total<find.total)
			{
				unsigned int counterNew = 0;
				unsigned int counterOld = 0;
				unsigned int lastIndex = 0;

				for(unsigned int i=0; i<indexes.size(); i++)
				{
					bool posOffset = false;
					unsigned int offset = 0;
					if(indexes[i]>=lastIndex)
					{
						posOffset = true;
						offset = indexes[i] - lastIndex;
					}
					else
					{
						posOffset = false;
						offset = lastIndex - indexes[i];
					}

					lastIndex = indexes[i] + find.total;

					if(posOffset)
					{
						for(unsigned int j=0; j<offset; j++)
						{
							newStr.characters[counterNew] = newStr.characters[counterOld];
							counterNew++;
							counterOld++;
						}
					}

					counterNew += rep.total;
					counterOld += find.total;

					if(i==(indexes.size()-1) && counterOld<newStr.total)
					{
						while(counterOld<total)
						{
							newStr.characters[counterNew] = newStr.characters[counterOld];
							counterNew++;
							counterOld++;
						}
					}
				}
				
				newStr.characters = (char*)std::realloc(newStr.characters, totalSize+1);
				newStr.characters[totalSize] = '\0';
				newStr.total = totalSize;
			}
			
			unsigned int difCounter = 0;

			for(unsigned int i=0; i<indexes.size(); i++)
			{
				unsigned int offset = 0;
				if(posDif)
				{
					offset = indexes[i] + difCounter;
				}
				else
				{
					offset = indexes[i] - difCounter;
				}

				for(unsigned int j=0; j<rep.total; j++)
				{
					newStr.characters[offset+j] = rep.characters[j];
				}

				difCounter+=dif;
			}
			return newStr;
		}
		return *this;
	}
	
	String String::substring(unsigned int beginIndex) const
	{
		if(beginIndex>total)
		{
#ifdef STRING_USES_GAMELIBRARY
			throw StringOutOfBoundsException(beginIndex, total);
#else
			throw StringException("index " + beginIndex + " is out of bounds in String with a length of " + total);
#endif
		}

		String newStr;
		newStr.characters = (char*)std::realloc(newStr.characters, (total-beginIndex)+1);
		unsigned int counter = 0;
		for(unsigned int i=beginIndex; i<total; i++)
		{
			newStr.characters[counter] = characters[i];
			counter++;
		}
		newStr.characters[counter] = '\0';
		newStr.total = counter;
		return newStr;
	}

	String String::substring(unsigned int beginIndex, unsigned int endIndex) const
	{
		if(beginIndex > total)
		{
#ifdef STRING_USES_GAMELIBRARY
			throw StringOutOfBoundsException(beginIndex, total);
#else
			throw StringException("index " + beginIndex + " is out of bounds in String with a length of " + total);
#endif
		}
		else if(endIndex > total)
		{
#ifdef STRING_USES_GAMELIBRARY
			throw StringOutOfBoundsException(endIndex, total);
#else
			throw StringException("index " + endIndex + " is out of bounds in String with a length of " + total);
#endif
		}

		unsigned int dif = 0;
		bool goUp = true;
		if(beginIndex <= endIndex)
		{
			dif = endIndex - beginIndex;
		}
		else
		{
			goUp = false;
			dif = beginIndex - endIndex;
		}

		String newStr;
		newStr.characters = (char*)std::realloc(newStr.characters, dif+1);
		unsigned int counter = 0;
		if(goUp)
		{
			for(unsigned int i=beginIndex; i<endIndex; i++)
			{
				newStr.characters[counter] = characters[i];
				counter++;
			}
		}
		else
		{
			bool firstLoop = true;
			unsigned int i = endIndex;
			while(i > beginIndex || (firstLoop && i==beginIndex))
			{
				if(!firstLoop)
				{
					i--;
				}
				newStr.characters[counter] = characters[i];
				counter++;
				firstLoop = false;
			}
		}
		newStr.characters[counter] = '\0';
		newStr.total = counter;
		return newStr;
	}

	String String::trim() const
	{
		if(total == 0)
		{
			return *this;
		}

		unsigned int i=0;
		
		unsigned int startIndex = 0;
		
		bool hitLetter = false;
		
		while(!hitLetter && i<total)
		{
			char c = charAt(i);
			
			if(c>' ')
			{
				startIndex = i;
				hitLetter = true;
			}
			
			i++;
		}
		
		if(!hitLetter)
		{
			return String("");
		}
		
		hitLetter = false;
		i = total-1;
		
		unsigned int endIndex = 0;
		
		bool firstLoop = true;
		while(!hitLetter && (i>0 || (firstLoop && i==0)))
		{
			if(firstLoop)
			{
				i--;
			}

			char c = charAt(i);

			if(c>' ')
			{
				endIndex = i+1;
				hitLetter = true;
			}

			firstLoop = false;
		}

		return substring(startIndex, endIndex);
	}

	unsigned int String::indexOf(const String&str) const
	{
		if(str.total==0 || str.total>total)
		{
			return STRING_NOTFOUND;
		}
		
		unsigned int finish = total - str.total;
		
		for(unsigned int i=0; i<=finish; i++)
		{
			if(characters[i]==str.characters[0])
			{
				bool match = true;
				for(unsigned int j=1; j<str.total; j++)
				{
					if(characters[i+j] != str.characters[j])
					{
						match = false;
						j = str.total;
					}
				}
				
				if(match)
				{
					return i;
				}
			}
		}
		return STRING_NOTFOUND;
	}

	unsigned int String::lastIndexOf(const String&str) const
	{
		if(str.total==0 || str.total>total)
		{
			return STRING_NOTFOUND;
		}
		
		unsigned int finish = (str.total-1);
		
		for(unsigned int i=(total-1); i>=finish; i--)
		{
			if(characters[i]==str.characters[str.total-1])
			{
				bool match = true;
				for(unsigned int j=1; j<str.total; j++)
				{
					if(characters[i-j] != str.characters[(str.total-1)-j])
					{
						match = false;
						j = str.total;
					}
				}
				
				if(match)
				{
					return (i-(str.total-1));
				}
			}
			
			if(i == 0)
			{
				return STRING_NOTFOUND;
			}
		}
		return STRING_NOTFOUND;
	}

	String String::toLowerCase() const
	{
		String newStr(*this);
		
		for(unsigned int i=0; i<total; i++)
		{
			char c = newStr.characters[i];
			if(c>='A' && c<='Z')
			{
				c = (char)((c-'A')+'a');
			}
			newStr.characters[i] = c;
		}
		
		return newStr;
	}

	String String::toUpperCase() const
	{
		String newStr(*this);
		
		for(unsigned int i=0; i<total; i++)
		{
			char c = newStr.characters[i];
			if(c>='a' && c<='z')
			{
				c = (char)((c-'a')+'A');
			}
			newStr.characters[i] = c;
		}
		
		return newStr;
	}
#ifdef STRING_USES_GAMELIBRARY
}
#endif