
#pragma once

#include "String.h"
#include <type_traits>
#include <sstream>
#include <iomanip>

namespace GameLibrary
{
	template<typename T, typename Sign>
	struct has_toString
	{
		typedef char yes[1];
		typedef char no [2];
		template <typename U, U> struct type_check;
		template <typename _1> static yes &chk(type_check<Sign, &_1::toString> *);
		template <typename   > static no  &chk(...);
		static bool const value = sizeof(chk<T>(0)) == sizeof(yes);
    };
	
	template<bool B> struct is_true { };
	
	template <typename U, typename E = void>
	struct Stringifier;
	
	template <typename U>
	struct Stringifier<U, typename std::enable_if<std::is_class<U>::value>::type>
	{
	private:
		template<typename T, bool B>
		struct StringifierImpl
		{
		private:
			String* createStringImpl(const U*value, is_true<true>)
			{
				if(value == nullptr)
				{
					return new String("null");
				}
				return new String(value->toString());
			}
			
			String* createStringImpl(const U*value, is_true<false>)
			{
				if(value == nullptr)
				{
					return new String("null");
				}
				std::stringstream ss;
				ss << typeid(U).name() << " @ 0x" << std::setfill('0') << std::setw(sizeof(value)) << std::hex << ((uintptr_t)value);
				return new String(ss.str());
			}
			
		public:
			String* createString(const T*value)
			{
				return createStringImpl(value, is_true<B>());
			}
		};
		
	public:
		String convertToString(const U*value)
		{
			String* str = StringifierImpl<U, has_toString<U, String(U::*)()const>::value>().createString(value);
			String ret(*str);
			delete str;
			return ret;
		}
	};
	
	template <typename U>
	struct Stringifier<U, typename std::enable_if<!std::is_class<U>::value && std::is_integral<U>::value && !std::is_pointer<U>::value>::type>
	{
	public:
		String convertToString(const U*value)
		{
			if(value == nullptr)
			{
				return "null";
			}
			return std::to_string(*value);
		}
	};
	
	template <typename U>
	struct Stringifier<U, typename std::enable_if<!std::is_class<U>::value && std::is_pointer<U>::value>::type>
	{
	public:
		typedef const signed char* string_ptr;

		String convertToString(const string_ptr* value)
		{
			if(value == nullptr)
			{
				return "null";
			}
			else if((*value) == nullptr)
			{
				return "";
			}
			else
			{
				return (*value);
			}
		}
		
		String convertToString(const U*value)
		{
			if(value == nullptr)
			{
				return "null";
			}
			std::stringstream ss;
			ss << "0x" << std::setfill('0') << std::setw(sizeof(*value)) << std::hex << ((uintptr_t)(*value));
			return ss.str();
		}
	};
	
	template <typename U>
	struct Stringifier<U, typename std::enable_if<!std::is_class<U>::value && !std::is_integral<U>::value && !std::is_pointer<U>::value>::type>
	{
	public:
		String convertToString(const bool*value)
		{
			if(value == nullptr)
			{
				return "null";
			}
			if((*value))
			{
				return "true";
			}
			return "false";
		}
		
		String convertToString(const U*value)
		{
			if(value == nullptr)
			{
				return "null";
			}
			std::stringstream ss;
			ss << "0x" << std::setfill('0') << std::setw(sizeof(value)) << std::hex << ((uintptr_t)(value));
			return ss.str();
		}
	};
}
