
#include "../Exception/BadAnyCastException.h"
#include <type_traits>

#ifdef _MSC_VER
#pragma warning(push)
#pragma warning(disable : 4521)
#endif

#pragma once

namespace GameLibrary
{
	template<class T>
	using StorageType = typename std::decay<T>::type;
	class Any
	{
	private:
		struct Base
		{
			virtual ~Base()
			{
				//
			}

			virtual Base* clone() const = 0;
		};

		template<typename T>
		struct Derived : Base
		{
			T value;

			template<typename U>
			Derived(U&& value) : value(std::forward<U>(value))
			{
				//
			}

			Base* clone() const
			{
				return new Derived<T>(value);
			}
		};

		Base* clone() const
		{
			if (ptr)
			{
				return ptr->clone();
			}
			else
			{
				return nullptr;
			}
		}

		Base* ptr;

	public:
		Any() : ptr(nullptr)
		{
			//
		}

		Any(Any& any) : ptr(any.clone())
		{
			//
		}

		Any(Any&& any) : ptr(any.ptr)
		{
			any.ptr = nullptr;
		}

		Any(const Any& any) : ptr(any.clone())
		{
			//
		}

		Any(const Any&& any) : ptr(any.clone())
		{
			//
		}

		template<class U>
		operator U()
		{
			return as<StorageType<U>>();
		}

		Any& operator=(const Any& any)
		{
			if (ptr == any.ptr)
			{
				return *this;
			}
			auto old_ptr = ptr;
			ptr = any.clone();

			if (old_ptr)
			{
				delete old_ptr;
			}

			return *this;
		}

		Any& operator=(Any&& any)
		{
			if (ptr == any.ptr)
			{
				return *this;
			}

			std::swap(ptr, any.ptr);

			return *this;
		}

		~Any()
		{
			if (ptr)
			{
				delete ptr;
			}
		}

		bool is_null() const
		{
			return !ptr;
		}

		bool not_null() const
		{
			return ptr!=nullptr;
		}

		template<typename U>
		Any(U&& value) : ptr(new Derived<StorageType<U>>(std::forward<U>(value)))
		{
			//
		}

		template<class U> bool is() const
		{
			typedef StorageType<U> T;
			auto derived = dynamic_cast<Derived<T>*> (ptr);
			return derived;
		}

		template<class U>
		StorageType<U>& as()
		{
			typedef StorageType<U> T;
			auto derived = dynamic_cast<Derived<T>*>(ptr);
			if (!derived)
			{
				throw BadAnyCastException(typeid(U).name());
			}
			return derived->value;
		}

		template<class U>
		const StorageType<U>& as()
		{
			typedef StorageType<U> T;
			auto derived = dynamic_cast<Derived<T>*>(ptr);
			if (!derived)
			{
				throw BadAnyCastException(typeid(U).name());
			}
			return derived->value;
		}
	};
}

#ifdef _MSC_VER
#pragma warning(pop)
#endif
