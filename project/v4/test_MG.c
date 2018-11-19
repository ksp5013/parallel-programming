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

	double **A;
	double *F;

	A = (double**)malloc(sizeof(double*)*array_length);
	for (i = 0; i < array_length; i++)
		A[i] = (double*)malloc(sizeof(double)*array_length);
	F = (double*)malloc(sizeof(double)*array_length);

	for (i = 0; i < array_length; i++) {
		for (j = 0; j < array_length; j++) {
			if (i == j)
				A[i][j] = 0.6186;
			else if(j-i==1)
				A[i][j] = -0.1515;
			else
				A[i][j] = 0;
			
		}
	}

	for (i = 0; i < array_length; i++)
		F[i] = 0.5;

//printf("%f\n\n",norm(F,array_length));
	printf("A = \n");
	for (i = 0; i < array_length; i++) {
		for (j = 0; j < array_length; j++) {
			printf("%.10lf ", A[i][j]);
		}
		printf("\n\n");
		//system("pause");
	}
	printf("\n");
	//system("pause");
	
	printf("F = \n");
	for (i = 0; i < array_length; i++)
		printf("%.10lf ",F[i]);
	printf("\n\n");

	double *u_f;
	u_f = (double*)malloc(sizeof(double) * array_length);
	srand(time(NULL));
	for (i = 0; i < array_length; i++)
		u_f[i] = (double)rand() / (RAND_MAX + 1.0);
	//unsigned int seed = time(NULL);
	//for (i = 0; i < array_size; i++)
	//	x = rand_r(&seed) / ((double)RAND_MAX + 1) * 2.0 - 1.0;

	int m = 3;
	double TOL = pow(10, -8);
	printf("TOL = %e\n\n",TOL);
	double *u;
	u = (double*)malloc(sizeof(double) * array_length);
	for (i = 0; i < array_length; i++)
		u[i] = u_f[i];
	double res = 1;
	int k = 1;
	while (res > TOL && k < 500) {
		//printf("fail 1\n");
		printf("\nMG loop %d\n\n",k);
		u = MG(A, array_length, F, u, m, TOL, 3);
		
		printf("u\n");
		for(i=0;i<array_length;i++)
			printf("%.10f ",u[i]);
		printf("\n");
		printf("u\n\n");
		
		k++;
		double *temp;
		temp = matrix_vector_multiply(A, u, array_length, array_length);
		temp = vector_sub(temp, F, array_length);
		res = norm(temp, array_length);
		res /= norm(F, array_length);
		printf("residual = %e\n\n",res);
		//system("pause");
	}

	if (k < 500)
		printf("success in loop %d\n", k);
	system("pause");

	return 0;
}
