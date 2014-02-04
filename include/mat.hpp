#ifndef MAT_H
#define MAT_H

#include <impl.hpp>

namespace mat
{
	template<typename _Tp = scalar_t>
	class mat
	{
	public:
		mat() : m_cx(0), m_cy(0), m_data(NULL) {}
		mat(_Tp* data, const size_t& cx, const size_t& cy, const bool& transpose = false) : m_cx(0), m_cy(0), m_data(NULL) {set(data, cx, cy, transpose);}
		mat(const mat& m) : m_cx(0), m_cy(0), m_data(NULL) {*this = m;}
		~mat() {set(NULL, 0, 0,false);}
		const size_t& cx() const {return m_cx;}
		const size_t& cy() const {return m_cy;}
		mat& operator=(const mat& m)
		{
			return set(m.data(), cx(), cy());
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
			t.set(data(), m_cx, m_cy, true);
			return t;
		}
		//invert
		mat operator!() const
		{
			//x must be square
			assert(cx() == cy());
			mat t;
			t.set(NULL, cx(), cx());
			inv(t.data(), cx(), cx(), data());
			return t;
		}
		mat& set(const _Tp* d, const size_t& cx, const size_t& cy, const bool& transpose = false)
		{
			if (m_data)
				delete[] m_data;
			m_cx = 0;
			m_cy = 0;
			m_data = NULL;
			if (cx == 0 || cy == 0)
				return *this;
			m_data = new _Tp[cx * cy];
			m_cx = cy;
			m_cy = cx;
			if (d) {
				if (transpose)
					impl::trans(data(), cx, cy, d);
				else
					impl::cpy(data(), cx, cy, d);
			}
			return *this;
		}
		mat& id(const size_t& cx)
		{
			if (cx == 0)
				set(NULL, 0, 0);
			m_cx = cx;
			m_cy = cx;
			m_data = new _Tp[cx * cx];
			impl::id(data(), cx);
			return *this;
		}
		const _Tp& at(const size_t& x, const size_t& y) const
		{
			return m_data[y * m_cx + x];
		}
		inline _Tp& at(const size_t& x, const size_t& y)
		{
			return m_data[y * m_cx + x];
		}
		_Tp dot(const mat& x)
		{
			assert(cx() == x.cx());
			assert(cy() == 1 && x.cy() == 1);
			_Tp s = 0;
			for (size_t i = 0; i < cx(); i++)
				s += m_data[i] * x.m_data[i];
			return s;
		}
		_Tp len()
		{
			return impl::sqrt(dot(*this));
		}
		inline _Tp* data()
		{
			return m_data;
		}
		inline const _Tp* data() const
		{
			return m_data;
		}
		//todo: debug output functions
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
