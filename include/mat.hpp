#ifndef MAT_H
#define MAT_H

#include <impl.hpp>
#include <assert.h>

namespace mat
{
	template<typename _Tp>
	class mat {
	public:
		mat() : m_cx(0), m_cy(0), m_data(NULL) {}
		mat(_Tp* data, const size_t& cx, const size_t& cy, const bool& transpose = false) {set(data, cx, cy, transpose);}
		mat(const mat& m) {*this = m;}
		~mat() {set(NULL, 0, 0,false);}
		const size_t& cx() {return m_cx;}
		const size_t& cy() {return m_cy;}
		mat& operator=(const mat& m)
		{
			return set(m.m_data, cx(), cy(), false);
		}
		mat& operator+=(const mat& x)
		{
			assert(cx() == x.cx() && cy() == x.cy());
			impl::add(m_data, m_cx, m_cy, m_data, x.m_data);
			return *this;
		}
		mat& operator-=(const mat& x)
		{
			assert(cx() == x.cx() && cy() == x.cy());
			impl::sub(m_data, m_cx, m_cy, m_data, x.m_data);
			return *this;
		}
		//m+m;
		mat operator+(const mat& x)
		{
			mat t(x);
			t += *this;
			return t;
		}
		//m-m;
		mat operator-(const mat& x)
		{
			mat t(x);
			t -= *this;
			return t;
		}
		//m*x
		mat operator*(const _Tp& x)
		{
			mat t(*this);
			t *= x;
			return t;
		}
		//m*=x
		mat& operator*=(const _Tp& x)
		{
			impl::smul(m_data, m_cx, m_cy, m_data, x);
			return *this;
		}
		//m*m;
		mat operator*(const mat& x)
		{
			//s must mul x
			assert(cx() == x.cy());
			mat t;
			t.set(NULL, x.cx(), cy(), false)
			impl::mul(t.m_data, m_data, cx(), cy(), x.m_data, x.cx(), x.cy());
			return t;
		}
		//m/m;
		mat operator/(const mat& x)
		{
			//x must be square
			assert(x.cx() == x.cy());
			assert(cx() == x.cx());
			mat t;
			t.set(NULL, x.cx(), cy(), false)
			impl::div(t.m_data, m_data, cx(), cy(), x.m_data, x.cx(), x.cy());
			return t;
		}
		//m^1;
		mat operator^(const int& dummy)
		{
			mat t;
			t.set(m_data, m_cx, m_cy, 1);
			return t;
		}
		mat& set(const _Tp* data, const size_t& cx, const size_t& cy, const bool& transpose)
		{
			if(m_data)
				delete[] m_data;
			m_cx = 0;
			m_cy = 0;
			if(cx == 0 || cy == 0)
				return *this;
			m_data = new _Tp[cx * cy];
			if(data) {
				if(transpose) {
					m_cx = cy;
					m_cy = cx;
					impl::trans(m_data, cx, cy, data);
				} else {
					m_cx = cx;
					m_cy = cy;
					impl::cpy(m_data, cx, cy, data);
				}
			}
			return *this;
		}
		mat& id(const size_t& cx)
		{
			if(cx == 0)
				set(NULL, 0, 0, false);
			m_cx = cx;
			m_cy = cx;
			m_data = new _Tp[cx * cx];
			impl::id(m_data, cx);
			return *this;
		}
		const _Tp& at(const size_t& x, const size_t& y) const
		{
			return m_data[y * m_cx + x];
		}
		_Tp& at(const size_t& x, const size_t& y)
		{
			return m_data[y * m_cx + x];
		}
	private:
		size_t m_cx, m_cy;
		float* m_data;
	};
	
	template<typename _Tp>
	mat<_Tp> e(const size_t& x)
	{
		mat t;
		t.id(x);
		return t;
	}
}

//1-m
template<typename _Tp>
mat<_Tp>& operator-(const int& x, const mat<_Tp>& m)
{
	mat<_Tp> t;
	return t.id() -= m;
}

//x*m
template<typename _Tp>
mat<_Tp> operator*(const _Tp& x, const mat<_Tp>& m)
{
	return m * x;
}

#endif
