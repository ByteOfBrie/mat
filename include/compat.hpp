#ifndef COMPAT_H
#define COMPAT_H

/*may need to replace with correct alloca header*/
#include <alloca.h>
#define MAT_ALLOCA alloca
//#define MAT_IMPL_USE_STD // for platforms without stl
//#define MAT_IPML_NO_MATH // for platforms without math.h

#ifdef MAT_IMPL_USE_STD
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

