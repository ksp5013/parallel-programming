#include <stdio.h>
#include <stdlib.h>

struct two_matrix {  //回傳restrict 及 interpolate用 
	double **Restrict;
	double **Interpolate;
};

struct matrix_vector {  //回傳 Ax=F 的A,F用  
	double **A;
	double *F;
};

double* Jacobi_it(double** A, int ASize, double* b, double* u_f, double w, double TOL, int itmax);

double* vector_sub(double* v1, double* v2, int size);

double* matrix_vector_multiply(double** A, double* v, int Arow, int Acol);

double norm(double* v, int size);

struct two_matrix* gen_restric(int size_fine, int size_coarse, int op);

double** kron(double** A, int Arow, int Acol, double** B, int Brow, int Bcol);

double** two_matrix_multiply(double** A, double** B, int rowA, int colA, int colB);

double* MG(double** A, int ASize, double* F, double* u_f, int m, double TOL, int itmax);

double** inverse(double** A, int ASize);

double* vector_add(double* v1, double* v2, int size);
