#include "function.h"
#include <math.h>

float* MG(float** A, int ASize, float* F, float* u_f, int m, float TOL, int itmax) {
	int i,j;
	int op = 1;
	float w = 0.5;
	float *output;
	output = (float*)malloc(sizeof(float) * ASize); 
	
	if(m==1)
		return matrix_vector_multiply(inverse(A), F, ASize, ASize);
	else {
		int size_fine = (int)sqrt((double)ASize);
		int size_coarse = (size_fine-1) / 2;
		//printf("\n%d %d\n",size_fine,size_coarse);
		int square_size_coarse = size_coarse*size_coarse, square_size_fine = size_fine * size_fine;
		struct two_matrix* Rst = gen_restric(size_fine, size_coarse, op);
		
		u_f = Jacobi_it(A, ASize, F, u_f, w, TOL, itmax);
		
		float* r_f;
		r_f = (float*)malloc(sizeof(float) * ASize);
		r_f = vector_sub(F, matrix_vector_multiply(A, u_f, ASize, ASize), ASize);
		
		//printf("fail 2\n");
		float *r_c = matrix_vector_multiply(Rst->Restrict, r_f, square_size_coarse, square_size_fine);
		//printf("fail 3\n");
		//要改，暫時寫著測試用 
		float **A_c = two_matrix_multiply(two_matrix_multiply(Rst->Restrict, A, square_size_coarse, square_size_fine,square_size_fine), Rst->Interpolate, square_size_coarse, square_size_fine, square_size_coarse);

		float *u_c;
		u_c = (float*)malloc(sizeof(float) * square_size_coarse);
		for(i=0; i<square_size_coarse; i++)
			u_c[i] = 0;
		//printf("fail 5\n");
		float *e_c = MG(A_c, square_size_coarse, r_c, u_c, m-1, TOL, itmax);
		
		float *e_f = matrix_vector_multiply(Rst->Interpolate, e_c, square_size_fine, square_size_coarse);
		
		u_f = vector_add(u_f, e_f, ASize);
		
		output = Jacobi_it(A, ASize, F, u_f, w, TOL, itmax);
	}
	return output;
}
