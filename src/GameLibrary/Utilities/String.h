
#include <climits>
#include <string>

#pragma once

#define STRING_USES_GAMELIBRARY

#ifdef STRING_USES_GAMELIBRARY
namespace GameLibrary
{
#else
	#include <exception>
	
	class StringException : public std::exception
	{
	private:
		std::string message;

	public:
		StringException(const StringException&);
		StringException(const std::string&reason);
		virtual ~StringException();
		virtual const char* what() const;
	};
#endif

#define STRING_NOTFOUND UINT_MAX
	
	class String
	{
		friend std::ostream& operator<<(std::ostream& stream, const String& str);
	private:
		char*characters;
		unsigned int total;
		
		static std::string intToString(int);
		static std::string uintToString(unsigned int);
		static std::string floatToString(float);
		static std::string doubleToString(double);
		static std::string longToString(long);
		
	public:
		static bool asBool(const String&);
		static int asInt(const String&);
		static long asLong(const String&);
		static short asShort(const String&);
		static float asFloat(const String&);
		static double asDouble(const String&);
		static long long asLongLong(const String&);
		static unsigned int asUInt(const String&);
		static unsigned char asUChar(const String&);
		static unsigned long asULong(const String&);
		static unsigned short asUShort(const String&);
		static unsigned long long asULongLong(const String&);

		static char asLowerCaseChar(char c);
		static char asUpperCaseChar(char c);
		
		String();
		String(const String&);
		String(const std::string&);
		String(const char*);
		String(const wchar_t*);
		String(const std::wstring&);
		String(bool);
		String(char);
		String(unsigned char);
		String(int);
		String(unsigned int);
		String(float);
		String(double);
		String(long);
		virtual ~String();

		std::wstring wstring() const;
		
		operator char*();
		operator const char*();
		operator std::string();
		operator std::wstring();
		operator char*() const;
		operator const char*() const;
		operator std::string() const;
		operator std::wstring() const;
		
		String operator+(const String&) const;
		String operator+(const std::string&) const;
		String operator+(const char*) const;
		String operator+(const wchar_t*) const;
		String operator+(const std::wstring&) const;
		String operator+(bool) const;
		String operator+(char) const;
		String operator+(unsigned char) const;
		String operator+(int) const;
		String operator+(unsigned int) const;
		String operator+(long) const;
		String operator+(float) const;
		String operator+(double) const;
		
		String& operator+=(const String&);
		String& operator+=(const std::string&);
		String& operator+=(const char*);
		String& operator+=(const wchar_t*);
		String& operator+=(const std::wstring&);
		String& operator+=(bool);
		String& operator+=(char);
		String& operator+=(unsigned char);
		String& operator+=(int);
		String& operator+=(unsigned int);
		String& operator+=(long);
		String& operator+=(float);
		String& operator+=(double);
		
		String& operator=(const String&);
		String& operator=(const std::string&);
		String& operator=(const char*);
		String& operator=(const wchar_t*);
		String& operator=(const std::wstring&);
		String& operator=(bool);
		String& operator=(char);
		String& operator=(unsigned char);
		String& operator=(int);
		String& operator=(unsigned int);
		String& operator=(long);
		String& operator=(float);
		String& operator=(double);
		
		bool operator==(const String&) const;
		bool operator==(const char*) const;
		
		bool equals(const String&) const;
		bool equals(const char*) const;
		
		int compare(const String&) const;
		
		void clear();
		unsigned int length() const;
		char charAt(unsigned int index) const;
		String replace(char find, char replace) const;
		String replace(const String&find, const String&rep) const;
		String substring(unsigned int beginIndex) const;
		String substring(unsigned int beginIndex, unsigned int endIndex) const;
		String trim() const;
		unsigned int indexOf(char) const;
		unsigned int indexOf(const String&) const;
		unsigned int lastIndexOf(char) const;
		unsigned int lastIndexOf(const String&) const;
		String toLowerCase() const;
		String toUpperCase() const;
	};
#ifdef STRING_USES_GAMELIBRARY
}
#endif


