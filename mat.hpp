#ifndef MAT_UTIL_H
#define MAT_UTIL_H

#include "compat.hpp"
#include "solver.hpp"

//N = cx, M = cy

namespace mat
{
	namespace impl
	{
		template<typename _Tp>
		_Tp* mul(_Tp* dest, const _Tp* A, size_t AN, size_t AM, const _Tp* B, size_t BN, size_t BM);
		template<typename _Tp>
		_Tp* tmul(_Tp* dest, const _Tp* A, size_t AN, size_t AM, const _Tp* B, size_t BN, size_t BM);
		template<typename _Tp>
		_Tp* mult(_Tp* dest, const _Tp* A, size_t AN, size_t AM, const _Tp* B, size_t BN, size_t BM);
		template<typename _Tp>
		_Tp* mulT(_Tp* dest, const _Tp* A, size_t AN, size_t AM, const _Tp* B, size_t BN, size_t BM);
		template<typename _Tp>
		_Tp* tmulT(_Tp* dest, const _Tp* A, size_t AN, size_t AM, const _Tp* B, size_t BN, size_t BM);
		template<typename _Tp>
		_Tp* multT(_Tp* dest, const _Tp* A, size_t AN, size_t AM, const _Tp* B, size_t BN, size_t BM);
		
		template<typename _Tp>
		_Tp* smul(_Tp* dest, size_t N, size_t M, const _Tp* src, _Tp C);
		template<typename _Tp>
		_Tp* add(_Tp* dest, size_t N, size_t M, const _Tp* A, const _Tp* B);
		template<typename _Tp>
		_Tp* trans(_Tp* dest, size_t N, size_t M, const _Tp* src);
		template<typename _Tp>
		_Tp* id(_Tp* dest, size_t N);
		template<typename _Tp>
		_Tp* cpy(_Tp* dest, size_t N, size_t M, const _Tp* src);
		template<typename _Tp>
		_Tp* inv(_Tp* dest, size_t N, const _Tp* src);
		template<typename _Tp>
		_Tp det(const _Tp* src, size_t N);
		template<typename _Tp>
		void printt(const _Tp& f);
		template<typename _Tp>
		void print(const _Tp* src, size_t N, size_t M);

		template<typename _Tp>
		_Tp* mul(_Tp* dest, const _Tp* A, size_t ci, size_t cy, const _Tp* B, size_t cx, size_t BM)
		{
			size_t x, y, i;
			if(ci != BM)
				return NULL;
			if(!A || !B)
				return NULL;
			for(i = 0; i < cx*cy; i++)
				dest[i] = 0;
			for(y = 0; y < cy; y++)
				for(x = 0; x < cx; x++)
					for(i = 0; i < ci; i++)
						dest[y * cx + x] += A[y * ci + i] * B[i * ci + x];
			return dest;
		}
		
		template<typename _Tp>
		_Tp* tmul(_Tp* dest, const _Tp* A, size_t cy, size_t ci, const _Tp* B, size_t cx, size_t BM)
		{
			size_t x, y, i;
			if(ci != BM)
				return NULL;
			if(!A || !B)
				return NULL;
			for(i = 0; i < cx*cy; i++)
				dest[i] = 0;
			for(y = 0; y < cy; y++)
				for(x = 0; x < cx; x++)
					for(i = 0; i < ci; i++)
						dest[y * cx + x] += A[i * ci + y] * B[i * ci + x];
			return dest;
		}
		
		template<typename _Tp>
		_Tp* mult(_Tp* dest, const _Tp* A, size_t ci, size_t cy, const _Tp* B, size_t BN, size_t cx)
		{
			size_t x, y, i;
			if(ci != BN)
				return NULL;
			if(!A || !B)
				return NULL;
			for(i = 0; i < cx*cy; i++)
				dest[i] = 0;
			for(y = 0; y < cy; y++)
				for(x = 0; x < cx; x++)
					for(i = 0; i < ci; i++)
						dest[y * cx + x] += A[y * ci + i] * B[x * ci + i];
			return dest;
		}

		template<typename _Tp>
		_Tp* mulT(_Tp* dest, const _Tp* A, size_t ci, size_t cy, const _Tp* B, size_t cx, size_t BM)
		{
			size_t x, y, i;
			if(ci != BM)
				return NULL;
			if(!A || !B)
				return NULL;
			for(i = 0; i < cx*cy; i++)
				dest[i] = 0;
			for(x = 0; x < cx; x++)
				for(y = 0; y < cy; y++)
					for(i = 0; i < ci; i++)
						dest[x * cx + y] += A[y * ci + i] * B[i * ci + x];
			return dest;
		}
		
		template<typename _Tp>
		_Tp* tmulT(_Tp* dest, const _Tp* A, size_t cy, size_t ci, const _Tp* B, size_t cx, size_t BM)
		{
			size_t x, y, i;
			if(ci != BM)
				return NULL;
			if(!A || !B)
				return NULL;
			for(i = 0; i < cx*cy; i++)
				dest[i] = 0;
			for(x = 0; x < cx; x++)
				for(y = 0; y < cy; y++)
					for(i = 0; i < ci; i++)
						dest[x * cx + y] += A[i * ci + y] * B[i * ci + x];
			return dest;
		}
		
		template<typename _Tp>
		_Tp* multT(_Tp* dest, const _Tp* A, size_t ci, size_t cy, const _Tp* B, size_t BN, size_t cx)
		{
			size_t x, y, i;
			if(ci != BN)
				return NULL;
			if(!A || !B)
				return NULL;
			for(i = 0; i < cx*cy; i++)
				dest[i] = 0;
			for(x = 0; x < cx; x++)
				for(y = 0; y < cy; y++)
					for(i = 0; i < ci; i++)
						dest[x * cx + y] += A[y * ci + i] * B[x * ci + i];
			return dest;
		}

		template<typename _Tp>
		_Tp* smul(_Tp* dest, size_t N, size_t M, const _Tp* src, _Tp C)
		{
			size_t x, y;
			if(!src)
				return NULL;
			for(y = 0; y < M; y++)
				for(x = 0; x < N; x++)
					dest[y * N + x] = src[y * N + x] * C;
			return dest;
		}

		template<typename _Tp>
		_Tp* add(_Tp* dest, size_t N, size_t M, const _Tp* A, const _Tp* B)
		{
			size_t i;
			if(!A || !B)
				return NULL;
			for(i = 0; i < M*N; i++)
				dest[i] = A[i] + B[i];
			return dest;
		}

		//NxM
		template<typename _Tp>
		_Tp* trans(_Tp* dest, size_t N, size_t M, const _Tp* src)
		{
			size_t x, y;
			if(!src)
				return NULL;
			for(y = 0; y < M; y++)
				for(x = 0; x < N; x++)
					dest[x * M + y] = src[y * N + x];
			return dest;
		}

		template<typename _Tp>
		_Tp* id(_Tp* dest, size_t N)
		{
			size_t x, y;
			for(y = 0; y < N; y++)
				for(x = 0; x < N; x++)
					if(x == y)
						dest[y * N + x] = 1;
					else
						dest[y * N + x] = 0;
			return dest;
		}

		template<typename _Tp>
		_Tp* cpy(_Tp* dest, size_t N, size_t M, const _Tp* src)
		{
			size_t i;
			if(!src)
				return NULL;
			for(i = 0; i < N*M; i++)
				dest[i] = src[i];
			return dest;
		}

		template<typename _Tp>
		_Tp* inv(_Tp* dest, size_t N, const _Tp* src)
		{
			_Tp* tmp = (_Tp*)MAT_ALLOCA(sizeof(_Tp) * N * N);
			if(!src)
				return NULL;
			id(dest, N);
			cpy(tmp, N, N, src);
			if(!LUImpl(tmp, N * sizeof(_Tp), N, dest, N * sizeof(_Tp), N))
				return NULL;
			return dest;
		}

		template<typename _Tp>
		_Tp det(const _Tp* src, size_t N)
		{
			size_t i;
			_Tp det;
			_Tp* tmp = (_Tp*)MAT_ALLOCA(sizeof(_Tp) * N * N);
			cpy(tmp, N, N, src);
			det = mat::impl::LUImpl(tmp, N * sizeof(_Tp), N, (_Tp*)NULL, 0, 0);
			for(i = 0; i < N; i++)
				det *= tmp[i * N + i];
			if(det)
				det = 1. / det;
			return det;
		}

		template<typename _Tp>
		void print(const _Tp* src, size_t N, size_t M)
		{
			size_t x, y;
			for(y = 0; y < M; y++) {
				mat::impl::print("[");
				for(x = 0; x < N; x++) {
					if(x)
						mat::impl::print(", ");
					mat::impl::printt(src[y * N + x]);
				}
				mat::impl::print("]\n");
			}
		}
	}
}

#endif
