
#pragma once

#include "String.h"
#include "WideString.h"
#include <string>
#include <limits>

namespace GameLibrary
{
	template<typename S, typename D>
	std::basic_string<D, std::char_traits<D>, std::allocator<D> > StringForceConvert(const std::basic_string<S, std::char_traits<S>, std::allocator<S> > &src)
	{
		if(sizeof(S) < sizeof(D))
		{
			size_t size = src.length();
			std::basic_string<D, std::char_traits<D>, std::allocator<D> > dst(size);
			for(size_t i=0; i<size; i++)
			{
				dst.at(i) = (D)src.at(i);
			}
			return dst;
		}
		else if(sizeof(S) > sizeof(D))
		{
			size_t size = src.length();
			S d_max = (S)std::numeric_limits<D>();
			std::basic_string<D, std::char_traits<D>, std::allocator<D> > dst(size);
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
			return dst;
		}
		else
		{
			return std::basic_string<D, std::char_traits<D>, std::allocator<D> >((D*)src.c_str(), src.length());
		}
	}
	
	template<typename D>
	std::basic_string<D, std::char_traits<D>, std::allocator<D> > StringForceConvert(const String&src)
	{
		if(sizeof(char) < sizeof(D))
		{
			size_t size = src.length();
			std::basic_string<D, std::char_traits<D>, std::allocator<D> > dst(size);
			for(size_t i=0; i<size; i++)
			{
				dst.at(i) = (D)src.at(i);
			}
			return dst;
		}
		else if(sizeof(char) > sizeof(D))
		{
			size_t size = src.length();
			char d_max = (char)std::numeric_limits<D>();
			std::basic_string<D, std::char_traits<D>, std::allocator<D> > dst(size);
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
			return dst;
		}
		else
		{
			return std::basic_string<D, std::char_traits<D>, std::allocator<D> >((D*)src.c_str(), src.length());
		}
	}
	
	template<typename D>
	std::basic_string<D, std::char_traits<D>, std::allocator<D> > StringForceConvert(const WideString&src)
	{
		if(sizeof(wchar_t) < sizeof(D))
		{
			size_t size = src.length();
			std::basic_string<D, std::char_traits<D>, std::allocator<D> > dst(size);
			for(size_t i=0; i<size; i++)
			{
				dst.at(i) = (D)src.at(i);
			}
			return dst;
		}
		else if(sizeof(wchar_t) > sizeof(D))
		{
			size_t size = src.length();
			wchar_t d_max = (wchar_t)std::numeric_limits<D>();
			std::basic_string<D, std::char_traits<D>, std::allocator<D> > dst(size);
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
			return dst;
		}
		else
		{
			return std::basic_string<D, std::char_traits<D>, std::allocator<D> >((D*)src.c_str(), src.length());
		}
	}
}
