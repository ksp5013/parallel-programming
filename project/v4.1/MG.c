#include "function.h"
#include <math.h>

double* MG(double** A, int ASize, double* F, double* u_f, int m, double TOL, int itmax) {
	int i,j;
	int op = 1;
	double w = 0.5;  //op w 暫時給定 
	double *output;  //最後的輸出 
	
	if(m==1 || ASize==1)  //如果V-cycle已到底或矩陣不能再切 用高斯消去法解 
		return matrix_vector_multiply(inverse(A, ASize), F, ASize, ASize);
	else {
		int size_fine = (int)sqrt((double)ASize);  //細網格大小 
		int size_coarse = (size_fine-1) / 2;       //粗網格大小 
		int square_size_coarse = size_coarse * size_coarse;  //粗細網格大小的平方值 預先計算 減少之後的運算量 
		int square_size_fine = size_fine * size_fine;
		
		struct two_matrix* Rst = gen_restric(size_fine, size_coarse, op);  //算出Restrict matrix 及 Interpolate matrix 
		
		u_f = Jacobi_it(A, ASize, F, u_f, w, TOL, itmax);  //對u_f做pre-smooth 
		
		double *temp1 = matrix_vector_multiply(A, u_f, ASize, ASize);  //算出fine-grid residual  r_f = F-A*u_f 
		double *r_f = vector_sub(F, temp1, ASize);  
		
		double *r_c = matrix_vector_multiply(Rst->Restrict, r_f, square_size_coarse, square_size_fine);  //r_c為 fine-grid residual轉成coarse-grid residual
		
		//計算粗網格的矩陣 日後要改 
		double **temp2 = two_matrix_multiply(Rst->Restrict, A, square_size_coarse, square_size_fine, square_size_fine);
		double **A_c = two_matrix_multiply(temp2, Rst->Interpolate, square_size_coarse, square_size_fine, square_size_coarse);

		double *u_c;
		u_c = (double*)malloc(sizeof(double) * square_size_coarse);  //u_c為全為0的陣列 
		for(i=0; i < square_size_coarse; i++)
			u_c[i] = 0;
		double *e_c = MG(A_c, square_size_coarse, r_c, u_c, m-1, TOL, itmax);  //用A_c r_c u_c 做下一層的multigrid 算出coarse-grid修正方向 
		
		double *e_f = matrix_vector_multiply(Rst->Interpolate, e_c, square_size_fine, square_size_coarse);  //將coarse-grid 轉成 fine-grid修正方向 
		
		u_f = vector_add(u_f, e_f, ASize);  //update u_f 
		
		output = Jacobi_it(A, ASize, F, u_f, w, TOL, itmax);  //對u_f做post-smooth 
		
		free(temp1);  //收回記憶體空間 因為matlab_op我都有分配記憶體 所以大多數的陣列都要回收 
		free(u_f);    //所有.c檔都只有粗略回收 可以更進一步的減少使用空間 
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
