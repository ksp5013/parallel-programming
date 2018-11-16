#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "function.h"

#define Pstart 0
#define Pend 1

int main() {
	int i, j;
	int input_size = 4;  //argument
	int array_length = (input_size - 1) * (input_size - 1);

	float **A;
	float *F;

	A = (float**)malloc(sizeof(float*)*array_length);
	for (i = 0; i < array_length; i++)
		A[i] = (float*)malloc(sizeof(float)*array_length);
	F = (float*)malloc(sizeof(float)*array_length);

	for (i = 0; i < array_length; i++) {
		for (j = 0; j < array_length; j++) {
			if (i == j)
				A[i][j] = -1;
			else if(i-j==1)
				A[i][j] = 1;
			else
				A[i][j] = 0;
			
		}
	}

	for (i = 0; i < array_length; i++)
		F[i] = 0.5;

	/*for (i = 0; i < array_length; i++) {
		for (j = 0; j < array_length; j++) {
			printf("%.f ", A[i][j]);
		}
		printf("\n");
		system("pause");
	}
	system("pause");*/

	float *u_f;
	u_f = (float*)malloc(sizeof(float) * array_length);
	srand(time(NULL));
	for (i = 0; i < array_length; i++)
		u_f[i] = (double)rand() / (RAND_MAX + 1.0);
	//unsigned int seed = time(NULL);
	//for (i = 0; i < array_size; i++)
	//	x = rand_r(&seed) / ((double)RAND_MAX + 1) * 2.0 - 1.0;

	int m = 3;
	float TOL = pow(10, -8);
	float *u;
	u = (float*)malloc(sizeof(float) * array_length);
	for (i = 0; i < array_length; i++)
		u[i] = u_f[i];
	int res = 1;
	int k = 1;
	while (res > TOL && k < 500) {
		//printf("fail 1\n");
		u = MG(A, array_length, F, u, m, TOL, 3);
		i++;
		float *temp;
		temp = matrix_vector_multiply(A, u, array_length, array_length);
		temp = vector_sub(temp, F, array_length);
		res = norm(temp, array_length) / norm(F, array_length);
	}

	if (k < 500)
		printf("success in loop %d\n", k);
	system("pause");

	return 0;
}
