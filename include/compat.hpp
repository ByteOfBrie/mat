#ifndef COMPAT_H
#define COMPAT_H

#include <config.hpp>

#ifndef MAT_IMPL_NO_STL
# include <cstddef>
# include <cstdio>
# include <algorithm>
# include <limits>
# ifndef MAT_IMPL_NO_MATH
#  include <cmath>
# endif
#else
# include <stddef.h>
# include <stdio.h>
# include <float.h>
# ifndef MAT_IMPL_NO_MATH
#  include <math.h>
# endif
#endif

namespace mat
{
	template<typename _Tp>
	inline _Tp sqrt(const _Tp& x);
	template<typename _Tp>
	inline _Tp sin(const _Tp& x);
	template<typename _Tp>
	inline _Tp cos(const _Tp& x);
	
	typedef MAT_SCALAR_TYPE scalar_t;

	namespace impl
	{
#ifndef MAT_IMPL_NO_STL
		namespace compat = ::std;
#else
		/*for arduino compatibility*/
		namespace compat
		{
			template<typename _Tp>
			_Tp abs(const _Tp& x)
			{
				if (x > 0)
					return x;
				else
					return -x;
			}
			template<typename T>
			void swap(T& a, T& b)
			{
				T c(a);
				a = b;
				b = c;
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

#ifndef MAT_IMPL_NO_MATH		
		template<typename _Tp>
		inline _Tp sqrt(const _Tp& x)
		{
			return ::sqrt(x);
		}

		template<typename _Tp>
		inline _Tp sin(const _Tp& x)
		{
			return ::sin(x);
		}

		template<typename _Tp>
		inline _Tp cos(const _Tp& x)
		{
			return ::cos(x);
		}
#endif
	}
}

#include <math.hpp>

#endif

