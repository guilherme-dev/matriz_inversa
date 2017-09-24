#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <float.h>
#include <math.h>
#include <time.h>
#include <sys/time.h>

#define IGUAL 1
#define MENOR 2
#define MENOR_IGUAL 3


/*!
 * ... text ...
 */	

char *input_name, *output_name;
FILE *input_f, *output_f;
int N,  max_iter, *row, i, j, k, l;
double *r;
double temp_begin, temp_end, temp_lu;
double *temp_iter, *temp_res;
double *A, *AX, *AX_T, *AW, *A_AI, *L, *U, *R, *I, *b, *z, *x;


void processa_argumentos (int argc, char const *argv[]);
void read_matriz (int read_file);
int compara_float(double a, double b, char operacao);
double *generateSquareRandomMatrix(int n );
double timestamp (void);
void print_matriz (double *A, int n);
void backward_substitution(double *U, double *x, double *z, int iter);
void forward_substitution(double *L, double *z, double *R, int iter);
void gerar_saida(void);