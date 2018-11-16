#include "function.h"

double* Jacobi_it(double** A, int ASize, double* b, double* u_f, double w, double TOL, int itmax) {
	int i,j;
	int nit=1;
	double *New_u_f;
	New_u_f = (double*)malloc(sizeof(double)*ASize);
	for(i=0;i<ASize;i++)
		New_u_f[i] = 0;
	
	while(nit <= itmax) {
		for(i=0; i<ASize; i++) {
			int temp = 0;
			for(j=0; j<ASize; j++) {
				if(i != j)
					temp += A[i][j] * u_f[j];
			}
			New_u_f[i] = w * (b[i] - temp) / A[i][i] + (1-w) * u_f[i];
		}
		
		printf("Jacobi_it\n");
		for(i=0;i<ASize;i++)
			printf("%f ",New_u_f[i]);
		printf("\n");
		printf("Jacobi_it\n\n");
		
		if( (norm(vector_sub(b, matrix_vector_multiply(A, New_u_f, ASize, ASize), ASize),ASize) / norm(b, ASize) ) < TOL) {
			printf("success at %d -th step!\n",nit);
			return New_u_f;
		}
		else {
			nit ++;
			for(i=0;i<ASize;i++)
				u_f[i] = New_u_f[i];
		}
	}
	printf("\n\n");
	
	printf("fail...\n");
	return New_u_f;
}

