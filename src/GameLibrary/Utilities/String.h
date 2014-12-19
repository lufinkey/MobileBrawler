
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
		//String
		friend String operator+(const String&left, const String&right);
		//std::string
		friend String operator+(const String&left, const std::string&right);
		friend String operator+(const std::string&left, const String&right);
		//const std::wstring
		friend String operator+(const String&left, const std::wstring&right);
		friend String operator+(const std::wstring&left, const String&right);
		//const char*
		friend String operator+(const String&left, const char*right);
		friend String operator+(const char*left, const String&right);
		//const wchar_t*
		friend String operator+(const String&left, const wchar_t*right);
		friend String operator+(const wchar_t*left, const String&right);
		//bool
		friend String operator+(const String&left, const bool&right);
		friend String operator+(const bool&left, const String&right);
		//char
		friend String operator+(const String&left, const char&right);
		friend String operator+(const char&left, const String&right);
		//unsigned char
		friend String operator+(const String&left, const unsigned char&right);
		friend String operator+(const unsigned char&left, const String&right);
		//short
		friend String operator+(const String&left, const short&right);
		friend String operator+(const short&left, const String&right);
		//unsigned short
		friend String operator+(const String&left, const unsigned short&right);
		friend String operator+(const unsigned short&left, const String&right);
		//int
		friend String operator+(const String&left, const int&right);
		friend String operator+(const int&left, const String&right);
		//unsigned int
		friend String operator+(const String&left, const unsigned int&right);
		friend String operator+(const unsigned int&left, const String&right);
		//long
		friend String operator+(const String&left, const long&right);
		friend String operator+(const long&left, const String&right);
		//unsigned long
		friend String operator+(const String&left, const unsigned long&right);
		friend String operator+(const unsigned long&left, const String&right);
		//long long
		friend String operator+(const String&left, const long long&right);
		friend String operator+(const long long&left, const String&right);
		//unsigned long long
		friend String operator+(const String&left, const unsigned long long&right);
		friend String operator+(const unsigned long long&left, const String&right);
		//float
		friend String operator+(const String&left, const float&right);
		friend String operator+(const float&left, const String&right);
		//double
		friend String operator+(const String&left, const double&right);
		friend String operator+(const double&left, const String&right);
		//long double
		friend String operator+(const String&left, const long double&right);
		friend String operator+(const long double&left, const String&right);
	private:
		char*characters;
		unsigned int total;
		
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
		String(const std::wstring&);
		String(const char*);
		String(const wchar_t*);
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
		
		String& operator+=(const String&);
		String& operator+=(const std::string&);
		String& operator+=(const std::wstring&);
		String& operator+=(const char*);
		String& operator+=(const wchar_t*);
		String& operator+=(bool);
		String& operator+=(char);
		String& operator+=(unsigned char);
		String& operator+=(short);
		String& operator+=(unsigned short);
		String& operator+=(int);
		String& operator+=(unsigned int);
		String& operator+=(long);
		String& operator+=(unsigned long);
		String& operator+=(long long);
		String& operator+=(unsigned long long);
		String& operator+=(float);
		String& operator+=(double);
		String& operator+=(long double);
		
		String& operator=(const String&);
		String& operator=(const std::string&);
		String& operator=(const std::wstring&);
		String& operator=(const char*);
		String& operator=(const wchar_t*);
		String& operator=(bool);
		String& operator=(char);
		String& operator=(unsigned char);
		String& operator=(short);
		String& operator=(unsigned short);
		String& operator=(int);
		String& operator=(unsigned int);
		String& operator=(long);
		String& operator=(unsigned long);
		String& operator=(long long);
		String& operator=(unsigned long long);
		String& operator=(float);
		String& operator=(double);
		String& operator=(long double);

		bool operator<(const String&) const;
		bool operator<=(const String&) const;
		bool operator>(const String&) const;
		bool operator>=(const String&) const;
		
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

	//String
	String operator+(const String&left, const String&right);
	//std::string
	String operator+(const String&left, const std::string&right);
	String operator+(const std::string&left, const String&right);
	//const std::wstring
	String operator+(const String&left, const std::wstring&right);
	String operator+(const std::wstring&left, const String&right);
	//const char*
	String operator+(const String&left, const char*right);
	String operator+(const char*left, const String&right);
	//const wchar_t*
	String operator+(const String&left, const wchar_t*right);
	String operator+(const wchar_t*left, const String&right);
	//bool
	String operator+(const String&left, const bool&right);
	String operator+(const bool&left, const String&right);
	//char
	String operator+(const String&left, const char&right);
	String operator+(const char&left, const String&right);
	//unsigned char
	String operator+(const String&left, const unsigned char&right);
	String operator+(const unsigned char&left, const String&right);
	//short
	String operator+(const String&left, const short&right);
	String operator+(const short&left, const String&right);
	//unsigned short
	String operator+(const String&left, const unsigned short&right);
	String operator+(const unsigned short&left, const String&right);
	//int
	String operator+(const String&left, const int&right);
	String operator+(const int&left, const String&right);
	//unsigned int
	String operator+(const String&left, const unsigned int&right);
	String operator+(const unsigned int&left, const String&right);
	//long
	String operator+(const String&left, const long&right);
	String operator+(const long&left, const String&right);
	//unsigned long
	String operator+(const String&left, const unsigned long&right);
	String operator+(const unsigned long&left, const String&right);
	//long long
	String operator+(const String&left, const long long&right);
	String operator+(const long long&left, const String&right);
	//unsigned long long
	String operator+(const String&left, const unsigned long long&right);
	String operator+(const unsigned long long&left, const String&right);
	//float
	String operator+(const String&left, const float&right);
	String operator+(const float&left, const String&right);
	//double
	String operator+(const String&left, const double&right);
	String operator+(const double&left, const String&right);
	//long double
	String operator+(const String&left, const long double&right);
	String operator+(const long double&left, const String&right);
}
#endif


