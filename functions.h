#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <float.h>
#include <math.h>
#include <time.h>

char *input_name, *output_name;
FILE *input_f, *output_f;
int N, iter, max_iter, *row, i, j, k, l;
double *A, *AI, *L, *U, *b, *z, *x;


void processa_argumentos (int argc, char const *argv[]);
void read_matriz (int read_file);
double *generateSquareRandomMatrix(int n );
double timestamp (void);
void print_matriz (double *A, int n);
void backward_substitution(void);
void forward_substitution(void);
// void aloca_estruturas ();