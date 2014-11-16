
#include <limits.h>
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

#define STRING_NOTFOUND std::numeric_limits<unsigned int>::max()

	class String
	{
		friend std::ostream& operator<<(std::ostream& stream, const String& str);
	private:
		char*characters;
		unsigned int total;
		
		static std::string intToString(int num);
		static std::string uintToString(unsigned int num);
		static std::string floatToString(float num);
		static std::string doubleToString(double num);
		static std::string longToString(long num);
		
	public:
		static bool asBool(const String&str);
		static int asInt(const String&str);
		static long asLong(const String&str);
		static short asShort(const String&str);
		static float asFloat(const String&str);
		static double asDouble(const String&str);
		static long long asLongLong(const String&str);
		static unsigned int asUInt(const String&str);
		static unsigned char asUChar(const String&str);
		static unsigned long asULong(const String&str);
		static unsigned short asUShort(const String&str);
		static unsigned long long asULongLong(const String&str);
		
		String();
		String(const String& str);
		String(const std::string&str);
		String(const char*str);
		String(const wchar_t*str);
		String(const std::wstring&str);
		String(bool b);
		String(char c);
		String(unsigned char num);
		String(int num);
		String(unsigned int num);
		String(float num);
		String(double num);
		String(long num);
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
		
		String operator+(const String& str) const;
		String operator+(const std::string& str) const;
		String operator+(const char*str) const;
		String operator+(const wchar_t*str) const;
		String operator+(const std::wstring& str) const;
		String operator+(bool b) const;
		String operator+(char c) const;
		String operator+(unsigned char num) const;
		String operator+(int num) const;
		String operator+(unsigned int num) const;
		String operator+(long num) const;
		String operator+(float num) const;
		String operator+(double num) const;
		
		String& operator+=(const String& str);
		String& operator+=(const std::string& str);
		String& operator+=(const char*str);
		String& operator+=(const wchar_t*str);
		String& operator+=(const std::wstring& str);
		String& operator+=(bool b);
		String& operator+=(char c);
		String& operator+=(unsigned char num);
		String& operator+=(int num);
		String& operator+=(unsigned int num);
		String& operator+=(long num);
		String& operator+=(float num);
		String& operator+=(double num);
		
		String& operator=(const String& str);
		String& operator=(const std::string& str);
		String& operator=(const char*str);
		String& operator=(const wchar_t*str);
		String& operator=(const std::wstring& str);
		String& operator=(bool b);
		String& operator=(char c);
		String& operator=(unsigned char num);
		String& operator=(int num);
		String& operator=(unsigned int num);
		String& operator=(long num);
		String& operator=(float num);
		String& operator=(double num);
		
		bool operator==(const String& cmp) const;
		bool operator==(const char*cmp) const;
		
		bool equals(const String& cmp) const;
		bool equals(const char*cmp) const;
		
		int compare(const String& cmp) const;
		
		void clear();
		unsigned int length() const;
		char charAt(unsigned int index) const;
		String replace(char find, char replace) const;
		String replace(const String&find, const String&rep) const;
		String substring(unsigned int beginIndex) const;
		String substring(unsigned int beginIndex, unsigned int endIndex) const;
		String trim() const;
		unsigned int indexOf(const String&str) const;
		unsigned int lastIndexOf(const String&str) const;
		String toLowerCase();
		String toUpperCase();
	};
#ifdef STRING_USES_GAMELIBRARY
}
#endif


