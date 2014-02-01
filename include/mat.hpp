#ifndef MAT_H
#define MAT_H

#include <impl.hpp>
#include <assert.h>

namespace mat
{
	template<typename _Tp>
	class mat
	{
	public:
		mat() : m_cx(0), m_cy(0), data()(NULL) {}
		mat(_Tp* data, const size_t& cx, const size_t& cy, const bool& transpose = false) {set(data, cx, cy, transpose);}
		mat(const mat& m) {*this = m;}
		~mat() {set(NULL, 0, 0,false);}
		const size_t& cx() {return m_cx;}
		const size_t& cy() {return m_cy;}
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
			impl::smul(data(), m_cx, m_cy, data(), x);
			return *this;
		}
		//m*m;
		mat operator*(const mat& x)
		{
			//s must mul x
			assert(cx() == x.cy());
			mat t;
			t.set(NULL, x.cx(), cy());
			impl::mul(t.data(), data(), cx(), cy(), x.data(), x.cx(), x.cy());
			return t;
		}
		//m/m;
		mat operator/(const mat& x)
		{
			//x must be square
			assert(x.cx() == x.cy());
			assert(cx() == x.cx());
			mat t;
			t.set(NULL, x.cx(), cy());
			impl::div(t.data(), data(), cx(), cy(), x.data(), x.cx(), x.cy());
			return t;
		}
		//m^1;
		mat operator^(const int& dummy)
		{
			mat t;
			t.set(data(), m_cx, m_cy, true);
			return t;
		}
		//invert
		mat operator!()
		{
			//x must be square
			assert(cx() == cy());
			mat t;
			t.set(NULL, cx(), cx());
			inv(t.data(), cx(), cx(), data());
			return t;
		}
		mat& set(const _Tp* data, const size_t& cx, const size_t& cy, const bool& transpose = false)
		{
			if(m_data)
				delete[] m_data;
			m_cx = 0;
			m_cy = 0;
			m_data = NULL;
			if(cx == 0 || cy == 0)
				return *this;
			m_data = new _Tp[cx * cy];
			if(data) {
				if(transpose) {
					m_cx = cy;
					m_cy = cx;
					impl::trans(data(), cx, cy, data);
				} else {
					m_cx = cx;
					m_cy = cy;
					impl::cpy(data(), cx, cy, data);
				}
			}
			return *this;
		}
		mat& id(const size_t& cx)
		{
			if(cx == 0)
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
			for(size_t i = 0; i < cx(); i++)
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
	return t.id() -= m;
}

//x*m
template<typename _Tp>
mat::mat<_Tp> operator*(const _Tp& x, const mat::mat<_Tp>& m)
{
	return m * x;
}

/*#if MAT_IMPL_USE_STD
template<typename _Tp>
std::ostream& operator<<(std::ostream& os, const mat::mat<_Tp>& m)
{
	size_t x, y;
	for(y = 0; y < m.cy(); y++) {
		os << "[";
		for(x = 0; m.cx(); x++) {
			if(x)
				os << ", ";
			os << m.at(x, y);
		}
		os << "]" << std::endl;
	}
	if(y == 0)
		os << "[]" << std::endl;
	return os;
}
#endif*/

#endif
