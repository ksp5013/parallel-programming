#include "function.h"
#include "math.h"

//matlab�䴩�����O��C���X �]���|���ƩI�s �ҥH�B�~�g��function 
//�o�̪�function���S���B�~�ˬd��J���x�}�ΦV�q�ण��ۭ� ���i��X�� 
//�o�̪��C��function��output�������t�O����Ŷ� 
double* vector_sub(double* v1, double* v2, int size) {  //�V�q��k 
	int i;
	double *output;
	output = (double*)malloc(sizeof(double) * size);
	
	for(i = 0; i < size; i++)
		output[i] = v1[i] - v2[i];
	
	return output;
}

double* matrix_vector_multiply(double** A, double* v, int Arow, int Acol) {  //�x�}*�V�q 
	double* output;
	output = (double*)malloc(sizeof(double) * Arow);
	
	int i,j;
	for(i = 0; i < Arow; i++)
		output[i] = 0;
	for(i = 0; i < Arow; i++) {
		for(j = 0; j < Acol; j++)
			output[i] += A[i][j] * v[j];
	}
	
	return output;
}

double norm(double* v, int size) {  //�p��V�qv������ �Y||v|| 
	int i;
	double output = 0;
	for(i = 0; i < size; i++)
		output += v[i]*v[i];
	
	return sqrt(output);
}

//matlab�����O
//���k�����ŧi�@�ӭ�n�j�p���x�} �N���������׻PA�ۦP���϶��x�} �C�Ӱ϶���JB*A[i][j]���x�} 
double** kron(double** A, int Arow, int Acol, double** B, int Brow, int Bcol) {
	int i,j,i_Block,j_Block;
	int new_row = Arow * Brow;
	int new_col = Acol * Bcol;
	double **output;
	output = (double**)malloc(sizeof(double*) * new_row);
	for(i = 0; i < new_row; i++)
		output[i] = (double*)malloc(sizeof(double) * new_col);
	
	for(i_Block = 0; i_Block < new_row; i_Block += Brow) {
		for(j_Block = 0; j_Block < new_col; j_Block += Bcol) {  //blocking 
			int index_x, index_y;
			index_x = i_Block / Brow;
			index_y = j_Block / Bcol;  //��XA[i][j]��i,j �]��for�j��O��ooutput�b�] �ҥHA��index�n�t�~�� 
			for(i = i_Block; i < i_Block+Brow; i++) {
				for(j = j_Block; j < j_Block+Bcol; j++) {
					int x = i % Brow;
					int y = j % Bcol;  //��XB[i][j]��i,j �]��for�j��O��ooutput�b�] �ҥHB��index�]�n�t�~��
					output[i][j] = A[index_x][index_y] * B[x][y];
				}
			}
		}
	}
	return output;
}

double** two_matrix_multiply(double** A, double** B, int rowA, int colA, int colB) {  //�x�}���k 
	int i,j,k;
	double **output;
	output = (double**)malloc(sizeof(double*) * rowA);
	for(i = 0; i < rowA; i++)
		output[i] = (double*)malloc(sizeof(double) * colB);
	
	for(i = 0; i < rowA; i++) {
		for(j = 0; j < colB; j++) {
			output[i][j] = 0;
			for(k = 0; k < colA; k++) 
				output[i][j] += A[i][k] * B[k][j];
		}
	}
	
	return output;
} 

double** inverse(double** A, int ASize) {  //�D�x�}���ϯx�} �γ̰򥻪��������h�k [A|I] -> [I|A'] 
	int i,j,k;
	double** output;
	output = (double**)malloc(sizeof(double*) * ASize);
	for(i = 0; i < ASize; i++) 
		output[i] = (double*)malloc(sizeof(double) * ASize);
		
	for(i = 0; i < ASize; i++) 
		for(j = 0; j < ASize; j++)
			output[i][j] = 0;
	
	for(i = 0; i < ASize; i++)
		output[i][i] = 1;  //output = I
	
	for(i = 0; i < ASize-1; i++) {  //�NA���U�T���M��0 
		for(j = i+1; j < ASize; j++) {
			if(A[i][i] != 0) {
				double div = A[j][i] / A[i][i] * -1;
				for(k = 0; k < ASize; k++) {
					A[j][k] += A[i][k] * div;
					output[j][k] += output[i][k] * div;
				}
			}
		}
	}
	
	for(i = 0; i < ASize; i++) {  //A���﨤�u����1 
		double temp = A[i][i];
		for(j = 0; j < ASize; j++) {
			A[i][j] /= temp;
			output[i][j] /= temp;
		}
	}
	
	for(i = ASize-1; i > 0; i--) {  //�NA���W�T���M��0 
		for(j = i-1; j >= 0; j--) {
			if(A[i][i] != 0) {
				double div = A[j][i] / A[i][i] * -1;
				for(k = 0; k < ASize; k++) {
					A[j][k] += A[i][k] * div;
					output[j][k] += output[i][k] * div;
				}
			}
		}
	}
	
	return output;
}

double* vector_add(double* v1, double* v2,int size) {  //�V�q�[�k 
	int i;
	double *output;
	output = (double*)malloc(sizeof(double) * size);
	
	for(i = 0; i < size; i++)
		output[i] = v1[i] + v2[i];
	
	return output;
}
