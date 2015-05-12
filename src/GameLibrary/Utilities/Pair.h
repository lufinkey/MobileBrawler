
#pragma once

#include "String.h"
#include <type_traits>

namespace GameLibrary
{
	template<class T1, class T2>
	class Pair
	{
	public:
		T1 first;
		T2 second;

		typedef T1 first_type;
		typedef T2 second_type;
		typedef Pair<T1, T2> pair_type;

		Pair() : first(), second()
		{
			//
		}

		Pair(const T1& v1, const T2& v2) : first(v1), second(v2)
		{
			//
		}

		Pair(const pair_type& p) : first(p.first), second(p.second)
		{
			//
		}

		/*template<class Other1, class Other2,
			class = typename enable_if<is_convertible<const O1&, T1>::value
				&& is_convertible<const O2&, T2>::value, void>::type>
		Pair(const Pair<Other1, Other2>& p) : first(p.first), second(p.second)
		{
			//
		}*/

		pair_type& operator=(const pair_type& p)
		{
			first = p.first;
			second = p.second;
			return *this;
		}

		template<class Other1, class Other2>
		pair_type& operator=(const Pair<Other1, Other2>& p)
		{
			first = p.first;
			second = p.second;
			return *this;
		}
		
		String toString() const
		{
			return "Pair( " + Stringifier<T1>().convertToString(&first) + ", " + Stringifier<T2>().convertToString(&second) + " )";
		}
	};
}