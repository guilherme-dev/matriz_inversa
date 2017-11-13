#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <float.h>
#include <math.h>
#include <time.h>
#include <sys/time.h>
// This block enables to compile the code with and without the likwid header in place
#ifdef LIKWID_PERFMON
#include <likwid.h>
#else
#define LIKWID_MARKER_INIT
#define LIKWID_MARKER_THREADINIT
#define LIKWID_MARKER_SWITCH
#define LIKWID_MARKER_REGISTER(regionTag)
#define LIKWID_MARKER_START(regionTag)
#define LIKWID_MARKER_STOP(regionTag)
#define LIKWID_MARKER_CLOSE
#define LIKWID_MARKER_GET(regionTag, nevents, events, time, count)
#endif


#define IGUAL 1
#define MENOR 2
#define MENOR_IGUAL 3
#define TESTE 1

#define size(n) (((n)*(n+1))/2)
#define offset(i,j) (size((i)-1)+(j))
#define index(i,j) ((i)<(j) ? 0 :  (offset((i),(j))))
#define uindex(i,j,n) ((i)>(j) ? 0 : (size(n)-size((n)-(i))+(j)-(i)))

#define lower_size (size(N) - (N))
#define upper_size (size(N))

int N,  					/**< Dimensão da Matriz A (Ax = b) */
	max_iter,				/**< Quantidade máxima de iterações */
	*row, 					/**< vetor de dimensão N. Serve como vetor de índices para auxílio nas trocas de linhas */
	i, j, k, l; 			/**< Variável genérica de controle */
double *r; 					/**< Vetor de dimensão \max_iter para armazenar a norma do residuo em cada iteração */
double t_begin, t_end; /**< Variaveis para calculo de tempo */
double t_op1, t_op2;
double *A, 				/**< Matriz A[N][N] implementada como um vetor[N*N], padrão mantido para todas matrizes bidimensionais. */
	   *x, 				/**< Vetor [N], guarda cada coluna da matriz inversa AX */
	   *AI, 			/**< matriz inversa (guarda todos os valores de x). */
	   *W, 			    /**< Armazena matriz AW[N][N], gerada a partir de Aw = I, onde x = x - w */
	   *L, 				/**< Matriz L[N][N] da fatoração LU */
	   *U, 				/**< Matriz U[N][N] da fatoração LU */
       *L_aux,
       *U_aux,
	   *R, 				/**< Matriz R[N][N] para guardar o residuo da resolução do SL */
	   *z; 				/**< vetor[N] auxiliar utilizado em Lz = I */




void processa_argumentos (int argc, char const *argv[], int *n, int *max_iter, double *A, int *opt);
int compara_float(double a, double b, char operacao);
double *generateSquareRandomMatrix(int n );
double timestamp (void);
void print_matriz (double *A, int n);
void inline backward_substitution(double *U, double *x, double *z, int i);
void inline forward_substitution(double *L, double *z, double *R);
void gerar_saida(FILE *output_f);
double soma_kahan(double *vet, int n);
