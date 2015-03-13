
#pragma once

#include "String.h"
#include "WideString.h"
#include <string>
#include <limits>

namespace GameLibrary
{
	template <typename S, typename D>
	D CharForceConvert(const S&src)
	{
		if(sizeof(S) < sizeof(D))
		{
			return (D)src;
		}
		else if(sizeof(S) > sizeof(D))
		{
			S d_max = (S)std::numeric_limits<D>::max();
			if(src >= d_max)
			{
				if(sizeof(D) >= 2)
				{
					return (D)0xfffd;
				}
				else
				{
					return (D)'?';
				}
			}
			else
			{
				return (D)src;
			}
		}
		else
		{
			return (D)src;
		}
	}
	
	template<typename S, typename D>
	std::basic_string<D, std::char_traits<D>, std::allocator<D> > StringForceConvert(const std::basic_string<S, std::char_traits<S>, std::allocator<S> > &src)
	{
		if(sizeof(S) < sizeof(D))
		{
			size_t size = src.length();
			std::basic_string<D, std::char_traits<D>, std::allocator<D> > dst;
			dst.resize(size+1);
			for(size_t i=0; i<size; i++)
			{
				dst.at(i) = (D)src.at(i);
			}
			dst.at(size) = NULL;
			return dst;
		}
		else if(sizeof(S) > sizeof(D))
		{
			size_t size = src.length();
			S d_max = (S)std::numeric_limits<D>();
			std::basic_string<D, std::char_traits<D>, std::allocator<D> > dst;
			dst.resize(size+1);
			for(size_t i=0; i<size; i++)
			{
				if(src.at(i) >= d_max)
				{
					if(sizeof(D) >= 2)
					{
						dst.at(i) = (D)0xfffd;
					}
					else
					{
						dst.at(i) = (D)'?';
					}
				}
				else
				{
					d.at(i) = (D)src.at(i);
				}
			}
			dst.at(size) = NULL;
			return dst;
		}
		else
		{
			return std::basic_string<D, std::char_traits<D>, std::allocator<D> >((const D*)src.c_str(), ((const D*)src.c_str()) + src.length());
		}
	}
	
	template<typename D>
	std::basic_string<D, std::char_traits<D>, std::allocator<D> > StringForceConvert(const String&src)
	{
		if(sizeof(String::char_type) < sizeof(D))
		{
			size_t size = src.length();
			std::basic_string<D, std::char_traits<D>, std::allocator<D> > dst;
			dst.resize(size+1);
			for(size_t i=0; i<size; i++)
			{
				dst.at(i) = (D)src.charAt(i);
			}
			dst.at(size) = NULL;
			return dst;
		}
		else if(sizeof(String::char_type) > sizeof(D))
		{
			size_t size = src.length();
			String::char_type d_max = (String::char_type)std::numeric_limits<D>::max();
			std::basic_string<D, std::char_traits<D>, std::allocator<D> > dst;
			dst.resize(size+1);
			for(size_t i=0; i<size; i++)
			{
				if(src.charAt(i) >= d_max)
				{
					if(sizeof(D) >= 2)
					{
						dst.at(i) = (D)0xfffd;
					}
					else
					{
						dst.at(i) = (D)'?';
					}
				}
				else
				{
					dst.at(i) = (D)src.charAt(i);
				}
			}
			dst.at(size) = NULL;
			return dst;
		}
		else
		{
			return std::basic_string<D, std::char_traits<D>, std::allocator<D> >((const D*)((const String::char_type*)src), ((const D*)((const String::char_type*)src)) + src.length());
		}
	}
	
	template<typename D>
	std::basic_string<D, std::char_traits<D>, std::allocator<D> > StringForceConvert(const WideString&src)
	{
		if(sizeof(WideString::char_type) < sizeof(D))
		{
			size_t size = src.length();
			std::basic_string<D, std::char_traits<D>, std::allocator<D> > dst;
			dst.resize(size+1);
			for(size_t i=0; i<size; i++)
			{
				dst.at(i) = (D)src.charAt(i);
			}
			dst.at(size) = NULL;
			return dst;
		}
		else if(sizeof(WideString::char_type) > sizeof(D))
		{
			size_t size = src.length();
			WideString::char_type d_max = (WideString::char_type)std::numeric_limits<D>::max();
			std::basic_string<D, std::char_traits<D>, std::allocator<D> > dst;
			dst.resize(size+1);
			for(size_t i=0; i<size; i++)
			{
				if(src.charAt(i) >= d_max)
				{
					if(sizeof(D) >= 2)
					{
						dst.at(i) = (D)0xfffd;
					}
					else
					{
						dst.at(i) = (D)'?';
					}
				}
				else
				{
					dst.at(i) = (D)src.charAt(i);
				}
			}
			dst.at(size) = NULL;
			return dst;
		}
		else
		{
			return std::basic_string<D, std::char_traits<D>, std::allocator<D> >((const D*)((const WideString::char_type*)src), ((const D*)((const WideString::char_type*)src)) + src.length());
		}
	}
}
