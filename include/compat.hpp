#ifndef COMPAT_H
#define COMPAT_H

/*Modify this file as neccicary to port to any C++ supporting platform*/

#include <alloca.h>
#include <cstddef>
#include <algorithm>
#include <limits>
#include <cmath>
#include <cstdio>

#define MAT_ALLOCA alloca

namespace mat
{
	namespace impl
	{
		namespace compat = ::std;
		
		template<typename _Tp>
		inline void printt(const _Tp& f);
		
		template<>
		inline void printt(const float& f)
		{
			printf("%1.2f", f);
		}
		
		inline void print(const char* str)
		{
			printf(str);
		}
	}
}

#endif

