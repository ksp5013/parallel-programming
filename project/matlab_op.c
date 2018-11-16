#include "function.h"

float* vector_sub(float* v1, float* v2, int size) {
	int i;
	for(i=0;i<size;i++)
		v1[i] -= v2[i];
	
	return v1;
}

float* matrix_vector_multiply(float** A, float* v, int Arow, int Acol) {
	float* output;
	output = (float*)malloc(sizeof(float)*Acol);
	
	int i,j;
	for(i=0; i<Acol; i++)
		output[i] = 0;
	for(i=0; i<Arow; i++) {
		for(j=0; j<Acol; j++)
			output[i] += A[i][j] * v[j];
	}
	
	//printf("mvm\n");
	
	return output;
}

float norm(float* v, int ASize) {
	int i;
	float output = 0;
	for(i=0; i<ASize; i++)
		output += v[i]*v[i];
	
	return output;
}

float** kron(float** A, int Arow, int Acol, float** B, int Brow, int Bcol) {
	int i,j,i_Block,j_Block;
	int new_row = Arow * Brow;
	int new_col = Acol * Bcol;
	float **output;
	output = (float**)malloc(sizeof(float*)*new_row);
	for(i=0; i<new_row; i++)
		output[i] = (float*)malloc(sizeof(float)*new_col);
	
	for(i_Block=0; i_Block<new_row; i_Block+=Brow) {
		for(j_Block=0; j_Block<new_col; j_Block+=Bcol) {
			int index_x, index_y;
			index_x = i_Block/Brow;
			index_y = j_Block/Bcol;
			for(i=i_Block; i<i_Block+Brow; i++) {
				for(j=j_Block; j<j_Block+Bcol; j++) {
					int x = i%Brow;
					int y = j%Bcol;
					output[i][j] = A[index_x][index_y] * B[x][y];
				}
			}
		}
	}
	return output;
}

float** two_matrix_multiply(float** A, float** B, int rowA, int colA, int colB) {
	//printf("fail 4\n");
	int i,j,k;
	float **output;
	output = (float**)malloc(sizeof(float*) * rowA);
	for(i=0; i<rowA; i++)
		output[i] = (float*)malloc(sizeof(float) * colB);
	
	for(i=0; i<rowA; i++) {
		for(j=0; j<colB; j++) {
			output[i][j] = 0;
			for(k=0; k<colA; k++) 
				output[i][j] += A[i][k] * B[k][j];
		}
	}
	
	return output;
} 

float** inverse(float** A) {
	
	return A;
}

float* vector_add(float* v1, float* v2,int size) {
	int i;
	for(i=0;i<size;i++)
		v1[i] += v2[i];
	
	return v1;
}
