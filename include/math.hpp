#ifndef MATH_HPP
#define MATH_HPP

namespace mat
{
  template<>
  inline float pi<float>()
  {
    return 3.1415926535897932384626433832795;
  }

  template<>
  inline double pi<double>()
  {
    return 3.1415926535897932384626433832795;
  }

	template<typename _Tp>
	inline _Tp deg(const _Tp& x)
	{
  	return x * pi<_Tp>() / ((_Tp)180.);
	}

	template<typename _Tp>
	inline _Tp rad(const _Tp& x)
	{
  	return x / ((_Tp)180.) * pi<_Tp>();
	}
}

#endif
