#include "function.h"

struct two_matrix* gen_restric(int size_fine, int size_coarse, int op) {
	struct two_matrix* output;
	output = (struct two_matrix*)malloc(sizeof(struct two_matrix));
	 
	float **R_f_c_1d, **R_f_c_2d;
	int i,j;
	R_f_c_1d = (float**)malloc(sizeof(float*)*size_coarse);
	for(i=0; i<size_coarse; i++)
		R_f_c_1d[i] = (float*)malloc(sizeof(float)*size_fine);
	
	int square_size_coarse = size_coarse*size_coarse, square_size_fine = size_fine * size_fine;
	R_f_c_2d = (float**)malloc(sizeof(float*)*square_size_coarse);
	for(i=0; i<square_size_coarse; i++)
		R_f_c_2d[i] = (float*)malloc(sizeof(float)*square_size_fine);
	
	//寫定，可能要改
	for(i=0; i<size_coarse; i++) {
		for(j=0; j<size_fine; j++)
			R_f_c_1d[i][j] = 0;
	}
	for(i=0; 2*i+1<size_coarse; i++)
		R_f_c_1d[i][2*i+1] = 1;
	R_f_c_2d = kron(R_f_c_1d, size_coarse, size_fine, R_f_c_1d, size_coarse, size_fine);
	
	//寫定，可能要改
	float **Ef, **E_f;
	Ef = (float**)malloc(sizeof(float*)*size_fine);
	for(i=0; i<size_fine; i++)
		Ef[i] = (float*)malloc(sizeof(float)*size_fine);
	for(i=0; i<size_fine; i++) {
		for(j=0; j<size_fine; j++) {
			if(i==j)
				Ef[i][j] = 2;
			else if(i-j==1 || j-i==1)
				Ef[i][j] = 1;
			else
				Ef[i][j] = 0;
		}
	}
	
	for(i=0; i<size_fine; i++) {
		for(j=0; j<size_fine; j++)
			Ef[i][j] = Ef[i][j] * 0.25;
	}
	
	E_f = kron(Ef, size_fine, size_fine, Ef, size_fine, size_fine);
	
	output->Restrict = two_matrix_multiply(R_f_c_2d, E_f, square_size_coarse, square_size_fine, square_size_fine);
	
	output->Interpolate = (float**)malloc(sizeof(float*)*square_size_fine);
	for(i=0; i<square_size_fine; i++)
		output->Interpolate[i] = (float*)malloc(sizeof(float)*square_size_coarse);
	
	for(i=0; i<square_size_fine; i++) {
		for(j=0; j<square_size_coarse; j++)
			output->Interpolate[i][j] = 4 * output->Restrict[j][i];
	}
	
	return output;
}
