#include "mat.hpp"

/*TODO: TESTING*/

#define N (10)

int main(int argc, char** argv)
{
	using namespace mat::impl;
	float a[N*N];
	float b[N*N];
	float r[N*N];
	srand(0);
	for(int i = 0; i < N*N; i++)
		a[i] = (rand() % 10) / 5.f;
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
	return 0;
}
