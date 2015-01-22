
#include "Number.h"

#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable : 4800)
#pragma warning(disable : 4804)
#pragma warning(disable : 4244)
#endif

namespace GameLibrary
{
#define NULL_STRING "(null)"
	
	class _BaseNumberType
	{
	public:
		Number::NumberType type;
		
		virtual _BaseNumberType* clone() const = 0;
		
		virtual Number operator+(const _BaseNumberType&) const = 0;
		virtual Number operator-(const _BaseNumberType&) const = 0;
		virtual Number operator*(const _BaseNumberType&) const = 0;
		virtual Number operator/(const _BaseNumberType&) const = 0;
		virtual Number operator%(const _BaseNumberType&) const = 0;
		
		virtual _BaseNumberType& operator+=(const _BaseNumberType&) = 0;
		virtual _BaseNumberType& operator-=(const _BaseNumberType&) = 0;
		virtual _BaseNumberType& operator*=(const _BaseNumberType&) = 0;
		virtual _BaseNumberType& operator/=(const _BaseNumberType&) = 0;
		virtual _BaseNumberType& operator%=(const _BaseNumberType&) = 0;
		
		virtual bool isIntegral() const = 0;
		
		virtual bool asBool() const = 0;
		virtual char asChar() const = 0;
		virtual unsigned char asUnsignedChar() const = 0;
		virtual short asShort() const = 0;
		virtual unsigned short asUnsignedShort() const = 0;
		virtual int asInt() const = 0;
		virtual unsigned int asUnsignedInt() const = 0;
		virtual long asLong() const = 0;
		virtual unsigned long asUnsignedLong() const = 0;
		virtual long long asLongLong() const = 0;
		virtual unsigned long long asUnsignedLongLong() const = 0;
		virtual float asFloat() const = 0;
		virtual double asDouble() const = 0;
		virtual long double asLongDouble() const = 0;
		virtual String asString() const = 0;
	};
	
	template<typename T>
	class _DerivedNumberType : public _BaseNumberType
	{
	public:
		T value;

		_DerivedNumberType(const T&val, const Number::NumberType&tp) : value(val) {type = tp;}
		
		virtual _BaseNumberType* clone() const
		{
			return (_BaseNumberType*)(new _DerivedNumberType<T>(value, type));
		}
		
		virtual _BaseNumberType& operator+=(const _BaseNumberType&num)
		{
			if(type == Number::TYPE_BOOL)
			{
				throw IllegalNumberOperationException("+=", "bool", "left");
			}
			switch(num.type)
			{
				default:
				case Number::TYPE_NULL:
				break;
				
				case Number::TYPE_BOOL:
				//value += ((_DerivedNumberType<bool>*)&num)->value;
				throw IllegalNumberOperationException("+=", "bool", "right");
				break;
				
				case Number::TYPE_CHAR:
				value += ((_DerivedNumberType<char>*)&num)->value;
				break;
				
				case Number::TYPE_UNSIGNEDCHAR:
				value += ((_DerivedNumberType<unsigned char>*)&num)->value;
				break;
				
				case Number::TYPE_SHORT:
				value += ((_DerivedNumberType<short>*)&num)->value;
				break;
				
				case Number::TYPE_UNSIGNEDSHORT:
				value += ((_DerivedNumberType<unsigned short>*)&num)->value;
				break;
				
				case Number::TYPE_INT:
				value += ((_DerivedNumberType<int>*)&num)->value;
				break;
				
				case Number::TYPE_UNSIGNEDINT:
				value += ((_DerivedNumberType<unsigned int>*)&num)->value;
				break;
				
				case Number::TYPE_LONG:
				value += ((_DerivedNumberType<long>*)&num)->value;
				break;
				
				case Number::TYPE_UNSIGNEDLONG:
				value += ((_DerivedNumberType<unsigned long>*)&num)->value;
				break;
				
				case Number::TYPE_LONGLONG:
				value += ((_DerivedNumberType<long long>*)&num)->value;
				break;
				
				case Number::TYPE_UNSIGNEDLONGLONG:
				value += ((_DerivedNumberType<unsigned long long>*)&num)->value;
				break;
				
				case Number::TYPE_FLOAT:
				value += ((_DerivedNumberType<float>*)&num)->value;
				break;
				
				case Number::TYPE_DOUBLE:
				value += ((_DerivedNumberType<double>*)&num)->value;
				break;
				
				case Number::TYPE_LONGDOUBLE:
				value += ((_DerivedNumberType<long double>*)&num)->value;
				break;
			}
			return *((_BaseNumberType*)this);
		}
		
		virtual Number operator+(const _BaseNumberType&num) const
		{
			if(type == Number::TYPE_BOOL)
			{
				throw IllegalNumberOperationException("+", "bool", "left");
			}
			switch(num.type)
			{
				default:
				case Number::TYPE_NULL:
				return value;
				
				case Number::TYPE_BOOL:
				//return value + ((_DerivedNumberType<bool>*)&num)->value;
				throw IllegalNumberOperationException("+", "bool", "right");
				
				case Number::TYPE_CHAR:
				return value + ((_DerivedNumberType<char>*)&num)->value;
				
				case Number::TYPE_UNSIGNEDCHAR:
				return value + ((_DerivedNumberType<unsigned char>*)&num)->value;
				
				case Number::TYPE_SHORT:
				return value + ((_DerivedNumberType<short>*)&num)->value;
				break;
				
				case Number::TYPE_UNSIGNEDSHORT:
				return value + ((_DerivedNumberType<unsigned short>*)&num)->value;
				break;
				
				case Number::TYPE_INT:
				return value + ((_DerivedNumberType<int>*)&num)->value;
				break;
				
				case Number::TYPE_UNSIGNEDINT:
				return value + ((_DerivedNumberType<unsigned int>*)&num)->value;
				break;
				
				case Number::TYPE_LONG:
				return value + ((_DerivedNumberType<long>*)&num)->value;
				
				case Number::TYPE_UNSIGNEDLONG:
				return value + ((_DerivedNumberType<unsigned long>*)&num)->value;
				
				case Number::TYPE_LONGLONG:
				return value + ((_DerivedNumberType<long long>*)&num)->value;
				
				case Number::TYPE_UNSIGNEDLONGLONG:
				return value + ((_DerivedNumberType<unsigned long long>*)&num)->value;
				
				case Number::TYPE_FLOAT:
				return value + ((_DerivedNumberType<float>*)&num)->value;
				
				case Number::TYPE_DOUBLE:
				return value + ((_DerivedNumberType<double>*)&num)->value;
				
				case Number::TYPE_LONGDOUBLE:
				return value + ((_DerivedNumberType<long double>*)&num)->value;
			}
			return (T)0;
		}
		
		virtual _BaseNumberType& operator-=(const _BaseNumberType&num)
		{
			if(type == Number::TYPE_BOOL)
			{
				throw IllegalNumberOperationException("-=", "bool", "left");
			}
			switch(num.type)
			{
				default:
				case Number::TYPE_NULL:
				break;
				
				case Number::TYPE_BOOL:
				//value -= ((_DerivedNumberType<bool>*)&num)->value);
				throw IllegalNumberOperationException("-=", "bool", "right");
				break;
				
				case Number::TYPE_CHAR:
				value -= ((_DerivedNumberType<char>*)&num)->value;
				break;
				
				case Number::TYPE_UNSIGNEDCHAR:
				value -= ((_DerivedNumberType<unsigned char>*)&num)->value;
				break;
				
				case Number::TYPE_SHORT:
				value -= ((_DerivedNumberType<short>*)&num)->value;
				break;
				
				case Number::TYPE_UNSIGNEDSHORT:
				value -= ((_DerivedNumberType<unsigned short>*)&num)->value;
				break;
				
				case Number::TYPE_INT:
				value -= ((_DerivedNumberType<int>*)&num)->value;
				break;
				
				case Number::TYPE_UNSIGNEDINT:
				value -= ((_DerivedNumberType<unsigned int>*)&num)->value;
				break;
				
				case Number::TYPE_LONG:
				value -= ((_DerivedNumberType<long>*)&num)->value;
				break;
				
				case Number::TYPE_UNSIGNEDLONG:
				value -= ((_DerivedNumberType<unsigned long>*)&num)->value;
				break;
				
				case Number::TYPE_LONGLONG:
				value -= ((_DerivedNumberType<long long>*)&num)->value;
				break;
				
				case Number::TYPE_UNSIGNEDLONGLONG:
				value -= ((_DerivedNumberType<unsigned long long>*)&num)->value;
				break;
				
				case Number::TYPE_FLOAT:
				value -= ((_DerivedNumberType<float>*)&num)->value;
				break;
				
				case Number::TYPE_DOUBLE:
				value -= ((_DerivedNumberType<double>*)&num)->value;
				break;
				
				case Number::TYPE_LONGDOUBLE:
				value -= ((_DerivedNumberType<long double>*)&num)->value;
				break;
			}
			return *((_BaseNumberType*)this);
		}
		
		virtual Number operator-(const _BaseNumberType&num) const
		{
			if(type == Number::TYPE_BOOL)
			{
				throw IllegalNumberOperationException("-", "bool", "left");
			}
			switch(num.type)
			{
				default:
				case Number::TYPE_NULL:
				return value;
				
				case Number::TYPE_BOOL:
				//return value - ((_DerivedNumberType<bool>*)&num)->value;
				throw IllegalNumberOperationException("-", "bool", "right");
				
				case Number::TYPE_CHAR:
				return value - ((_DerivedNumberType<char>*)&num)->value;
				
				case Number::TYPE_UNSIGNEDCHAR:
				return value - ((_DerivedNumberType<unsigned char>*)&num)->value;
				
				case Number::TYPE_SHORT:
				return value - ((_DerivedNumberType<short>*)&num)->value;
				
				case Number::TYPE_UNSIGNEDSHORT:
				return value - ((_DerivedNumberType<unsigned short>*)&num)->value;
				
				case Number::TYPE_INT:
				return value - ((_DerivedNumberType<int>*)&num)->value;
				
				case Number::TYPE_UNSIGNEDINT:
				return value - ((_DerivedNumberType<unsigned int>*)&num)->value;
				
				case Number::TYPE_LONG:
				return value - ((_DerivedNumberType<long>*)&num)->value;
				
				case Number::TYPE_UNSIGNEDLONG:
				return value - ((_DerivedNumberType<unsigned long>*)&num)->value;
				
				case Number::TYPE_LONGLONG:
				return value - ((_DerivedNumberType<long long>*)&num)->value;
				
				case Number::TYPE_UNSIGNEDLONGLONG:
				return value - ((_DerivedNumberType<unsigned long long>*)&num)->value;
				
				case Number::TYPE_FLOAT:
				return value - ((_DerivedNumberType<float>*)&num)->value;
				
				case Number::TYPE_DOUBLE:
				return value - ((_DerivedNumberType<double>*)&num)->value;
				
				case Number::TYPE_LONGDOUBLE:
				return value - ((_DerivedNumberType<long double>*)&num)->value;
			}
			return (T)0;
		}
		
		virtual _BaseNumberType& operator*=(const _BaseNumberType&num)
		{
			if(type == Number::TYPE_BOOL)
			{
				throw IllegalNumberOperationException("*=", "bool", "left");
			}
			switch(num.type)
			{
				default:
				case Number::TYPE_NULL:
				value = (T)0;
				break;
				
				case Number::TYPE_BOOL:
				//value *= ((_DerivedNumberType<bool>*)&num)->value;
				throw IllegalNumberOperationException("*=", "bool", "right");
				break;
				
				case Number::TYPE_CHAR:
				value *= ((_DerivedNumberType<char>*)&num)->value;
				break;
				
				case Number::TYPE_UNSIGNEDCHAR:
				value *= ((_DerivedNumberType<unsigned char>*)&num)->value;
				break;
				
				case Number::TYPE_SHORT:
				value *= ((_DerivedNumberType<short>*)&num)->value;
				break;
				
				case Number::TYPE_UNSIGNEDSHORT:
				value *= ((_DerivedNumberType<unsigned short>*)&num)->value;
				break;
				
				case Number::TYPE_INT:
				value *= ((_DerivedNumberType<int>*)&num)->value;
				break;
				
				case Number::TYPE_UNSIGNEDINT:
				value *= ((_DerivedNumberType<unsigned int>*)&num)->value;
				break;
				
				case Number::TYPE_LONG:
				value *= ((_DerivedNumberType<long>*)&num)->value;
				break;
				
				case Number::TYPE_UNSIGNEDLONG:
				value *= ((_DerivedNumberType<unsigned long>*)&num)->value;
				break;
				
				case Number::TYPE_LONGLONG:
				value *= ((_DerivedNumberType<long long>*)&num)->value;
				break;
				
				case Number::TYPE_UNSIGNEDLONGLONG:
				value *= ((_DerivedNumberType<unsigned long long>*)&num)->value;
				break;
				
				case Number::TYPE_FLOAT:
				value *= ((_DerivedNumberType<float>*)&num)->value;
				break;
				
				case Number::TYPE_DOUBLE:
				value *= ((_DerivedNumberType<double>*)&num)->value;
				break;
				
				case Number::TYPE_LONGDOUBLE:
				value *= ((_DerivedNumberType<long double>*)&num)->value;
				break;
			}
			return *((_BaseNumberType*)this);
		}
		
		virtual Number operator*(const _BaseNumberType&num) const
		{
			if(type == Number::TYPE_BOOL)
			{
				throw IllegalNumberOperationException("*", "bool", "left");
			}
			switch(num.type)
			{
				default:
				case Number::TYPE_NULL:
				return Number();
				
				case Number::TYPE_BOOL:
				//return value * ((_DerivedNumberType<bool>*)&num)->value;
				throw IllegalNumberOperationException("*", "bool", "right");
				
				case Number::TYPE_CHAR:
				return value * ((_DerivedNumberType<char>*)&num)->value;
				
				case Number::TYPE_UNSIGNEDCHAR:
				return value * ((_DerivedNumberType<unsigned char>*)&num)->value;
				
				case Number::TYPE_SHORT:
				return value * ((_DerivedNumberType<short>*)&num)->value;
				
				case Number::TYPE_UNSIGNEDSHORT:
				return value * ((_DerivedNumberType<unsigned short>*)&num)->value;
				
				case Number::TYPE_INT:
				return value * ((_DerivedNumberType<int>*)&num)->value;
				
				case Number::TYPE_UNSIGNEDINT:
				return value * ((_DerivedNumberType<unsigned int>*)&num)->value;
				
				case Number::TYPE_LONG:
				return value * ((_DerivedNumberType<long>*)&num)->value;
				
				case Number::TYPE_UNSIGNEDLONG:
				return value * ((_DerivedNumberType<unsigned long>*)&num)->value;
				
				case Number::TYPE_LONGLONG:
				return value * ((_DerivedNumberType<long long>*)&num)->value;
				
				case Number::TYPE_UNSIGNEDLONGLONG:
				return value * ((_DerivedNumberType<unsigned long long>*)&num)->value;
				
				case Number::TYPE_FLOAT:
				return value * ((_DerivedNumberType<float>*)&num)->value;
				
				case Number::TYPE_DOUBLE:
				return value * ((_DerivedNumberType<double>*)&num)->value;
				
				case Number::TYPE_LONGDOUBLE:
				return value * ((_DerivedNumberType<long double>*)&num)->value;
			}
			return (T)0;
		}
		
		virtual _BaseNumberType& operator/=(const _BaseNumberType&num)
		{
			if(type == Number::TYPE_BOOL)
			{
				throw IllegalNumberOperationException("/=", "bool", "left");
			}
			switch(num.type)
			{
				default:
				case Number::TYPE_NULL:
				value = (T)0;
				break;
				
				case Number::TYPE_BOOL:
				//value /= ((_DerivedNumberType<bool>*)&num)->value;
				throw IllegalNumberOperationException("/=", "bool", "right");
				break;
				
				case Number::TYPE_CHAR:
				value /= ((_DerivedNumberType<char>*)&num)->value;
				break;
				
				case Number::TYPE_UNSIGNEDCHAR:
				value /= ((_DerivedNumberType<unsigned char>*)&num)->value;
				break;
				
				case Number::TYPE_SHORT:
				value /= ((_DerivedNumberType<short>*)&num)->value;
				break;
				
				case Number::TYPE_UNSIGNEDSHORT:
				value /= ((_DerivedNumberType<unsigned short>*)&num)->value;
				break;
				
				case Number::TYPE_INT:
				value /= ((_DerivedNumberType<int>*)&num)->value;
				break;
				
				case Number::TYPE_UNSIGNEDINT:
				value /= ((_DerivedNumberType<unsigned int>*)&num)->value;
				break;
				
				case Number::TYPE_LONG:
				value /= ((_DerivedNumberType<long>*)&num)->value;
				break;
				
				case Number::TYPE_UNSIGNEDLONG:
				value /= ((_DerivedNumberType<unsigned long>*)&num)->value;
				break;
				
				case Number::TYPE_LONGLONG:
				value /= ((_DerivedNumberType<long long>*)&num)->value;
				break;
				
				case Number::TYPE_UNSIGNEDLONGLONG:
				value /= ((_DerivedNumberType<unsigned long long>*)&num)->value;
				break;
				
				case Number::TYPE_FLOAT:
				value /= ((_DerivedNumberType<float>*)&num)->value;
				break;
				
				case Number::TYPE_DOUBLE:
				value /= ((_DerivedNumberType<double>*)&num)->value;
				break;
				
				case Number::TYPE_LONGDOUBLE:
				value /= ((_DerivedNumberType<long double>*)&num)->value;
				break;
			}
			return *((_BaseNumberType*)this);
		}
		
		virtual Number operator/(const _BaseNumberType&num) const
		{
			if(type == Number::TYPE_BOOL)
			{
				throw IllegalNumberOperationException("/=", "bool", "left");
			}
			switch(num.type)
			{
				default:
				case Number::TYPE_NULL:
				return Number();
				
				case Number::TYPE_BOOL:
				//return value / ((_DerivedNumberType<bool>*)&num)->value;
				throw IllegalNumberOperationException("/=", "bool", "right");
				
				case Number::TYPE_CHAR:
				return value / ((_DerivedNumberType<char>*)&num)->value;
				
				case Number::TYPE_UNSIGNEDCHAR:
				return value / ((_DerivedNumberType<unsigned char>*)&num)->value;
				
				case Number::TYPE_SHORT:
				return value / ((_DerivedNumberType<short>*)&num)->value;
				
				case Number::TYPE_UNSIGNEDSHORT:
				return value / ((_DerivedNumberType<unsigned short>*)&num)->value;
				
				case Number::TYPE_INT:
				return value / ((_DerivedNumberType<int>*)&num)->value;
				
				case Number::TYPE_UNSIGNEDINT:
				return value / ((_DerivedNumberType<unsigned int>*)&num)->value;
				
				case Number::TYPE_LONG:
				return value / ((_DerivedNumberType<long>*)&num)->value;
				
				case Number::TYPE_UNSIGNEDLONG:
				return value / ((_DerivedNumberType<unsigned long>*)&num)->value;
				
				case Number::TYPE_LONGLONG:
				return value / ((_DerivedNumberType<long long>*)&num)->value;
				
				case Number::TYPE_UNSIGNEDLONGLONG:
				return value / ((_DerivedNumberType<unsigned long long>*)&num)->value;
				
				case Number::TYPE_FLOAT:
				return value / ((_DerivedNumberType<float>*)&num)->value;
				
				case Number::TYPE_DOUBLE:
				return value / ((_DerivedNumberType<double>*)&num)->value;
				
				case Number::TYPE_LONGDOUBLE:
				return value / ((_DerivedNumberType<long double>*)&num)->value;
			}
			return (T)0;
		}
		
		virtual _BaseNumberType& operator%=(const _BaseNumberType&num)
		{
			switch(type)
			{
				case Number::TYPE_FLOAT:
				throw IllegalNumberOperationException("%=", "float", "left");
				break;
				
				case Number::TYPE_DOUBLE:
				throw IllegalNumberOperationException("%=", "double", "left");
				break;
				
				case Number::TYPE_LONGDOUBLE:
				throw IllegalNumberOperationException("%=", "long double", "left");
				break;
			}
			return *((_BaseNumberType*)this);
		}
		
		virtual Number operator%(const _BaseNumberType&num) const
		{
			switch(type)
			{
				case Number::TYPE_FLOAT:
				throw IllegalNumberOperationException("%=", "float", "left");
				break;
				
				case Number::TYPE_DOUBLE:
				throw IllegalNumberOperationException("%=", "double", "left");
				break;
				
				case Number::TYPE_LONGDOUBLE:
				throw IllegalNumberOperationException("%=", "long double", "left");
				break;
			}
			return (T)0;
		}
		
		virtual bool isIntegral() const
		{
			return false;
		}
		
		virtual bool asBool() const
		{
			return static_cast<bool>(value);
		}
		
		virtual char asChar() const
		{
			return static_cast<char>(value);
		}
		
		virtual unsigned char asUnsignedChar() const
		{
			return static_cast<unsigned char>(value);
		}
		
		virtual short asShort() const
		{
			return static_cast<short>(value);
		}
		
		virtual unsigned short asUnsignedShort() const
		{
			return static_cast<unsigned short>(value);
		}
		
		virtual int asInt() const
		{
			return static_cast<int>(value);
		}
		
		virtual unsigned int asUnsignedInt() const
		{
			return static_cast<unsigned int>(value);
		}
		
		virtual long asLong() const
		{
			return static_cast<long>(value);
		}
		
		virtual unsigned long asUnsignedLong() const
		{
			return static_cast<unsigned long>(value);
		}
		
		virtual long long asLongLong() const
		{
			return static_cast<long long>(value);
		}
		
		virtual unsigned long long asUnsignedLongLong() const
		{
			return static_cast<unsigned long long>(value);
		}
		
		virtual float asFloat() const
		{
			return static_cast<float>(value);
		}
		
		virtual double asDouble() const
		{
			return static_cast<double>(value);
		}
		
		virtual long double asLongDouble() const
		{
			return static_cast<long double>(value);
		}
		
		virtual String asString() const
		{
			return String("") + value;
		}
	};
	
	template<typename T>
	class _DerivedIntegralType : public _DerivedNumberType<T>
	{
	public:
		T value;
		
		_DerivedIntegralType(const T&val, const Number::NumberType&tp) : _DerivedNumberType<T>(val, tp) {}
		virtual ~_DerivedIntegralType() {}
		
		virtual _BaseNumberType* clone() const
		{
			return (_BaseNumberType*)(new _DerivedIntegralType<T>(value, type));
		}
		
		virtual _BaseNumberType& operator%=(const _BaseNumberType&num)
		{
			if(type==Number::TYPE_BOOL)
			{
				throw IllegalNumberOperationException("%=", "bool", "left");
			}
			switch(num.type)
			{
				default:
				case Number::TYPE_NULL:
				break;
				
				case Number::TYPE_BOOL:
				//value %= ((_DerivedNumberType<bool>*)&num)->value;
				throw IllegalNumberOperationException("%=", "bool", "right");
				break;
				
				case Number::TYPE_CHAR:
				value %= ((_DerivedNumberType<char>*)&num)->value;
				break;
				
				case Number::TYPE_UNSIGNEDCHAR:
				value %= ((_DerivedNumberType<unsigned char>*)&num)->value;
				break;
				
				case Number::TYPE_SHORT:
				value %= ((_DerivedNumberType<short>*)&num)->value;
				break;
				
				case Number::TYPE_UNSIGNEDSHORT:
				value %= ((_DerivedNumberType<unsigned short>*)&num)->value;
				break;
				
				case Number::TYPE_INT:
				value %= ((_DerivedNumberType<int>*)&num)->value;
				break;
				
				case Number::TYPE_UNSIGNEDINT:
				value %= ((_DerivedNumberType<unsigned int>*)&num)->value;
				break;
				
				case Number::TYPE_LONG:
				value %= ((_DerivedNumberType<long>*)&num)->value;
				break;
				
				case Number::TYPE_UNSIGNEDLONG:
				value %= ((_DerivedNumberType<unsigned long>*)&num)->value;
				break;
				
				case Number::TYPE_LONGLONG:
				value %= ((_DerivedNumberType<long long>*)&num)->value;
				break;
				
				case Number::TYPE_UNSIGNEDLONGLONG:
				value %= ((_DerivedNumberType<unsigned long long>*)&num)->value;
				break;
				
				case Number::TYPE_FLOAT:
				//value %= ((_DerivedNumberType<float>*)&num)->value;
				throw IllegalNumberOperationException("%=", "float", "right");
				break;
				
				case Number::TYPE_DOUBLE:
				//value %= ((_DerivedNumberType<double>*)&num)->value;
				throw IllegalNumberOperationException("%=", "double", "right");
				break;
				
				case Number::TYPE_LONGDOUBLE:
				//value %= ((_DerivedNumberType<long double>*)&num)->value;
				throw IllegalNumberOperationException("%=", "long double", "right");
				break;
			}
			return *((_BaseNumberType*)this);
		}
		
		virtual Number operator%(const _BaseNumberType&num) const
		{
			if(type==Number::TYPE_BOOL)
			{
				throw IllegalNumberOperationException("%=", "bool", "left");
			}
			switch(num.type)
			{
				default:
				case Number::TYPE_NULL:
				return Number();
				
				case Number::TYPE_BOOL:
				//return value % ((_DerivedNumberType<bool>*)&num)->value;
				throw IllegalNumberOperationException("%=", "bool", "right");
				
				case Number::TYPE_CHAR:
				return value % ((_DerivedNumberType<char>*)&num)->value;
				
				case Number::TYPE_UNSIGNEDCHAR:
				return value % ((_DerivedNumberType<unsigned char>*)&num)->value;
				
				case Number::TYPE_SHORT:
				return value % ((_DerivedNumberType<short>*)&num)->value;
				
				case Number::TYPE_UNSIGNEDSHORT:
				return value % ((_DerivedNumberType<unsigned short>*)&num)->value;
				
				case Number::TYPE_INT:
				return value % ((_DerivedNumberType<int>*)&num)->value;
				
				case Number::TYPE_UNSIGNEDINT:
				return value % ((_DerivedNumberType<unsigned int>*)&num)->value;
				
				case Number::TYPE_LONG:
				return value % ((_DerivedNumberType<long>*)&num)->value;
				
				case Number::TYPE_UNSIGNEDLONG:
				return value % ((_DerivedNumberType<unsigned long>*)&num)->value;
				
				case Number::TYPE_LONGLONG:
				return value % ((_DerivedNumberType<long long>*)&num)->value;
				
				case Number::TYPE_UNSIGNEDLONGLONG:
				return value % ((_DerivedNumberType<unsigned long long>*)&num)->value;
				
				case Number::TYPE_FLOAT:
				//return value % ((_DerivedNumberType<float>*)&num)->value;
				throw IllegalNumberOperationException("%=", "float", "right");
				
				case Number::TYPE_DOUBLE:
				//return value % ((_DerivedNumberType<double>*)&num)->value;
				throw IllegalNumberOperationException("%=", "double", "right");
				
				case Number::TYPE_LONGDOUBLE:
				//return value % ((_DerivedNumberType<long double>*)&num)->value;
				throw IllegalNumberOperationException("%=", "long double", "right");
			}
			return (T)0;
		}
		
		virtual bool isIntegral() const
		{
			return true;
		}
	};
	
	Number::Number()
	{
		value = nullptr;
	}
	
	Number::Number(const bool&val)
	{
		value = new _DerivedIntegralType<bool>(val, TYPE_BOOL);
	}
	
	Number::Number(const char&val)
	{
		value = new _DerivedIntegralType<char>(val, TYPE_CHAR);
	}
	
	Number::Number(const unsigned char&val)
	{
		value = new _DerivedIntegralType<unsigned char>(val, TYPE_UNSIGNEDCHAR);
	}
	
	Number::Number(const short&val)
	{
		value = new _DerivedIntegralType<short>(val, TYPE_SHORT);
	}
	
	Number::Number(const unsigned short&val)
	{
		value = new _DerivedIntegralType<unsigned short>(val, TYPE_UNSIGNEDSHORT);
	}
	
	Number::Number(const int&val)
	{
		value = new _DerivedIntegralType<int>(val, TYPE_INT);
	}
	
	Number::Number(const unsigned int&val)
	{
		value = new _DerivedIntegralType<unsigned int>(val, TYPE_UNSIGNEDINT);
	}
	
	Number::Number(const long&val)
	{
		value = new _DerivedIntegralType<long>(val, TYPE_LONG);
	}
	
	Number::Number(const unsigned long&val)
	{
		value = new _DerivedIntegralType<unsigned long>(val, TYPE_UNSIGNEDLONG);
	}
	
	Number::Number(const long long&val)
	{
		value = new _DerivedIntegralType<long long>(val, TYPE_LONGLONG);
	}
	
	Number::Number(const unsigned long long&val)
	{
		value = new _DerivedIntegralType<unsigned long long>(val, TYPE_UNSIGNEDLONGLONG);
	}
	
	Number::Number(const float&val)
	{
		value = new _DerivedNumberType<float>(val, TYPE_FLOAT);
	}
	
	Number::Number(const double&val)
	{
		value = new _DerivedNumberType<double>(val, TYPE_DOUBLE);
	}
	
	Number::Number(const long double&val)
	{
		value = new _DerivedNumberType<long double>(val, TYPE_LONGDOUBLE);
	}
	
	Number::Number(const Number&num)
	{
		if(num.value == nullptr)
		{
			value = nullptr;
		}
		else
		{
			value = num.value->clone();
		}
	}
	
	Number::~Number()
	{
		if(value!=nullptr)
		{
			delete value;
		}
	}
	
	Number& Number::operator=(const Number&num)
	{
		if(value != nullptr)
		{
			delete value;
			value = nullptr;
		}
		if(num.value != nullptr)
		{
			value = num.value->clone();
		}
		return *this;
	}
		
	Number& Number::operator+=(const Number&num)
	{
		*value += *num.value;
		return *this;
	}
	
	Number& Number::operator-=(const Number&num)
	{
		*value -= *num.value;
		return *this;
	}
	
	Number& Number::operator*=(const Number&num)
	{
		*value *= *num.value;
		return *this;
	}
	
	Number& Number::operator/=(const Number&num)
	{
		*value /= *num.value;
		return *this;
	}
	
	Number& Number::operator%=(const Number&num)
	{
		*value %= *num.value;
		return *this;
	}
	
	bool Number::isIntegral() const
	{
		if(value == nullptr)
		{
			return false;
		}
		return value->isIntegral();
	}
	
	Number::NumberType Number::getType() const
	{
		if(value == nullptr)
		{
			return TYPE_NULL;
		}
		return value->type;
	}
	
	Number::operator bool() const
	{
		if(value == nullptr)
		{
			return false;
		}
		return value->asBool();
	}
	
	Number::operator char() const
	{
		if(value == nullptr)
		{
			return 0;
		}
		return value->asChar();
	}
	
	Number::operator unsigned char() const
	{
		if(value == nullptr)
		{
			return 0;
		}
		return value->asChar();
	}
	
	Number::operator short() const
	{
		if(value == nullptr)
		{
			return 0;
		}
		return value->asShort();
	}
	
	Number::operator unsigned short() const
	{
		if(value == nullptr)
		{
			return 0;
		}
		return value->asUnsignedShort();
	}
	
	Number::operator int() const
	{
		if(value == nullptr)
		{
			return 0;
		}
		return value->asInt();
	}
	
	Number::operator unsigned int() const
	{
		if(value == nullptr)
		{
			return 0;
		}
		return value->asUnsignedInt();
	}
	
	Number::operator long() const
	{
		if(value == nullptr)
		{
			return 0;
		}
		return value->asLong();
	}
	
	Number::operator unsigned long() const
	{
		if(value == nullptr)
		{
			return 0;
		}
		return value->asUnsignedLong();
	}
	
	Number::operator long long() const
	{
		if(value == nullptr)
		{
			return 0;
		}
		return value->asLongLong();
	}
	
	Number::operator unsigned long long() const
	{
		if(value == nullptr)
		{
			return 0;
		}
		return value->asUnsignedLongLong();
	}
	
	Number::operator float() const
	{
		if(value == nullptr)
		{
			return 0;
		}
		return value->asFloat();
	}
	
	Number::operator double() const
	{
		if(value == nullptr)
		{
			return 0;
		}
		return value->asDouble();
	}
	
	Number::operator long double() const
	{
		if(value == nullptr)
		{
			return 0;
		}
		return value->asLongDouble();
	}
	
	bool Number::asBool() const
	{
		if(value == nullptr)
		{
			return false;
		}
		return value->asBool();
	}
	
	char Number::asChar() const
	{
		if(value == nullptr)
		{
			return 0;
		}
		return value->asChar();
	}
	
	unsigned char Number::asUnsignedChar() const
	{
		if(value == nullptr)
		{
			return 0;
		}
		return value->asUnsignedChar();
	}
	
	short Number::asShort() const
	{
		if(value == nullptr)
		{
			return 0;
		}
		return value->asShort();
	}
	
	unsigned short Number::asUnsignedShort() const
	{
		if(value == nullptr)
		{
			return 0;
		}
		return value->asUnsignedShort();
	}
	
	int Number::asInt() const
	{
		if(value == nullptr)
		{
			return 0;
		}
		return value->asInt();
	}
	
	unsigned int Number::asUnsignedInt() const
	{
		if(value == nullptr)
		{
			return 0;
		}
		return value->asUnsignedInt();
	}
	
	long Number::asLong() const
	{
		if(value == nullptr)
		{
			return 0;
		}
		return value->asLong();
	}
	
	unsigned long Number::asUnsignedLong() const
	{
		if(value == nullptr)
		{
			return 0;
		}
		return value->asUnsignedLong();
	}
	
	long long Number::asLongLong() const
	{
		if(value == nullptr)
		{
			return 0;
		}
		return value->asLongLong();
	}
	
	unsigned long long Number::asUnsignedLongLong() const
	{
		if(value == nullptr)
		{
			return 0;
		}
		return value->asUnsignedLongLong();
	}
	
	float Number::asFloat() const
	{
		if(value == nullptr)
		{
			return 0;
		}
		return value->asFloat();
	}
	
	double Number::asDouble() const
	{
		if(value == nullptr)
		{
			return 0;
		}
		return value->asDouble();
	}
	
	long double Number::asLongDouble() const
	{
		if(value == nullptr)
		{
			return 0;
		}
		return value->asLongDouble();
	}
	
	String Number::asString() const
	{
		if(value == nullptr)
		{
			return NULL_STRING;
		}
		return value->asString();
	}

#define NUMBER_OPERATION_TONUMBER(operatr, type, defaultReturn) \
	Number operator##operatr(const Number&left, const type&right) \
	{ \
		if(left.value==nullptr) \
		{ \
			return defaultReturn; \
		} \
		return *left.value operatr *Number(right).value; \
	}
	
#define NUMBER_OPERATION_TOPRIMITIVE(operatr, type, convertFunc, defaultReturn) \
	type operator##operatr(const type&left, const Number&right) \
	{ \
		if(right.value==nullptr) \
		{ \
			return defaultReturn; \
		} \
		return *Number(left).value operatr *right.value; \
	}
	
#define NUMBER_OPERATIONTO_DEFINE(operatr, type, convertFunc, defaultReturn) \
	type operator##operatr(type&left, const Number&right) \
	{ \
		if(right.value==nullptr) \
		{ \
			return defaultReturn; \
		} \
		left operatr right.value->convertFunc(); \
		return left; \
	}
	
#define NUMBER_OPERATOR_SET(type, convertFunc) \
	NUMBER_OPERATION_TONUMBER(+, type, left) \
	NUMBER_OPERATION_TOPRIMITIVE(+, type, convertFunc, left) \
	NUMBER_OPERATION_TONUMBER(-, type, left) \
	NUMBER_OPERATION_TOPRIMITIVE(-, type, convertFunc, left) \
	NUMBER_OPERATION_TONUMBER(*, type, left) \
	NUMBER_OPERATION_TOPRIMITIVE(*, type, convertFunc, (type)0) \
	NUMBER_OPERATION_TONUMBER(/, type, left) \
	NUMBER_OPERATION_TOPRIMITIVE(/, type, convertFunc, (type)0) \
	NUMBER_OPERATION_TONUMBER(%, type, left) \
	NUMBER_OPERATION_TOPRIMITIVE(%, type, convertFunc, (type)0)
	
#define NUMBER_OPERATOR_SET_FLOATINGPOINT(type, convertFunc) \
	NUMBER_OPERATION_TONUMBER(+, type, left) \
	NUMBER_OPERATION_TOPRIMITIVE(+, type, convertFunc, left) \
	NUMBER_OPERATION_TONUMBER(-, type, left) \
	NUMBER_OPERATION_TOPRIMITIVE(-, type, convertFunc, left) \
	NUMBER_OPERATION_TONUMBER(*, type, left) \
	NUMBER_OPERATION_TOPRIMITIVE(*, type, convertFunc, (type)0) \
	NUMBER_OPERATION_TONUMBER(/, type, left) \
	NUMBER_OPERATION_TOPRIMITIVE(/, type, convertFunc, (type)0) \
	NUMBER_OPERATION_TOPRIMITIVE(%, type, convertFunc, (type)0)
	
	Number operator+(const Number&left, const Number&right)
	{
		if(left.value == nullptr)
		{
			return left;
		}
		else if(right.value == nullptr)
		{
			return left;
		}
		return *left.value + *right.value;
	}
	
	Number operator-(const Number&left, const Number&right)
	{
		if(left.value == nullptr)
		{
			return left;
		}
		else if(right.value == nullptr)
		{
			return left;
		}
		return *left.value - *right.value;
	}
	
	Number operator*(const Number&left, const Number&right)
	{
		if(left.value == nullptr)
		{
			return left;
		}
		else if(right.value == nullptr)
		{
			return right;
		}
		return *left.value * *right.value;
	}
	
	Number operator/(const Number&left, const Number&right)
	{
		if(left.value == nullptr)
		{
			return left;
		}
		else if(right.value == nullptr)
		{
			return right;
		}
		return *left.value / *right.value;
	}
	
	Number operator%(const Number&left, const Number&right)
	{
		if(left.value == nullptr)
		{
			return left;
		}
		else if(right.value == nullptr)
		{
			return right;
		}
		return *left.value % *right.value;
	}
	
	String operator+(const String&left, const Number&right)
	{
		if(right.value == nullptr)
		{
			return left + NULL_STRING;
		}
		return left + right.value->asString();
	}
	
	String operator+(const Number&left, const String&right)
	{
		if(left.value == nullptr)
		{
			return NULL_STRING + right;
		}
		return left.value->asString() + right;
	}
	
	//NUMBER_OPERATOR_SET(bool, asBool)
	NUMBER_OPERATOR_SET(char, asChar)
	NUMBER_OPERATOR_SET(unsigned char, asUnsignedChar)
	NUMBER_OPERATOR_SET(short, asShort)
	NUMBER_OPERATOR_SET(unsigned short, asUnsignedShort)
	NUMBER_OPERATOR_SET(int, asInt)
	NUMBER_OPERATOR_SET(unsigned int, asUnsignedInt)
	NUMBER_OPERATOR_SET(long, asLong)
	NUMBER_OPERATOR_SET(unsigned long, asUnsignedLong)
	NUMBER_OPERATOR_SET(long long, asLongLong)
	NUMBER_OPERATOR_SET(unsigned long long, asUnsignedLongLong)
	NUMBER_OPERATOR_SET_FLOATINGPOINT(float, asFloat)
	NUMBER_OPERATOR_SET_FLOATINGPOINT(double, asDouble)
	NUMBER_OPERATOR_SET_FLOATINGPOINT(long double, asLongDouble)
}

#ifdef _MSC_VER
#pragma warning(pop)
#endif