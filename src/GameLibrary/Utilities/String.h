
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
	#define _STRING_CLASS String
	#define _STRING_TYPE char
	
	class _STRING_CLASS;
	
	class _STRING_CLASS
	{
		//std::string
		friend _STRING_CLASS operator+(const _STRING_CLASS&left, const std::string&right);
		friend _STRING_CLASS operator+(const std::string&left, const _STRING_CLASS&right);
		//const std::wstring
		friend _STRING_CLASS operator+(const _STRING_CLASS&left, const std::wstring&right);
		friend _STRING_CLASS operator+(const std::wstring&left, const _STRING_CLASS&right);
		//const wchar_t
		friend _STRING_CLASS operator+(const _STRING_CLASS&left, const wchar_t&right);
		friend _STRING_CLASS operator+(const wchar_t&left, const _STRING_CLASS&right);
		//const wchar_t*
		friend _STRING_CLASS operator+(const _STRING_CLASS&left, const wchar_t*right);
		friend _STRING_CLASS operator+(const wchar_t*left, const _STRING_CLASS&right);
		#ifdef __OBJC__
			//NSString*
			friend _STRING_CLASS operator+(const _STRING_CLASS&left, const NSString*&right);
			friend _STRING_CLASS operator+(const NSString*&left, const _STRING_CLASS&right);
		#endif
		
	public:
		_STRING_CLASS(const std::string&);
		_STRING_CLASS(const std::wstring&);
		_STRING_CLASS(const wchar_t&);
		_STRING_CLASS(const wchar_t*);
		_STRING_CLASS(const wchar_t*str, size_t length);
		#ifdef __OBJC__
			_STRING_CLASS(const NSString*&);
		#endif
		
		operator std::string() const;
		operator std::wstring() const;
		#ifdef __OBJC__
			operator NSString*() const;
		#endif
		
		void append(const wchar_t*str, size_t length);
		_STRING_CLASS& operator+=(const std::string&);
		_STRING_CLASS& operator+=(const std::wstring&);
		_STRING_CLASS& operator+=(const wchar_t&);
		_STRING_CLASS& operator+=(const wchar_t*);
		#ifdef __OBJC__
			_STRING_CLASS& operator+=(const NSString*&);
		#endif
		
		void set(const wchar_t*str, size_t length);
		_STRING_CLASS& operator=(const std::string&);
		_STRING_CLASS& operator=(const std::wstring&);
		_STRING_CLASS& operator=(const wchar_t&);
		_STRING_CLASS& operator=(const wchar_t*);
		#ifdef __OBJC__
			_STRING_CLASS& operator=(const NSString*&);
		#endif
		
		#include "StringClass.h.impl"
	//}
	
	//const std::string
	String operator+(const String&left, const std::string&right);
	String operator+(const std::string&left, const String&right);
	//const std::wstring
	String operator+(const String&left, const std::wstring&right);
	String operator+(const std::wstring&left, const String&right);
	//const wchar_t
	String operator+(const String&left, const wchar_t&right);
	String operator+(const wchar_t&left, const String&right);
	//const wchar_t*
	String operator+(const String&left, const wchar_t*right);
	String operator+(const wchar_t*left, const String&right);
	#ifdef __OBJC__
		//NSString*
		String operator+(const String&left, const NSString*&right);
		String operator+(const NSString*&left, const String&right);
	#endif
	
#ifndef _STRING_STANDALONE
}
#endif

#undef _STRING_CLASS
#undef _STRING_TYPE
