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
			double temp = 0;
			for(j=0; j<ASize; j++) {
				if(i != j)
					temp += A[i][j] * u_f[j];
			}
			New_u_f[i] = w * (b[i] - temp) / A[i][i] + (1.0-w) * u_f[i];
		}
		
		printf("Jacobit loop %d\n",nit);
		printf("New_u_f\n");
		for(i=0;i<ASize;i++)
			printf("%.10lf ",New_u_f[i]);
		printf("\n\n");
		
		double *temp1 = matrix_vector_multiply(A, New_u_f, ASize, ASize);
		
		printf("A*New_u_f\n");
		for(i=0;i<ASize;i++)
			printf("%.10lf ",temp1[i]);
		printf("\n\n");
		
		double *temp2 = vector_sub(b, temp1, ASize);
		
		if( (norm(temp2, ASize) / norm(b, ASize) ) < TOL) {
			printf("success at %d -th step!\n",nit);
			return New_u_f;
		}
		else {
			nit ++;
			for(i=0;i<ASize;i++)
				u_f[i] = New_u_f[i];
		}
	}
	
	printf("fail...\n\n");
	return New_u_f;
}

