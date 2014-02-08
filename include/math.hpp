#ifndef MATH_HPP
#define MATH_HPP

namespace mat
{
	class mathutils
	{
	public:
		template<typename Tp>
		inline static Tp pi();
		template<typename Tp>
		inline static Tp todeg(const Tp& x);
		template<typename Tp>
		inline static Tp torad(const Tp& x);
		template<typename Tp>
		inline static void swap(Tp& a, Tp& b);
		template<typename Tp>
		inline static Tp abs(const Tp& x);
		template<typename Tp>
		inline static Tp epsilon();
		template<typename Tp>
		inline static Tp sqrt(const Tp& x);
		template<typename Tp>
		inline static Tp sin(const Tp& x);
		template<typename Tp>
		inline static Tp cos(const Tp& x);
	};
}

#include <math.impl.hpp>

#endif
