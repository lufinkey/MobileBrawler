
#pragma once

#include "../Exception/Utilities/IllegalNumberOperationException.h"

namespace GameLibrary
{
	class _BaseNumberType;
	
	class Number
	{
	public:
		typedef enum
		{
			TYPE_NULL,
			TYPE_BOOL,
			TYPE_CHAR,
			TYPE_UNSIGNEDCHAR,
			TYPE_SHORT,
			TYPE_UNSIGNEDSHORT,
			TYPE_INT,
			TYPE_UNSIGNEDINT,
			TYPE_LONG,
			TYPE_UNSIGNEDLONG,
			TYPE_LONGLONG,
			TYPE_UNSIGNEDLONGLONG,
			TYPE_FLOAT,
			TYPE_DOUBLE,
			TYPE_LONGDOUBLE
		} NumberType;
		
		Number();
		Number(const bool&);
		Number(const char&);
		Number(const unsigned char&);
		Number(const short&);
		Number(const unsigned short&);
		Number(const int&);
		Number(const unsigned int&);
		Number(const long&);
		Number(const unsigned long&);
		Number(const long long&);
		Number(const unsigned long long&);
		Number(const float&);
		Number(const double&);
		Number(const long double&);
		Number(const Number&);
		~Number();
		
		Number& operator=(const Number&);
		
		Number operator+(const Number&) const;
		Number operator-(const Number&) const;
		Number operator*(const Number&) const;
		Number operator/(const Number&) const;
		Number operator%(const Number&) const;
		
		Number& operator+=(const Number&);
		Number& operator-=(const Number&);
		Number& operator*=(const Number&);
		Number& operator/=(const Number&);
		Number& operator%=(const Number&);
		
		bool asBool() const;
		char asChar() const;
		unsigned char asUnsignedChar() const;
		short asShort() const;
		unsigned short asUnsignedShort() const;
		int asInt() const;
		unsigned int asUnsignedInt() const;
		long asLong() const;
		unsigned long asUnsignedLong() const;
		long long asLongLong() const;
		unsigned long long asUnsignedLongLong() const;
		float asFloat() const;
		double asDouble() const;
		long double asLongDouble() const;
		
	private:
		_BaseNumberType* value;
	};
	
	/*//bool
	Number operator+(const Number&left, const bool&right);
	bool operator+(const bool&left, const Number&right);
	Number operator-(const Number&left, const bool&right);
	bool operator-(const bool&left, const Number&right);
	Number operator*(const Number&left, const bool&right);
	bool operator*(const bool&left, const Number&right);
	Number operator/(const Number&left, const bool&right);
	bool operator/(const bool&left, const Number&right);
	Number operator%(const Number&left, const bool&right);
	bool operator%(const bool&left, const Number&right);*/
	
	Number operator+(const Number&left, const Number&right);
	Number operator-(const Number&left, const Number&right);
	Number operator*(const Number&left, const Number&right);
	Number operator/(const Number&left, const Number&right);
	Number operator%(const Number&left, const Number&right);
	
	//char
	Number operator+(const Number&left, const char&right);
	char operator+(const char&left, const Number&right);
	Number operator-(const Number&left, const char&right);
	char operator-(const char&left, const Number&right);
	Number operator*(const Number&left, const char&right);
	char operator*(const char&left, const Number&right);
	Number operator/(const Number&left, const char&right);
	char operator/(const char&left, const Number&right);
	Number operator%(const Number&left, const char&right);
	char operator%(const char&left, const Number&right);
	
	//unsigned char
	Number operator+(const Number&left, const unsigned char&right);
	unsigned char operator+(const unsigned char&left, const Number&right);
	Number operator-(const Number&left, const unsigned char&right);
	unsigned char operator-(const unsigned char&left, const Number&right);
	Number operator*(const Number&left, const unsigned char&right);
	unsigned char operator*(const unsigned char&left, const Number&right);
	Number operator/(const Number&left, const unsigned char&right);
	unsigned char operator/(const unsigned char&left, const Number&right);
	Number operator%(const Number&left, const unsigned char&right);
	unsigned char operator%(const unsigned char&left, const Number&right);
	
	//short
	Number operator+(const Number&left, const short&right);
	short operator+(const short&left, const Number&right);
	Number operator-(const Number&left, const short&right);
	short operator-(const short&left, const Number&right);
	Number operator*(const Number&left, const short&right);
	short operator*(const short&left, const Number&right);
	Number operator/(const Number&left, const short&right);
	short operator/(const short&left, const Number&right);
	Number operator%(const Number&left, const short&right);
	short operator%(const short&left, const Number&right);
	
	//unsigned short
	Number operator+(const Number&left, const unsigned short&right);
	unsigned short operator+(const unsigned short&left, const Number&right);
	Number operator-(const Number&left, const unsigned short&right);
	unsigned short operator-(const unsigned short&left, const Number&right);
	Number operator*(const Number&left, const unsigned short&right);
	unsigned short operator*(const unsigned short&left, const Number&right);
	Number operator/(const Number&left, const unsigned short&right);
	unsigned short operator/(const unsigned short&left, const Number&right);
	Number operator%(const Number&left, const unsigned short&right);
	unsigned short operator%(const unsigned short&left, const Number&right);
	
	//int
	Number operator+(const Number&left, const int&right);
	int operator+(const int&left, const Number&right);
	Number operator-(const Number&left, const int&right);
	int operator-(const int&left, const Number&right);
	Number operator*(const Number&left, const int&right);
	int operator*(const int&left, const Number&right);
	Number operator/(const Number&left, const int&right);
	int operator/(const int&left, const Number&right);
	Number operator%(const Number&left, const int&right);
	int operator%(const int&left, const Number&right);
	
	//unsigned int
	Number operator+(const Number&left, const unsigned int&right);
	unsigned int operator+(const unsigned int&left, const Number&right);
	Number operator-(const Number&left, const unsigned int&right);
	unsigned int operator-(const unsigned int&left, const Number&right);
	Number operator*(const Number&left, const unsigned int&right);
	unsigned int operator*(const unsigned int&left, const Number&right);
	Number operator/(const Number&left, const unsigned int&right);
	unsigned int operator/(const unsigned int&left, const Number&right);
	Number operator%(const Number&left, const unsigned int&right);
	unsigned int operator%(const unsigned int&left, const Number&right);
	
	//long
	Number operator+(const Number&left, const long&right);
	long operator+(const long&left, const Number&right);
	Number operator-(const Number&left, const long&right);
	long operator-(const long&left, const Number&right);
	Number operator*(const Number&left, const long&right);
	long operator*(const long&left, const Number&right);
	Number operator/(const Number&left, const long&right);
	long operator/(const long&left, const Number&right);
	Number operator%(const Number&left, const long&right);
	long operator%(const long&left, const Number&right);
	
	//unsigned long
	Number operator+(const Number&left, const unsigned long&right);
	unsigned long operator+(const unsigned long&left, const Number&right);
	Number operator-(const Number&left, const unsigned long&right);
	unsigned long operator-(const unsigned long&left, const Number&right);
	Number operator*(const Number&left, const unsigned long&right);
	unsigned long operator*(const unsigned long&left, const Number&right);
	Number operator/(const Number&left, const unsigned long&right);
	unsigned long operator/(const unsigned long&left, const Number&right);
	Number operator%(const Number&left, const unsigned long&right);
	unsigned long operator%(const unsigned long&left, const Number&right);
	
	//long long
	Number operator+(const Number&left, const long long&right);
	long long operator+(const long long&left, const Number&right);
	Number operator-(const Number&left, const long long&right);
	long long operator-(const long long&left, const Number&right);
	Number operator*(const Number&left, const long long&right);
	long long operator*(const long long&left, const Number&right);
	Number operator/(const Number&left, const long long&right);
	long long operator/(const long long&left, const Number&right);
	Number operator%(const Number&left, const long long&right);
	long long operator%(const long long&left, const Number&right);
	
	//unsigned long long
	Number operator+(const Number&left, const unsigned long long&right);
	unsigned long long operator+(const unsigned long long&left, const Number&right);
	Number operator-(const Number&left, const unsigned long long&right);
	unsigned long long operator-(const unsigned long long&left, const Number&right);
	Number operator*(const Number&left, const unsigned long long&right);
	unsigned long long operator*(const unsigned long long&left, const Number&right);
	Number operator/(const Number&left, const unsigned long long&right);
	unsigned long long operator/(const unsigned long long&left, const Number&right);
	Number operator%(const Number&left, const unsigned long long&right);
	unsigned long long operator%(const unsigned long long&left, const Number&right);
	
	//float
	Number operator+(const Number&left, const float&right);
	float operator+(const float&left, const Number&right);
	Number operator-(const Number&left, const float&right);
	float operator-(const float&left, const Number&right);
	Number operator*(const Number&left, const float&right);
	float operator*(const float&left, const Number&right);
	Number operator/(const Number&left, const float&right);
	float operator/(const float&left, const Number&right);
	//Number operator%(const Number&left, const float&right);
	float operator%(const float&left, const Number&right);
	
	//double
	Number operator+(const Number&left, const double&right);
	double operator+(const double&left, const Number&right);
	Number operator-(const Number&left, const double&right);
	double operator-(const double&left, const Number&right);
	Number operator*(const Number&left, const double&right);
	double operator*(const double&left, const Number&right);
	Number operator/(const Number&left, const double&right);
	double operator/(const double&left, const Number&right);
	//Number operator%(const Number&left, const double&right);
	double operator%(const double&left, const Number&right);
	
	//long double
	Number operator+(const Number&left, const long double&right);
	long double operator+(const long double&left, const Number&right);
	Number operator-(const Number&left, const long double&right);
	long double operator-(const long double&left, const Number&right);
	Number operator*(const Number&left, const long double&right);
	long double operator*(const long double&left, const Number&right);
	Number operator/(const Number&left, const long double&right);
	long double operator/(const long double&left, const Number&right);
	//Number operator%(const Number&left, const long double&right);
	long double operator%(const long double&left, const Number&right);
}
