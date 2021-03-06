﻿#pragma once
#include <xx_mempool.h>
#include <iostream>
#include <type_traits>
#include <time.h>						// for clock()
namespace xx
{
	template<typename T, typename ENABLE = void>
	struct DumpCore
	{
		static void Dump(T const& o);
	};

	template<typename T>
	struct DumpCore<T, std::enable_if_t<(std::is_pointer<T>::value && IsObject_v<T>) || IsRef_v<T>>>
	{
		inline static void Dump(T const& o)
		{
			if (!o) return;
			String_v str(o->mempool());
			o->ToString(*str);
			std::cout << str->C_str() << std::endl;
		}
	};
	template<typename T>
	struct DumpCore<T, std::enable_if_t<!std::is_pointer<T>::value && IsObject_v<T>>>
	{
		inline static void Dump(T const& o)
		{
			String_v str(o.mempool());
			o.ToString(*str);
			std::cout << str->C_str() << std::endl;
		}
	};

	template<typename T>
	void Dump(T const& o)
	{
		DumpCore<T>::Dump(o);
	}

	inline int64_t GetCurrentMS()
	{
		return (int64_t)clock();
	}
}
