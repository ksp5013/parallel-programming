#include "function.h"
#include <math.h>

double* MG(double** A, int ASize, double* F, double* u_f, int m, double TOL, int itmax) {
	int i,j;
	int op = 1;
	double w = 0.5;
	double *output;
	output = (double*)malloc(sizeof(double) * ASize); 
	
	if(m==1 || ASize==1)
		return matrix_vector_multiply(inverse(A, ASize), F, ASize, ASize);
	else {
		int size_fine = (int)sqrt((double)ASize);
		int size_coarse = (size_fine-1) / 2;
		//printf("\n%d %d\n",size_fine,size_coarse);
		int square_size_coarse = size_coarse*size_coarse, square_size_fine = size_fine * size_fine;
		struct two_matrix* Rst = gen_restric(size_fine, size_coarse, op);
		
		u_f = Jacobi_it(A, ASize, F, u_f, w, TOL, itmax);
		
		/*printf("u_f\n");
		for(i=0;i<ASize;i++)
			printf("%f ",u_f[i]);
		printf("\n");
		printf("u_f\n\n");*/
		
		double* r_f;
		r_f = (double*)malloc(sizeof(double) * ASize);
		r_f = vector_sub(F, matrix_vector_multiply(A, u_f, ASize, ASize), ASize);
		
		/*printf("r_f\n");
		for(i=0;i<ASize;i++)
			printf("%f ",r_f[i]);
		printf("\n");
		printf("r_f\n\n");*/
		
		//printf("fail 2\n");
		double *r_c = matrix_vector_multiply(Rst->Restrict, r_f, square_size_coarse, square_size_fine);
		
		/*printf("r_c\n");
		for(i=0;i<ASize;i++)
			printf("%f ",r_c[i]);
		printf("\n");
		printf("r_c\n\n");*/
		
		//printf("fail 3\n");
		//要改，暫時寫著測試用 
		double **A_c = two_matrix_multiply(two_matrix_multiply(Rst->Restrict, A, square_size_coarse, square_size_fine,square_size_fine), Rst->Interpolate, square_size_coarse, square_size_fine, square_size_coarse);

		double *u_c;
		u_c = (double*)malloc(sizeof(double) * square_size_coarse);
		for(i=0; i<square_size_coarse; i++)
			u_c[i] = 0;
		//printf("fail 5\n");
		double *e_c = MG(A_c, square_size_coarse, r_c, u_c, m-1, TOL, itmax);
		
		printf("e_c\n");
		for(i=0;i<square_size_coarse;i++)
			printf("%f ",e_c[i]);
		printf("\n");
		printf("e_c\n\n");
		
		double *e_f = matrix_vector_multiply(Rst->Interpolate, e_c, square_size_fine, square_size_coarse);
		
		u_f = vector_add(u_f, e_f, ASize);
		
		output = Jacobi_it(A, ASize, F, u_f, w, TOL, itmax);
	}
	return output;
}
