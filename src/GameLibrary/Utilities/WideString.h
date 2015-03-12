
#pragma once

#include <string>

#ifdef __OBJC__
	#import <Foundation/Foundation.h>
#endif

#ifndef _STRING_STANDALONE
#include "../Types.h"
namespace GameLibrary
{
#endif
	#define _STRING_CLASS WideString
	#define _STRING_TYPE wchar_t
	
	class _STRING_CLASS;

	#ifndef _STRING_STANDALONE
		#define _WIDESTRING_STRING_ENABLED
	#endif

	#ifdef _WIDESTRING_STRING_ENABLED
		class String;
	#endif
	
	class _STRING_CLASS
	{
		#ifdef _WIDESTRING_STRING_ENABLED
			friend class String;
		#endif
		//std::string
		friend _STRING_CLASS operator+(const _STRING_CLASS&left, const std::string&right);
		friend _STRING_CLASS operator+(const std::string&left, const _STRING_CLASS&right);
		//const std::wstring
		friend _STRING_CLASS operator+(const _STRING_CLASS&left, const std::wstring&right);
		friend _STRING_CLASS operator+(const std::wstring&left, const _STRING_CLASS&right);
		//const char
		friend _STRING_CLASS operator+(const _STRING_CLASS&left, const char&right);
		friend _STRING_CLASS operator+(const char&left, const _STRING_CLASS&right);
		//const char*
		friend _STRING_CLASS operator+(const _STRING_CLASS&left, const char*right);
		friend _STRING_CLASS operator+(const char*left, const _STRING_CLASS&right);
		#ifdef _WIDESTRING_STRING_ENABLED
			//WideString
			friend _STRING_CLASS operator+(const _STRING_CLASS&left, const String&right);
			friend String operator+(const String&left, const _STRING_CLASS&right);
		#endif
		#ifdef __OBJC__
			//NSString*
			friend _STRING_CLASS operator+(const _STRING_CLASS&left, const NSString*&right);
			friend _STRING_CLASS operator+(const NSString*&left, const _STRING_CLASS&right);
		#endif
		
	public:
		_STRING_CLASS(const std::wstring&);
		_STRING_CLASS(const std::string&);
		_STRING_CLASS(const char&);
		_STRING_CLASS(const char*);
		_STRING_CLASS(const char*str, size_t length);
		#ifdef _WIDESTRING_STRING_ENABLED
			_STRING_CLASS(const String&);
		#endif
		#ifdef __OBJC__
			_STRING_CLASS(const NSString*&);
		#endif
		
		#ifdef _WIDESTRING_STRING_ENABLED
			String toString() const;
		#endif
		
		operator std::wstring() const;
		operator std::string() const;
		#ifdef __OBJC__
			operator NSString*() const;
		#endif
		
		void append(const char*str, size_t length);
		_STRING_CLASS& operator+=(const std::wstring&);
		_STRING_CLASS& operator+=(const std::string&);
		_STRING_CLASS& operator+=(const char&);
		_STRING_CLASS& operator+=(const char*);
		#ifdef _WIDESTRING_STRING_ENABLED
			_STRING_CLASS& operator+=(const String&);
		#endif
		#ifdef __OBJC__
			_STRING_CLASS& operator+=(const NSString*&);
		#endif
		
		void set(const char*str, size_t length);
		_STRING_CLASS& operator=(const std::wstring&);
		_STRING_CLASS& operator=(const std::string&);
		_STRING_CLASS& operator=(const char&);
		_STRING_CLASS& operator=(const char*);
		#ifdef _WIDESTRING_STRING_ENABLED
			_STRING_CLASS& operator=(const String&);
		#endif
		#ifdef __OBJC__
			_STRING_CLASS& operator=(const NSString*&);
		#endif
		
		#include "StringClass.h.impl"
	//}
	
	//const std::wstring
	_STRING_CLASS operator+(const _STRING_CLASS&left, const std::wstring&right);
	_STRING_CLASS operator+(const std::wstring&left, const _STRING_CLASS&right);
	//const std::string
	_STRING_CLASS operator+(const _STRING_CLASS&left, const std::string&right);
	_STRING_CLASS operator+(const std::string&left, const _STRING_CLASS&right);
	//const char
	_STRING_CLASS operator+(const _STRING_CLASS&left, const char&right);
	_STRING_CLASS operator+(const char&left, const _STRING_CLASS&right);
	//const char*
	_STRING_CLASS operator+(const _STRING_CLASS&left, const char*right);
	_STRING_CLASS operator+(const char*left, const _STRING_CLASS&right);
	#ifdef _WIDESTRING_STRING_ENABLED
		//String
		_STRING_CLASS operator+(const _STRING_CLASS&left, const String&right);
	#endif
	#ifdef __OBJC__
		//NSString*
		_STRING_CLASS operator+(const _STRING_CLASS&left, const NSString*&right);
		_STRING_CLASS operator+(const NSString*&left, const _STRING_CLASS&right);
	#endif
	
#ifndef _STRING_STANDALONE
}
#endif

#undef _STRING_CLASS
#undef _STRING_TYPE
