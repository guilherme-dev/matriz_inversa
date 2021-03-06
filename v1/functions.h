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


int N,  					/**< Dimensão da Matriz A (Ax = b) */
	max_iter,				/**< Quantidade máxima de iterações */
	*row, 					/**< vetor de dimensão N. Serve como vetor de índices para auxílio nas trocas de linhas */
	i, j, k, l; 			/**< Variável genérica de controle */
double *r, 					/**< Vetor de dimensão \max_iter para armazenar a norma do residuo em cada iteração */
		*aux_v;			   /**< Vetor auxiliar de dimensão N */
double temp_begin, temp_end, temp_lu; /**< Variaveis para calculo de tempo */
double *temp_iter, *temp_res; /**< Vetores para armazenar tempo das iterações, usado para calcular a media */
double *A, 				/**< Matriz A[N][N] implementada como um vetor[N*N], padrão mantido para todas matrizes bidimensionais. */
	   *x, 				/**< Vetor [N], guarda cada coluna da matriz inversa AX */
	   *AX, 			/**< Matriz AX[N][N] auxiliar, matriz inversa (guarda todos os valores de x). */
	   *AW, 			/**< Armazena matriz AW[N][N], gerada a partir de Aw = I, onde x = x - w */
	   *A_AI, 			/**< Matriz [N][N] que armazena a multiplicação A * A_Inversa */
	   *L, 				/**< Matriz L[N][N] da fatoração LU */
	   *U, 				/**< Matriz U[N][N] da fatoração LU */
	   *R, 				/**< Matriz R[N][N] para guardar o residuo da resolução do SL */
	   *I, 				/**< Matriz I[N][N] para armazenar a matriz Identidade (eca)*/
	   *b, 				/**< vetor[N] auxiliar */
	   *z; 				/**< vetor[N] auxiliar utilizado em Lz = I */


void processa_argumentos (int argc, char const *argv[], int *n, int *max_iter, double *A, int *opt);
int compara_float(double a, double b, char operacao);
double *generateSquareRandomMatrix(int n );
double timestamp (void);
void print_matriz (double *A, int n);
void aloca_estruturas (void);
void backward_substitution(double *U, double *x, double *z, int iter);
void forward_substitution(double *L, double *z, double *R, int iter);
void gerar_saida(FILE *output_f);
double soma_kahan(double *vet, int n);
