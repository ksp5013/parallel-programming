#include <stdio.h>
#include <stdlib.h>

struct two_matrix {
	float **Restrict;
	float **Interpolate;
};

struct matrix_vector {
	float **A;
	float *F;
};

float* Jacobi_it(float** A, int ASize, float* b, float* u_f, float w, float TOL, int itmax);

float* vector_sub(float* v1, float* v2, int size);

float* matrix_vector_multiply(float** A, float* v, int Arow, int Acol);

float norm(float* v, int ASize);

struct two_matrix* gen_restric(int size_fine, int size_coarse, int op);

float** kron(float** A, int Arow, int Acol, float** B, int Brow, int Bcol);

float** two_matrix_multiply(float** A, float** B, int rowA, int colA, int colB);

float* MG(float** A, int ASize, float* F, float* u_f, int m, float TOL, int itmax);

float** inverse(float** A, int ASize);

float* vector_add(float* v1, float* v2, int size);
