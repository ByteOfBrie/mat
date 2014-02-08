#ifndef MAT_H
#define MAT_H

#include <iostream>
#include <impl.hpp>

namespace mat
{
	template<typename _Tp = scalar_t>
	class mat
	{
	public:
		mat() : m_cx(0), m_cy(0), m_data(NULL) {}

		mat(_Tp* data, const size_t& cx, const size_t& cy, const bool& transpose = false) : m_cx(0), m_cy(0), m_data(NULL)
		{
			set(data, cx, cy, transpose);
		}

		mat(const mat& m) : m_cx(0), m_cy(0), m_data(NULL)
		{
			*this = m;
		}

		~mat()
		{
			set(NULL, 0, 0,false);
		}

		inline const size_t& cx() const
		{
			return m_cx;
		}

		inline const size_t& cy() const
		{
			return m_cy;
		}

                inline const _Tp& at(const size_t& x, const size_t& y) const
                {
                        return m_data[y * m_cx + x];
                }

                inline _Tp& at(const size_t& x, const size_t& y)
                {
                        return m_data[y * m_cx + x];
                }

                inline _Tp* data()
                {
                        return m_data;
                }

                inline const _Tp* data() const
                {
                        return m_data;
                }

		mat& operator=(const mat& m)
		{
			return set(m.data(), m.cx(), m.cy());
		}

		mat& operator+=(const mat& x)
		{
			assert(cx() == x.cx() && cy() == x.cy());
			impl::add(data(), m_cx, m_cy, data(), x.data());
			return *this;
		}

		mat& operator-=(const mat& x)
		{
			assert(cx() == x.cx() && cy() == x.cy());
			impl::sub(data(), m_cx, m_cy, data(), x.data());
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
		mat operator-(const mat& x) const
		{
			mat t(x);
			t -= *this;
			return t;
		}

		//m*x
		mat operator*(const _Tp& x) const
		{
			mat t(*this);
			t *= x;
			return t;
		}

		//m*=x
		mat& operator*=(const _Tp& x)
		{
			impl::smul(data(), m_cx, m_cy, data(), x);
			return *this;
		}

		//m*m;
		mat operator*(const mat& x) const
		{
			//s must mul x
			assert(cx() == x.cy());
			mat t;
			t.set(NULL, x.cx(), cy());
			impl::mul(t.data(), data(), cx(), cy(), x.data(), x.cx(), x.cy());
			return t;
		}

		//m/m;
		mat operator/(const mat& x) const
		{
			//x must be square
			assert(x.cx() == x.cy());
			assert(cx() == x.cx());
			mat t;
			t.set(NULL, x.cx(), cy());
			impl::div(t.data(), data(), cx(), cy(), x.data(), x.cx());
			return t;
		}

		//m^1;
		mat operator^(const int& dummy) const
		{
			mat t;
			t.set(data(), cx(), cy(), true);
			return t;
		}

		mat cholesky() const
		{
			//assert(cx() == cy());
			mat t;
			if(cx() != cy())
				return t;
			t.set(NULL, cx(), cy(), false, false);
			if (!impl::cholesky(t.data(), cx(), data()))
				t.set(NULL, 0, 0);
			return t;
		}

		//invert
		mat operator!() const
		{
			//x must be square
			//assert(cx() == cy());
			mat t;
			if (cx() != cy())
				return t;
			t.set(NULL, cx(), cx());
			if (!impl::inv(t.data(), cx(), cx(), data()))
				t.set(NULL, 0, 0);
			return t;
		}

		inline mat& zero(const ssize_t& cx = -1)
		{
			return set(NULL, cx, cx, false, true);
		}

		mat& set(const _Tp* d, const size_t& cx, const size_t& cy, const bool& transpose = false, const bool& zero = false)
		{
			if (cx * cy != mat::cx() * mat::cy()) {
				if (m_data)
					delete[] m_data;
				m_cx = transpose ? cy : cx;
				m_cy = transpose ? cx : cy;
				m_data = NULL;
				if (cx == 0 || cy == 0)
					return *this;
				m_data = new _Tp[cx * cy];
			}
			if (d) {
				if (transpose)
					impl::trans(data(), cx, cy, d);
				else
					impl::cpy(data(), cx, cy, d);
			} else {
				if(zero)
					impl::zero(data(), cx, cy);
			}
			return *this;
		}

		mat& id(const ssize_t& cx = -1)
		{
			if(cx < 0)
				set(NULL, cx, cx, false, false);
			impl::id(data(), cx);
			return *this;
		}

		_Tp dot(const mat& x) const
		{
			assert(cx() == x.cx());
			assert(cy() == 1 && x.cy() == 1);
			_Tp s = 0;
			for (size_t i = 0; i < cx(); i++)
				s += m_data[i] * x.m_data[i];
			return s;
		}

		_Tp len() const
		{
			assert(cy() == 1);
			return impl::sqrt(dot(*this));
		}

		mat normal() const
		{
			mat t(*this);
			t *= 1. / t.len();
			return t;
		}

		mat& normalize()
		{
			return *this *= 1. / len();
		}
	private:
		size_t m_cx, m_cy;
		_Tp* m_data;
	};
	
	template<typename _Tp>
	mat<_Tp> e(const size_t& x)
	{
		mat<_Tp> t;
		t.id(x);
		return t;
	}
	
	template<typename _Tp>
	mat<_Tp> rot(const _Tp& theta)
	{
		mat<_Tp> t;
		_Tp n[4] = {impl::cos(theta), -impl::sin(theta), impl::sin(theta), impl::cos(theta)};
		t.set(n, 2, 2);
		return t;
	}
	
	template<typename _Tp>
	void print(const mat<_Tp>& m)
	{
		impl::print(m.data(), m.cx(), m.cy());
	}
}

//1-m
template<typename _Tp>
mat::mat<_Tp>& operator-(const int& x, const mat::mat<_Tp>& m)
{
	mat::mat<_Tp> t;
	t.id() -= m;
	return t;
}

//x*m
template<typename _Tp>
mat::mat<_Tp> operator*(const _Tp& x, const mat::mat<_Tp>& m)
{
	return m * x;
}

#endif
