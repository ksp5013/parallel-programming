#include "function.h"
#include "math.h"

double* vector_sub(double* v1, double* v2, int size) {
	int i;
	double *output;
	output = (double*)malloc(sizeof(double) * size);
	
	for(i=0;i<size;i++)
		output[i] = v1[i] - v2[i];
	
	return output;
}

double* matrix_vector_multiply(double** A, double* v, int Arow, int Acol) {
	double* output;
	output = (double*)malloc(sizeof(double)*Acol);
	
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

double norm(double* v, int ASize) {
	int i;
	double output = 0;
	for(i=0; i<ASize; i++)
		output += v[i]*v[i];
	
	printf("norm = %lf %lf\n",output, sqrt(output));
	
	return sqrt(output);
}

double** kron(double** A, int Arow, int Acol, double** B, int Brow, int Bcol) {
	int i,j,i_Block,j_Block;
	int new_row = Arow * Brow;
	int new_col = Acol * Bcol;
	double **output;
	output = (double**)malloc(sizeof(double*)*new_row);
	for(i=0; i<new_row; i++)
		output[i] = (double*)malloc(sizeof(double)*new_col);
	
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

double** two_matrix_multiply(double** A, double** B, int rowA, int colA, int colB) {
	//printf("fail 4\n");
	int i,j,k;
	double **output;
	output = (double**)malloc(sizeof(double*) * rowA);
	for(i=0; i<rowA; i++)
		output[i] = (double*)malloc(sizeof(double) * colB);
	
	for(i=0; i<rowA; i++) {
		for(j=0; j<colB; j++) {
			output[i][j] = 0;
			for(k=0; k<colA; k++) 
				output[i][j] += A[i][k] * B[k][j];
		}
	}
	
	return output;
} 

double** inverse(double** A, int ASize) {
	int i,j,k;
	double** output;
	output = (double**)malloc(sizeof(double*) * ASize);
	for(i=0;i<ASize;i++) 
		output[i] = (double*)malloc(sizeof(double) * ASize);
		
	for(i=0;i<ASize;i++) 
		for(j=0;j<ASize;j++)
			output[i][j] = 0;
	
	for(i=0;i<ASize;i++)
		output[i][i] = 1;
	
	for(i=0;i<ASize-1;i++) {
		for(j=i+1;j<ASize;j++) {
			if(A[i][i]!=0) {
				double div = A[j][i] / A[i][i] * -1;
				for(k=0;k<ASize;k++) {
					A[j][k] += A[i][k] * div;
					output[j][k] += output[i][k] * div;
				}
			}
		}
	}
	
	for(i=0;i<ASize;i++) {
		double temp = A[i][i];
		for(j=0;j<ASize;j++) {
			A[i][j] /= temp;
			output[i][j] /= temp;
		}
	}
	
	for(i=ASize-1;i>0;i--) {
		for(j=i-1;j>=0;j--) {
			if(A[i][i]!=0) {
				double div = A[j][i] / A[i][i] * -1;
				for(k=0;k<ASize;k++) {
					A[j][k] += A[i][k] * div;
					output[j][k] += output[i][k] * div;
				}
			}
		}
	}
	
	return A;
}

double* vector_add(double* v1, double* v2,int size) {
	int i;
	double *output;
	output = (double*)malloc(sizeof(double) * size);
	
	for(i=0;i<size;i++)
		output[i] = v1[i] + v2[i];
	
	return output;
}
