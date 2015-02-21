
#pragma once

#include "../Exception/Utilities/IllegalNumberOperationException.h"
#include "../Utilities/String.h"

namespace GameLibrary
{
	class Number;
	class _BaseNumberType;
	
	//TODO add equality operators
#define _NUMBER_OPERATOR_DECLARE(prefix, type, operatr) \
	prefix Number operator operatr(const Number&left, const type&right); \
	prefix type operator operatr(const type&left, const Number&right);
	
#define _NUMBER_COMPARISON_DECLARE(prefix, type, operatr) \
	prefix bool operator operatr(const Number&left, const type&right); \
	prefix bool operator operatr(const type&left, const Number&right);
	
#define _NUMBER_COMPARISON_DECLARE_SET(prefix, type) \
	_NUMBER_COMPARISON_DECLARE(prefix, type, ==) \
	_NUMBER_COMPARISON_DECLARE(prefix, type, !=) \
	_NUMBER_COMPARISON_DECLARE(prefix, type, >) \
	_NUMBER_COMPARISON_DECLARE(prefix, type, >=) \
	_NUMBER_COMPARISON_DECLARE(prefix, type, <) \
	_NUMBER_COMPARISON_DECLARE(prefix, type, <=)
	
#define _NUMBER_OPERATOR_DECLARE_SET(prefix, type) \
	_NUMBER_OPERATOR_DECLARE(prefix, type, +) \
	_NUMBER_OPERATOR_DECLARE(prefix, type, -) \
	_NUMBER_OPERATOR_DECLARE(prefix, type, *) \
	_NUMBER_OPERATOR_DECLARE(prefix, type, /) \
	_NUMBER_OPERATOR_DECLARE(prefix, type, %) \
	_NUMBER_COMPARISON_DECLARE_SET(prefix, type)
	
#define _NUMBER_OPERATOR_DECLARE_SET_FLOATINGPOINT(prefix, type) \
	_NUMBER_OPERATOR_DECLARE(prefix, type, +) \
	_NUMBER_OPERATOR_DECLARE(prefix, type, -) \
	_NUMBER_OPERATOR_DECLARE(prefix, type, *) \
	_NUMBER_OPERATOR_DECLARE(prefix, type, /) \
	prefix type operator%(const type&left, const Number&right); \
	_NUMBER_COMPARISON_DECLARE_SET(prefix, type)
	
	Number operator+(const Number&left, const Number&right);
	Number operator-(const Number&left, const Number&right);
	Number operator*(const Number&left, const Number&right);
	Number operator/(const Number&left, const Number&right);
	Number operator%(const Number&left, const Number&right);
	String operator+(const Number&left, const String&right);
	String operator+(const String&left, const Number&right);
	bool operator==(const Number&left, const Number&right);
	bool operator!=(const Number&left, const Number&right);
	bool operator<(const Number&left, const Number&right);
	bool operator<=(const Number&left, const Number&right);
	bool operator>(const Number&left, const Number&right);
	bool operator>=(const Number&left, const Number&right);
	
	_NUMBER_COMPARISON_DECLARE_SET(, bool)
	_NUMBER_OPERATOR_DECLARE_SET(, char)
	_NUMBER_OPERATOR_DECLARE_SET(, unsigned char)
	_NUMBER_OPERATOR_DECLARE_SET(, short)
	_NUMBER_OPERATOR_DECLARE_SET(, unsigned short)
	_NUMBER_OPERATOR_DECLARE_SET(, int)
	_NUMBER_OPERATOR_DECLARE_SET(, unsigned int)
	_NUMBER_OPERATOR_DECLARE_SET(, long)
	_NUMBER_OPERATOR_DECLARE_SET(, unsigned long)
	_NUMBER_OPERATOR_DECLARE_SET(, long long)
	_NUMBER_OPERATOR_DECLARE_SET(, unsigned long long)
	_NUMBER_OPERATOR_DECLARE_SET_FLOATINGPOINT(, float)
	_NUMBER_OPERATOR_DECLARE_SET_FLOATINGPOINT(, double)
	_NUMBER_OPERATOR_DECLARE_SET_FLOATINGPOINT(, long double)
	
	class Number
	{
		friend std::ostream& operator<<(std::ostream& stream, const Number& num);
		_NUMBER_COMPARISON_DECLARE_SET(friend, bool)
		_NUMBER_OPERATOR_DECLARE_SET(friend, char)
		_NUMBER_OPERATOR_DECLARE_SET(friend, unsigned char)
		_NUMBER_OPERATOR_DECLARE_SET(friend, short)
		_NUMBER_OPERATOR_DECLARE_SET(friend, unsigned short)
		_NUMBER_OPERATOR_DECLARE_SET(friend, int)
		_NUMBER_OPERATOR_DECLARE_SET(friend, unsigned int)
		_NUMBER_OPERATOR_DECLARE_SET(friend, long)
		_NUMBER_OPERATOR_DECLARE_SET(friend, unsigned long)
		_NUMBER_OPERATOR_DECLARE_SET(friend, long long)
		_NUMBER_OPERATOR_DECLARE_SET(friend, unsigned long long)
		_NUMBER_OPERATOR_DECLARE_SET_FLOATINGPOINT(friend, float)
		_NUMBER_OPERATOR_DECLARE_SET_FLOATINGPOINT(friend, double)
		_NUMBER_OPERATOR_DECLARE_SET_FLOATINGPOINT(friend, long double)
		friend Number operator+(const Number&left, const Number&right);
		friend Number operator-(const Number&left, const Number&right);
		friend Number operator*(const Number&left, const Number&right);
		friend Number operator/(const Number&left, const Number&right);
		friend Number operator%(const Number&left, const Number&right);
		friend String operator+(const Number&left, const String&right);
		friend String operator+(const String&left, const Number&right);
		friend bool operator==(const Number&left, const Number&right);
		friend bool operator!=(const Number&left, const Number&right);
		friend bool operator<(const Number&left, const Number&right);
		friend bool operator<=(const Number&left, const Number&right);
		friend bool operator>(const Number&left, const Number&right);
		friend bool operator>=(const Number&left, const Number&right);
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
		
		Number& operator+=(const Number&);
		Number& operator-=(const Number&);
		Number& operator*=(const Number&);
		Number& operator/=(const Number&);
		Number& operator%=(const Number&);
		
		Number& operator++();
		Number& operator--();
		
		Number operator-() const;
		
		bool isIntegral() const;
		Number::NumberType getType() const;
		
		operator bool() const;
		operator char() const;
		operator unsigned char() const;
		operator short() const;
		operator unsigned short() const;
		operator int() const;
		operator unsigned int() const;
		operator long() const;
		operator unsigned long() const;
		operator long long() const;
		operator unsigned long long() const;
		operator float() const;
		operator double() const;
		operator long double() const;
		
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
		String asString() const;
		
	private:
		_BaseNumberType* value;
	};
	
	std::ostream& operator<<(std::ostream& stream, const Number& num);
	
	#undef _NUMBER_OPERATOR_DECLARE_SET_FLOATINGPOINT
	#undef _NUMBER_OPERATOR_DECLARE_SET
	#undef _NUMBER_COMPARISON_DECLARE
	#undef _NUMBER_OPERATOR_DECLARE
}
