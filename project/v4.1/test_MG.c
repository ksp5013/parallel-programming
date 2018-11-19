#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include "function.h"

#define Pstart 0
#define Pend 1

int main() {
	int i, j;
	int input_size = 4;  //������ 
	int array_length = (input_size - 1) * (input_size - 1);  //�̾ڵ��� �T�w�x�}�j�p 

	double **A;  //�ŧiA, F 
	double *F;

	A = (double**)malloc(sizeof(double*) * array_length);  //���tA, F���O����Ŷ� 
	for (i = 0; i < array_length; i++)
		A[i] = (double*)malloc(sizeof(double) * array_length);
	F = (double*)malloc(sizeof(double) * array_length);
	
	//�Ȯɵ��w 
	for (i = 0; i < array_length; i++) {
		for (j = 0; j < array_length; j++) {  //��l��A 
			if (i == j)
				A[i][j] = 1;
			else if(j - i == 1)
				A[i][j] = -1;
			else
				A[i][j] = 0;
			
		}
	}

	for (i = 0; i < array_length; i++)  //��l��F 
		F[i] = 0.5;

	printf("A = \n");
	for (i = 0; i < array_length; i++) {
		for (j = 0; j < array_length; j++) {  //��XA 
			printf("%.10lf ", A[i][j]);
		}
		printf("\n\n");
	}
	printf("\n");
	
	printf("F = \n");
	for (i = 0; i < array_length; i++)  //��XF 
		printf("%.10lf ",F[i]);
	printf("\n\n"); 

	double *u_f;
	u_f = (double*)malloc(sizeof(double) * array_length);
	srand(time(NULL));
	for (i = 0; i < array_length; i++)
		u_f[i] = (double)rand() / (RAND_MAX + 1.0);  //�ŧi, ���t�Ŷ�, ��l��u_f, u_f��Ax=F���� 

	int m = 3;  //V-cycle�`�� 
	double TOL = pow(10, -8);  //�̤p�~�t 
	printf("TOL = %e\n\n",TOL);
	double *u;
	u = (double*)malloc(sizeof(double) * array_length);  //u�ƻsu_f, u,u_f�i�R�@��?? 
	for (i = 0; i < array_length; i++)
		u[i] = u_f[i];
	double res = 1;  //u_f�PF���~�t 
	int k = 1;  //�j�鱱�����,�קK�L�a�j�� 
	while (res > TOL && k < 500) {  //��~�t�p��̤p�~�t�ΰj������ ���X�j�� 
		printf("\nMG loop %d\n\n", k);
		u = MG(A, array_length, F, u, m, TOL, 3);  //��u_f��multigrid 
		
		printf("u\n");
		for(i = 0; i < array_length; i++)  //��Xmultigrid�᪺���G 
			printf("%.10f ", u[i]);
		printf("\n");
		printf("u\n\n");
		
		k++;
		double *temp1, *temp2;  //�p��u_f�PF���~�t  
		temp1 = matrix_vector_multiply(A, u, array_length, array_length);  //temp1 = A*u_f 
		temp2 = vector_sub(temp1, F, array_length);  //temp2 = F-A*u_f
		res = norm(temp2, array_length);
		res /= norm(F, array_length);    //res = ||F-A*u_f|| / ||F|| 
		printf("residual = %e\n\n", res);
		
		free(temp1);  //�^���O����Ŷ� 
		free(temp2);
	}

	if (k < 500)
		printf("success in loop %d\n", k);  //��X���\�Υ��� 
	else
		printf("fail within %d loop", k);
	
	system("pause");
	return 0;
}
