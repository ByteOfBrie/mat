#include "mat.hpp"

/*TODO: TESTING*/

#define N (10)

int main(int argc, char** argv)
{
/*	using namespace mat::impl;
	float a[N*N] = {
		0.60, 1.20, 1.40, 1.00, 0.60, 1.00, 1.20, 0.40, 1.80, 0.20,
		0.40, 1.40, 0.00, 1.80, 0.60, 1.20, 0.00, 1.20, 0.40, 1.20,
		0.20, 1.60, 1.40, 1.80, 0.40, 0.00, 0.40, 0.60, 1.40, 1.00,
		1.80, 0.40, 0.40, 1.60, 1.80, 1.40, 0.60, 1.20, 0.20, 0.40,
		1.80, 0.60, 0.20, 1.80, 0.80, 1.40, 1.60, 0.80, 1.00, 0.00,
		0.60, 1.20, 0.20, 0.00, 1.20, 0.60, 0.40, 0.00, 1.20, 0.20,
		1.00, 1.00, 0.80, 1.40, 1.20, 1.00, 1.20, 1.80, 0.60, 1.40,
		0.80, 1.00, 0.40, 1.00, 0.80, 1.40, 0.80, 0.80, 0.60, 0.00,
		1.40, 1.60, 1.20, 1.60, 1.60, 0.80, 0.60, 0.20, 0.80, 1.80,
		0.40, 0.00, 1.20, 1.60, 1.80, 0.40, 1.20, 1.20, 0.80, 1.80,
		};
	float b[N*N];
	float r[N*N];
	//srand(0);
	//for(int i = 0; i < N*N; i++)
	//	a[i] = (rand() % 10) / 5.f;
	inv(b, N, a);
	float v[N] = {1,2,3,4,5,6,7,8,9,10};
	float q[N];
	float o[N];
	mul(r, a, N, N, b, N, N);
	printf("a:\n");
	print(a, N, N);
	printf("b:\n");
	print(b, N, N);	
	printf("r:\n");
	print(r, N, N);
	mult(q, a, N, N, v, N, 1);
	mult(o, b, N, N, q, N, 1);
	printf("v:\n");
	print(v, N, 1);
	printf("q:\n");
	print(q, N, 1);
	printf("r:\n");
	print(o, N, 1);
	mat::mat<> t(a, N, N);
	mat::print(t);
	mat::print(t / t);
	mat::print(t.cholskey());*/
/*	float a[] = {25, 15, -5,
		     15, 18, 0,
		     -5, 0, 11,
		    };
	mat::mat<> t(a, 3, 3);
	mat::print(t.cholesky() * (t.cholesky()^1));
	float z = sqrt(-1);
	printf("%i\n", z==z);*/
	return 0;
}
