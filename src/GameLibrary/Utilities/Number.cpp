
#include "Number.h"

#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable : 4800)
#pragma warning(disable : 4804)
#pragma warning(disable : 4244)
#pragma warning(disable : 4805)
#pragma warning(disable : 4018)
#endif

namespace GameLibrary
{
#define NULL_STRING "(null)"
	
	class _BaseNumberType
	{
	public:
		Number::NumberType type;
		
		virtual ~_BaseNumberType(){}
		
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
		
		virtual _BaseNumberType& operator++() = 0;
		virtual _BaseNumberType& operator--() = 0;
		
		virtual bool operator==(const _BaseNumberType&) const = 0;
		virtual bool operator!=(const _BaseNumberType&) const = 0;
		virtual bool operator>(const _BaseNumberType&) const = 0;
		virtual bool operator>=(const _BaseNumberType&) const = 0;
		virtual bool operator<(const _BaseNumberType&) const = 0;
		virtual bool operator<=(const _BaseNumberType&) const = 0;
		
		virtual std::ostream& streamTo(std::ostream&) const = 0;
		
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
		
		virtual _BaseNumberType* clone() const override
		{
			return (_BaseNumberType*)(new _DerivedNumberType<T>(value, type));
		}
		
		virtual _BaseNumberType& operator+=(const _BaseNumberType&num) override
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
		
		virtual Number operator+(const _BaseNumberType&num) const override
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
		
		virtual _BaseNumberType& operator-=(const _BaseNumberType&num) override
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
		
		virtual Number operator-(const _BaseNumberType&num) const override
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
		
		virtual _BaseNumberType& operator*=(const _BaseNumberType&num) override
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
		
		virtual Number operator*(const _BaseNumberType&num) const override
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
		
		virtual _BaseNumberType& operator/=(const _BaseNumberType&num) override
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
		
		virtual Number operator/(const _BaseNumberType&num) const override
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
		
		virtual _BaseNumberType& operator%=(const _BaseNumberType&num) override
		{
			switch(type)
			{
				default:
				//Do nothing
				break;
				
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
		
		virtual Number operator%(const _BaseNumberType&num) const override
		{
			switch(type)
			{
				default:
				//Do nothing
				break;
				
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
		
		virtual _BaseNumberType& operator++() override
		{
			if(type == Number::TYPE_BOOL)
			{
				throw IllegalNumberOperationException("++", "bool", "left");
			}
			return *this;
		}
		
		virtual _BaseNumberType& operator--() override
		{
			if(type == Number::TYPE_BOOL)
			{
				throw IllegalNumberOperationException("--", "bool", "left");
			}
			return *this;
		}
		
#define NUMBER_OPERATOR_BODY(operatr, arg) \
	switch(arg.type) \
	{ \
		default: \
		return false; \
		\
		case Number::TYPE_BOOL: \
		return value operatr ((_DerivedNumberType<bool>*)&arg)->value; \
		\
		case Number::TYPE_CHAR: \
		return value operatr ((_DerivedNumberType<char>*)&arg)->value; \
		\
		case Number::TYPE_UNSIGNEDCHAR: \
		return value operatr ((_DerivedNumberType<unsigned char>*)&arg)->value; \
		\
		case Number::TYPE_SHORT: \
		return value operatr ((_DerivedNumberType<short>*)&arg)->value; \
		\
		case Number::TYPE_UNSIGNEDSHORT: \
		return value operatr ((_DerivedNumberType<unsigned short>*)&arg)->value; \
		\
		case Number::TYPE_INT: \
		return value operatr ((_DerivedNumberType<int>*)&arg)->value; \
		\
		case Number::TYPE_UNSIGNEDINT: \
		return value operatr ((_DerivedNumberType<unsigned int>*)&arg)->value; \
		\
		case Number::TYPE_LONG: \
		return value operatr ((_DerivedNumberType<long>*)&arg)->value; \
		\
		case Number::TYPE_UNSIGNEDLONG: \
		return value operatr ((_DerivedNumberType<unsigned long>*)&arg)->value; \
		\
		case Number::TYPE_LONGLONG: \
		return value operatr ((_DerivedNumberType<long long>*)&arg)->value; \
		\
		case Number::TYPE_UNSIGNEDLONGLONG: \
		return value operatr ((_DerivedNumberType<unsigned long long>*)&arg)->value; \
		\
		case Number::TYPE_FLOAT: \
		return value operatr ((_DerivedNumberType<float>*)&arg)->value; \
		\
		case Number::TYPE_DOUBLE: \
		return value operatr ((_DerivedNumberType<double>*)&arg)->value; \
		\
		case Number::TYPE_LONGDOUBLE: \
		return value operatr ((_DerivedNumberType<long double>*)&arg)->value; \
	} \
	return false;
		
		bool operator==(const _BaseNumberType&num) const override
		{
			NUMBER_OPERATOR_BODY(==, num)
		}
		
		bool operator!=(const _BaseNumberType&num) const override
		{
			NUMBER_OPERATOR_BODY(!=, num)
		}
		
		bool operator>(const _BaseNumberType&num) const override
		{
			NUMBER_OPERATOR_BODY(>, num)
		}
		
		bool operator>=(const _BaseNumberType&num) const override
		{
			NUMBER_OPERATOR_BODY(>=, num)
		}
		
		bool operator<(const _BaseNumberType&num) const override
		{
			NUMBER_OPERATOR_BODY(<, num)
		}
		
		bool operator<=(const _BaseNumberType&num) const override
		{
			NUMBER_OPERATOR_BODY(<=, num)
		}
		
		virtual std::ostream& streamTo(std::ostream&stream) const override
		{
			stream << value;
			return stream;
		}
		
		virtual bool isIntegral() const override
		{
			return false;
		}
		
		virtual bool asBool() const override
		{
			if(value)
			{
				return true;
			}
			return false;
		}
		
		virtual char asChar() const override
		{
			return static_cast<char>(value);
		}
		
		virtual unsigned char asUnsignedChar() const override
		{
			return static_cast<unsigned char>(value);
		}
		
		virtual short asShort() const override
		{
			return static_cast<short>(value);
		}
		
		virtual unsigned short asUnsignedShort() const override
		{
			return static_cast<unsigned short>(value);
		}
		
		virtual int asInt() const override
		{
			return static_cast<int>(value);
		}
		
		virtual unsigned int asUnsignedInt() const override
		{
			return static_cast<unsigned int>(value);
		}
		
		virtual long asLong() const override
		{
			return static_cast<long>(value);
		}
		
		virtual unsigned long asUnsignedLong() const override
		{
			return static_cast<unsigned long>(value);
		}
		
		virtual long long asLongLong() const override
		{
			return static_cast<long long>(value);
		}
		
		virtual unsigned long long asUnsignedLongLong() const override
		{
			return static_cast<unsigned long long>(value);
		}
		
		virtual float asFloat() const override
		{
			return static_cast<float>(value);
		}
		
		virtual double asDouble() const override
		{
			return static_cast<double>(value);
		}
		
		virtual long double asLongDouble() const override
		{
			return static_cast<long double>(value);
		}
		
		virtual String asString() const override
		{
			return String("") + value;
		}
	};

	template<typename T>
	class _DerivedNonBoolNumberType : public _DerivedNumberType < T >
	{
	public:
		_DerivedNonBoolNumberType(const T&val, const Number::NumberType&tp) : _DerivedNumberType<T>(val, tp) {}
		virtual ~_DerivedNonBoolNumberType() {}
		
		virtual _BaseNumberType& operator++() override
		{
			value++;
			return *((_BaseNumberType*)this);
		}
		
		virtual _BaseNumberType& operator--() override
		{
			value--;
			return *((_BaseNumberType*)this);
		}
	};
	
	template<typename T>
	class _DerivedIntegralType : public _DerivedNumberType<T>
	{
	public:
		_DerivedIntegralType(const T&val, const Number::NumberType&tp) : _DerivedNumberType<T>(val, tp) {}
		virtual ~_DerivedIntegralType() {}
		
		virtual _BaseNumberType* clone() const override
		{
			return (_BaseNumberType*)(new _DerivedIntegralType<T>(_DerivedNumberType<T>::value, _BaseNumberType::type));
		}
		
		virtual _BaseNumberType& operator%=(const _BaseNumberType&num) override
		{
			if(_BaseNumberType::type==Number::TYPE_BOOL)
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
				_DerivedNumberType<T>::value %= ((_DerivedNumberType<char>*)&num)->value;
				break;
				
				case Number::TYPE_UNSIGNEDCHAR:
				_DerivedNumberType<T>::value %= ((_DerivedNumberType<unsigned char>*)&num)->value;
				break;
				
				case Number::TYPE_SHORT:
				_DerivedNumberType<T>::value %= ((_DerivedNumberType<short>*)&num)->value;
				break;
				
				case Number::TYPE_UNSIGNEDSHORT:
				_DerivedNumberType<T>::value %= ((_DerivedNumberType<unsigned short>*)&num)->value;
				break;
				
				case Number::TYPE_INT:
				_DerivedNumberType<T>::value %= ((_DerivedNumberType<int>*)&num)->value;
				break;
				
				case Number::TYPE_UNSIGNEDINT:
				_DerivedNumberType<T>::value %= ((_DerivedNumberType<unsigned int>*)&num)->value;
				break;
				
				case Number::TYPE_LONG:
				_DerivedNumberType<T>::value %= ((_DerivedNumberType<long>*)&num)->value;
				break;
				
				case Number::TYPE_UNSIGNEDLONG:
				_DerivedNumberType<T>::value %= ((_DerivedNumberType<unsigned long>*)&num)->value;
				break;
				
				case Number::TYPE_LONGLONG:
				_DerivedNumberType<T>::value %= ((_DerivedNumberType<long long>*)&num)->value;
				break;
				
				case Number::TYPE_UNSIGNEDLONGLONG:
				_DerivedNumberType<T>::value %= ((_DerivedNumberType<unsigned long long>*)&num)->value;
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
		
		virtual Number operator%(const _BaseNumberType&num) const override
		{
			if(_BaseNumberType::type==Number::TYPE_BOOL)
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
				return _DerivedNumberType<T>::value % ((_DerivedNumberType<char>*)&num)->value;
				
				case Number::TYPE_UNSIGNEDCHAR:
				return _DerivedNumberType<T>::value % ((_DerivedNumberType<unsigned char>*)&num)->value;
				
				case Number::TYPE_SHORT:
				return _DerivedNumberType<T>::value % ((_DerivedNumberType<short>*)&num)->value;
				
				case Number::TYPE_UNSIGNEDSHORT:
				return _DerivedNumberType<T>::value % ((_DerivedNumberType<unsigned short>*)&num)->value;
				
				case Number::TYPE_INT:
				return _DerivedNumberType<T>::value % ((_DerivedNumberType<int>*)&num)->value;
				
				case Number::TYPE_UNSIGNEDINT:
				return _DerivedNumberType<T>::value % ((_DerivedNumberType<unsigned int>*)&num)->value;
				
				case Number::TYPE_LONG:
				return _DerivedNumberType<T>::value % ((_DerivedNumberType<long>*)&num)->value;
				
				case Number::TYPE_UNSIGNEDLONG:
				return _DerivedNumberType<T>::value % ((_DerivedNumberType<unsigned long>*)&num)->value;
				
				case Number::TYPE_LONGLONG:
				return _DerivedNumberType<T>::value % ((_DerivedNumberType<long long>*)&num)->value;
				
				case Number::TYPE_UNSIGNEDLONGLONG:
				return _DerivedNumberType<T>::value % ((_DerivedNumberType<unsigned long long>*)&num)->value;
				
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
		
		virtual bool isIntegral() const override
		{
			return true;
		}
	};
	
	template<typename T>
	class _DerivedNonBoolIntegralType : public _DerivedIntegralType < T >
	{
	public:
		_DerivedNonBoolIntegralType(const T&val, const Number::NumberType&tp) : _DerivedIntegralType<T>(val, tp) {}
		virtual ~_DerivedNonBoolIntegralType() {}
		
		virtual _BaseNumberType& operator++() override
		{
			value++;
			return *((_BaseNumberType*)this);
		}
		
		virtual _BaseNumberType& operator--() override
		{
			value--;
			return *((_BaseNumberType*)this);
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
		value = new _DerivedNonBoolIntegralType<char>(val, TYPE_CHAR);
	}
	
	Number::Number(const unsigned char&val)
	{
		value = new _DerivedNonBoolIntegralType<unsigned char>(val, TYPE_UNSIGNEDCHAR);
	}
	
	Number::Number(const short&val)
	{
		value = new _DerivedNonBoolIntegralType<short>(val, TYPE_SHORT);
	}
	
	Number::Number(const unsigned short&val)
	{
		value = new _DerivedNonBoolIntegralType<unsigned short>(val, TYPE_UNSIGNEDSHORT);
	}
	
	Number::Number(const int&val)
	{
		value = new _DerivedNonBoolIntegralType<int>(val, TYPE_INT);
	}
	
	Number::Number(const unsigned int&val)
	{
		value = new _DerivedNonBoolIntegralType<unsigned int>(val, TYPE_UNSIGNEDINT);
	}
	
	Number::Number(const long&val)
	{
		value = new _DerivedNonBoolIntegralType<long>(val, TYPE_LONG);
	}
	
	Number::Number(const unsigned long&val)
	{
		value = new _DerivedNonBoolIntegralType<unsigned long>(val, TYPE_UNSIGNEDLONG);
	}
	
	Number::Number(const long long&val)
	{
		value = new _DerivedNonBoolIntegralType<long long>(val, TYPE_LONGLONG);
	}
	
	Number::Number(const unsigned long long&val)
	{
		value = new _DerivedNonBoolIntegralType<unsigned long long>(val, TYPE_UNSIGNEDLONGLONG);
	}
	
	Number::Number(const float&val)
	{
		value = new _DerivedNonBoolNumberType<float>(val, TYPE_FLOAT);
	}
	
	Number::Number(const double&val)
	{
		value = new _DerivedNonBoolNumberType<double>(val, TYPE_DOUBLE);
	}
	
	Number::Number(const long double&val)
	{
		value = new _DerivedNonBoolNumberType<long double>(val, TYPE_LONGDOUBLE);
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
		if(value==nullptr || num.value==nullptr)
		{
			//TODO replace with more specific exception type
			throw Exception("Cannot perform Math operations on an uninitialized Number object");
		}
		*value += *num.value;
		return *this;
	}
	
	Number& Number::operator-=(const Number&num)
	{
		if(value==nullptr || num.value==nullptr)
		{
			//TODO replace with more specific exception type
			throw Exception("Cannot perform Math operations on an uninitialized Number object");
		}
		*value -= *num.value;
		return *this;
	}
	
	Number& Number::operator*=(const Number&num)
	{
		if(value==nullptr || num.value==nullptr)
		{
			//TODO replace with more specific exception type
			throw Exception("Cannot perform Math operations on an uninitialized Number object");
		}
		*value *= *num.value;
		return *this;
	}
	
	Number& Number::operator/=(const Number&num)
	{
		if(value==nullptr || num.value==nullptr)
		{
			//TODO replace with more specific exception type
			throw Exception("Cannot perform Math operations on an uninitialized Number object");
		}
		*value /= *num.value;
		return *this;
	}
	
	Number& Number::operator%=(const Number&num)
	{
		if(value==nullptr || num.value==nullptr)
		{
			//TODO replace with more specific exception type
			throw Exception("Cannot perform Math operations on an uninitialized Number object");
		}
		*value %= *num.value;
		return *this;
	}
	
	Number& Number::operator++()
	{
		if(value == nullptr)
		{
			//TODO replace with more specific exception type
			throw Exception("Cannot perform Math operations on an uninitialized Number object");
		}
		*value++;
		return *this;
	}
	
	Number Number::operator-() const
	{
		return *this * -1;
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
	
	std::ostream& operator<<(std::ostream& stream, const Number& num)
	{
		if(num.value == nullptr)
		{
			stream << NULL_STRING;
			return stream;
		}
		return num.value->streamTo(stream);
	}
	
#define NUMBER_OPERATION_TONUMBER(operatr, type) \
	Number operator operatr(const Number&left, const type&right) \
	{ \
		if(left.value==nullptr) \
		{ \
			/*TODO replace with more specific exception type*/ \
			throw Exception("Cannot perform Math operations on an uninitialized Number object"); \
		} \
		return *left.value operatr *Number(right).value; \
	}
	
#define NUMBER_OPERATION_TOPRIMITIVE(operatr, type) \
	type operator operatr(const type&left, const Number&right) \
	{ \
		if(right.value==nullptr) \
		{ \
			/*TODO replace with more specific exception type*/ \
			throw Exception("Cannot perform Math operations on an uninitialized Number object"); \
		} \
		return *Number(left).value operatr *right.value; \
	}
	
#define NUMBER_COMPARISON_DEFINE(operatr, type, nullReturn) \
	bool operator operatr(const type&left, const Number&right) \
	{ \
		if(right.value==nullptr) \
		{ \
			return nullReturn; \
		} \
		return *Number(left).value operatr *right.value; \
	} \
	bool operator operatr(const Number&left, const type&right) \
	{ \
		if(left.value==nullptr) \
		{ \
			return nullReturn; \
		} \
		return *left.value operatr *Number(right).value; \
	}
	
#define NUMBER_COMPARISON_DEFINE_WITHEXCEPTION(operatr, type) \
	bool operator operatr(const type&left, const Number&right) \
	{ \
		if(right.value==nullptr) \
		{ \
			/*TODO replace with more specific exception type*/ \
			throw Exception("Cannot perform Math operations on an uninitialized Number object"); \
		} \
		return *Number(left).value operatr *right.value; \
	} \
	bool operator operatr(const Number&left, const type&right) \
	{ \
		if(left.value==nullptr) \
		{ \
			/*TODO replace with more specific exception type*/ \
			throw Exception("Cannot perform Math operations on an uninitialized Number object"); \
		} \
		return *left.value operatr *Number(right).value; \
	}
	
#define NUMBER_COMPARISON_SET(type) \
	NUMBER_COMPARISON_DEFINE(==, type, false) \
	NUMBER_COMPARISON_DEFINE(!=, type, true) \
	NUMBER_COMPARISON_DEFINE_WITHEXCEPTION(>, type) \
	NUMBER_COMPARISON_DEFINE_WITHEXCEPTION(>=, type) \
	NUMBER_COMPARISON_DEFINE_WITHEXCEPTION(<, type) \
	NUMBER_COMPARISON_DEFINE_WITHEXCEPTION(<=, type)
	
#define NUMBER_OPERATOR_SET(type) \
	NUMBER_OPERATION_TONUMBER(+, type) \
	NUMBER_OPERATION_TOPRIMITIVE(+, type) \
	NUMBER_OPERATION_TONUMBER(-, type) \
	NUMBER_OPERATION_TOPRIMITIVE(-, type) \
	NUMBER_OPERATION_TONUMBER(*, type) \
	NUMBER_OPERATION_TOPRIMITIVE(*, type) \
	NUMBER_OPERATION_TONUMBER(/, type) \
	NUMBER_OPERATION_TOPRIMITIVE(/, type) \
	NUMBER_OPERATION_TONUMBER(%, type) \
	NUMBER_OPERATION_TOPRIMITIVE(%, type) \
	NUMBER_COMPARISON_SET(type)
	
#define NUMBER_OPERATOR_SET_FLOATINGPOINT(type) \
	NUMBER_OPERATION_TONUMBER(+, type) \
	NUMBER_OPERATION_TOPRIMITIVE(+, type) \
	NUMBER_OPERATION_TONUMBER(-, type) \
	NUMBER_OPERATION_TOPRIMITIVE(-, type) \
	NUMBER_OPERATION_TONUMBER(*, type) \
	NUMBER_OPERATION_TOPRIMITIVE(*, type) \
	NUMBER_OPERATION_TONUMBER(/, type) \
	NUMBER_OPERATION_TOPRIMITIVE(/, type) \
	NUMBER_OPERATION_TOPRIMITIVE(%, type) \
	NUMBER_COMPARISON_SET(type)
	
	Number operator+(const Number&left, const Number&right)
	{
		if(left.value==nullptr || right.value==nullptr)
		{
			//TODO replace with more specific exception type
			throw Exception("Cannot perform Math operations on an uninitialized Number object");
		}
		return *left.value + *right.value;
	}
	
	Number operator-(const Number&left, const Number&right)
	{
		if(left.value==nullptr || right.value==nullptr)
		{
			//TODO replace with more specific exception type
			throw Exception("Cannot perform Math operations on an uninitialized Number object");
		}
		return *left.value - *right.value;
	}
	
	Number operator*(const Number&left, const Number&right)
	{
		if(left.value==nullptr || right.value==nullptr)
		{
			//TODO replace with more specific exception type
			throw Exception("Cannot perform Math operations on an uninitialized Number object");
		}
		return *left.value * *right.value;
	}
	
	Number operator/(const Number&left, const Number&right)
	{
		if(left.value==nullptr || right.value==nullptr)
		{
			//TODO replace with more specific exception type
			throw Exception("Cannot perform Math operations on an uninitialized Number object");
		}
		return *left.value / *right.value;
	}
	
	Number operator%(const Number&left, const Number&right)
	{
		if(left.value==nullptr || right.value==nullptr)
		{
			//TODO replace with more specific exception type
			throw Exception("Cannot perform Math operations on an uninitialized Number object");
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
	
	bool operator==(const Number&left, const Number&right)
	{
		if(left.value==nullptr)
		{
			if(right.value == nullptr)
			{
				return true;
			}
			return false;
		}
		return *left.value == *right.value;
	}
	
	bool operator!=(const Number&left, const Number&right)
	{
		if(left.value==nullptr)
		{
			if(right.value == nullptr)
			{
				return false;
			}
			return true;
		}
		return *left.value != *right.value;
	}
	
	bool operator>(const Number&left, const Number&right)
	{
		if(left.value==nullptr || right.value==nullptr)
		{
			//TODO replace with more specific exception type
			throw Exception("Cannot perform Math operations on an uninitialized Number object");
		}
		return *left.value > *right.value;
	}
	
	bool operator>=(const Number&left, const Number&right)
	{
		if(left.value==nullptr || right.value==nullptr)
		{
			//TODO replace with more specific exception type
			throw Exception("Cannot perform Math operations on an uninitialized Number object");
		}
		return *left.value >= *right.value;
	}
	
	bool operator<(const Number&left, const Number&right)
	{
		if(left.value==nullptr || right.value==nullptr)
		{
			//TODO replace with more specific exception type
			throw Exception("Cannot perform Math operations on an uninitialized Number object");
		}
		return *left.value < *right.value;
	}
	
	bool operator<=(const Number&left, const Number&right)
	{
		if(left.value==nullptr || right.value==nullptr)
		{
			//TODO replace with more specific exception type
			throw Exception("Cannot perform Math operations on an uninitialized Number object");
		}
		return *left.value <= *right.value;
	}
	
	NUMBER_COMPARISON_SET(bool)
	NUMBER_OPERATOR_SET(char)
	NUMBER_OPERATOR_SET(unsigned char)
	NUMBER_OPERATOR_SET(short)
	NUMBER_OPERATOR_SET(unsigned short)
	NUMBER_OPERATOR_SET(int)
	NUMBER_OPERATOR_SET(unsigned int)
	NUMBER_OPERATOR_SET(long)
	NUMBER_OPERATOR_SET(unsigned long)
	NUMBER_OPERATOR_SET(long long)
	NUMBER_OPERATOR_SET(unsigned long long)
	NUMBER_OPERATOR_SET_FLOATINGPOINT(float)
	NUMBER_OPERATOR_SET_FLOATINGPOINT(double)
	NUMBER_OPERATOR_SET_FLOATINGPOINT(long double)
}

#ifdef _MSC_VER
#pragma warning(pop)
#endif
