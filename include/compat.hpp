#ifndef COMPAT_H
#define COMPAT_H

/*may need to replace with correct alloca header*/
#include <alloca.h>

#ifdef MAT_IMPL_USE_STD
# include <cstddef>
# include <cstdio>
# include <algorithm>
# include <limits>
# include <cmath>
#else
# include <stddef.h>
# include <stdio.h>
# include <limits.h>
#endif

#define MAT_ALLOCA alloca

namespace mat
{
	namespace impl
	{
#ifdef MAT_IMPL_USE_STD
		namespace compat = ::std;
#else
		/*for arduino compatibility*/
		namespace compat
		{
			template<typename _Tp>
			_Tp abs(const _Tp& x)
			{
				if(x > 0)
					return x;
				else
					return -x;
			}
			template<typename T>
			void swap(T& a, T& b)
			{
				T c(a);
				a=b;
				b=c;
			}
			template<typename _Tp>
			struct numeric_limits;

			template<>
			struct numeric_limits<float>
			{
				static inline float epsilon()
				{
					return FLT_EPSILON;
				}
			};

			template<>
			struct numeric_limits<double>
			{
				static inline double epsilon()
				{
					return DBL_EPSILON;
				}
			};
		}
#endif
		
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

