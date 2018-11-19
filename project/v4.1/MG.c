#include "function.h"
#include <math.h>

double* MG(double** A, int ASize, double* F, double* u_f, int m, double TOL, int itmax) {
	int i,j;
	int op = 1;
	double w = 0.5;  //op w �Ȯɵ��w 
	double *output;  //�̫᪺��X 
	
	if(m==1 || ASize==1)  //�p�GV-cycle�w�쩳�ίx�}����A�� �ΰ������h�k�� 
		return matrix_vector_multiply(inverse(A, ASize), F, ASize, ASize);
	else {
		int size_fine = (int)sqrt((double)ASize);  //�Ӻ���j�p 
		int size_coarse = (size_fine-1) / 2;       //�ʺ���j�p 
		int square_size_coarse = size_coarse * size_coarse;  //�ʲӺ���j�p������� �w���p�� ��֤��᪺�B��q 
		int square_size_fine = size_fine * size_fine;
		
		struct two_matrix* Rst = gen_restric(size_fine, size_coarse, op);  //��XRestrict matrix �� Interpolate matrix 
		
		u_f = Jacobi_it(A, ASize, F, u_f, w, TOL, itmax);  //��u_f��pre-smooth 
		
		double *temp1 = matrix_vector_multiply(A, u_f, ASize, ASize);  //��Xfine-grid residual  r_f = F-A*u_f 
		double *r_f = vector_sub(F, temp1, ASize);  
		
		double *r_c = matrix_vector_multiply(Rst->Restrict, r_f, square_size_coarse, square_size_fine);  //r_c�� fine-grid residual�নcoarse-grid residual
		
		//�p��ʺ��檺�x�} ���n�� 
		double **temp2 = two_matrix_multiply(Rst->Restrict, A, square_size_coarse, square_size_fine, square_size_fine);
		double **A_c = two_matrix_multiply(temp2, Rst->Interpolate, square_size_coarse, square_size_fine, square_size_coarse);

		double *u_c;
		u_c = (double*)malloc(sizeof(double) * square_size_coarse);  //u_c������0���}�C 
		for(i=0; i < square_size_coarse; i++)
			u_c[i] = 0;
		double *e_c = MG(A_c, square_size_coarse, r_c, u_c, m-1, TOL, itmax);  //��A_c r_c u_c ���U�@�h��multigrid ��Xcoarse-grid�ץ���V 
		
		double *e_f = matrix_vector_multiply(Rst->Interpolate, e_c, square_size_fine, square_size_coarse);  //�Ncoarse-grid �ন fine-grid�ץ���V 
		
		u_f = vector_add(u_f, e_f, ASize);  //update u_f 
		
		output = Jacobi_it(A, ASize, F, u_f, w, TOL, itmax);  //��u_f��post-smooth 
		
		free(temp1);  //���^�O����Ŷ� �]��matlab_op�ڳ������t�O���� �ҥH�j�h�ƪ��}�C���n�^�� 
		free(u_f);    //�Ҧ�.c�ɳ��u���ʲ��^�� �i�H��i�@�B����֨ϥΪŶ� 
		free(r_c);
		free(u_c);
		free(e_c);
		free(e_f);
		
		for(i = 0; i < square_size_coarse; i++)
			free(temp2[i]);
		free(temp2);
		
		for(i = 0; i < square_size_coarse; i++)
			free(A_c[i]);
		free(A_c);
		
	}
	return output;
}
