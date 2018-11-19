#include "function.h"

//不懂這兩個矩陣的產生方法 直接從matlab code轉成c code 因此不知道如何寫註解 
struct two_matrix* gen_restric(int size_fine, int size_coarse, int op) {
	struct two_matrix* output;  //宣告回傳值 
	output = (struct two_matrix*)malloc(sizeof(struct two_matrix));  //分配output空間 
	 
	double **R_f_c_1d, **R_f_c_2d;
	int i,j;
	R_f_c_1d = (double**)malloc(sizeof(double*) * size_coarse);
	for(i = 0; i < size_coarse; i++)
		R_f_c_1d[i] = (double*)malloc(sizeof(double) * size_fine);
	
	int square_size_coarse = size_coarse * size_coarse;
	int square_size_fine = size_fine * size_fine;
	R_f_c_2d = (double**)malloc(sizeof(double*) * square_size_coarse);
	for(i = 0; i < square_size_coarse; i++)
		R_f_c_2d[i] = (double*)malloc(sizeof(double) * square_size_fine);
	
	//寫定，可能要改 從matlab執行結果觀察得到 
	for(i = 0; i < size_coarse; i++) {
		for(j = 0; j < size_fine; j++)
			R_f_c_1d[i][j] = 0;
	}
	for(i = 0; 2*i+1 < size_fine; i++)
		R_f_c_1d[i][2*i+1] = 1;
	
	R_f_c_2d = kron(R_f_c_1d, size_coarse, size_fine, R_f_c_1d, size_coarse, size_fine);
	
	//寫定，可能要改
	double **Ef, **E_f;
	Ef = (double**)malloc(sizeof(double*) * size_fine);
	for(i = 0; i < size_fine; i++)
		Ef[i] = (double*)malloc(sizeof(double) * size_fine);
	for(i = 0; i < size_fine; i++) {
		for(j = 0; j < size_fine; j++) {
			if(i == j)
				Ef[i][j] = 2;
			else if(i-j ==1 || j-i ==1)
				Ef[i][j] = 1;
			else
				Ef[i][j] = 0;
		}
	}
	
	for(i = 0; i < size_fine; i++) {
		for(j = 0; j < size_fine; j++)
			Ef[i][j] = Ef[i][j] * 0.25;
	}
	
	E_f = kron(Ef, size_fine, size_fine, Ef, size_fine, size_fine);
	
	output->Restrict = two_matrix_multiply(R_f_c_2d, E_f, square_size_coarse, square_size_fine, square_size_fine);
	
	output->Interpolate = (double**)malloc(sizeof(double*) * square_size_fine);
	for(i = 0; i < square_size_fine; i++)
		output->Interpolate[i] = (double*)malloc(sizeof(double) * square_size_coarse);
	
	for(i = 0; i < square_size_fine; i++) {
		for(j = 0; j < square_size_coarse; j++)
			output->Interpolate[i][j] = 4 * output->Restrict[j][i];
	}
	
	
	for(i = 0; i < size_coarse; i++)
		free(R_f_c_1d[i]);
	free(R_f_c_1d);
	
	for(i = 0; i < square_size_coarse; i++)
		free(R_f_c_2d[i]);
	free(R_f_c_2d);
	
	for(i = 0; i < size_fine; i++)
		free(Ef[i]);
	free(Ef);
	
	for(i = 0; i < square_size_fine; i++)
		free(E_f[i]);
	free(E_f);
	
	return output;
}
