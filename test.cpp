#include "mat.hpp"

/*TODO: TESTING*/

int main(int argc, char** argv)
{
	using namespace mat::impl;
	float mat[4] = {
	  0,1,1,0,
	};
	float vec[2] = {1, 2};
	float res[2];
//	float out[2];
//	float matinv[4];
//	float prod[4];
	//id(mat, 4);
//	inv(matinv, 2, mat);
//	mul(prod, mat, 2, 2, matinv, 2, 2);
	printf("mat:\n");
	print(mat, 2, 2);
//	printf("inv:\n");
//	print(matinv, 2, 2);
//	printf("prod:\n");
//	print(prod, 2, 2);
	printf("vec:\n");
	print(vec, 2, 1);
	multT(res, mat, 2, 2, vec, 2, 1);
	printf("res:\n");
	print(res, 2, 1);
//	mul(out, matinv, 2, 2, res, 2, 1);
//	printf("out:\n");
//	print(out, 2, 1);
	return 0;
}

