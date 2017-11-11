#include "functions.h"


/**
 * Processa argumentos de entrada
 *
 */
void processa_argumentos (int argc, char const *argv[], int *N, int *max_iter, double *A, int *opt) {
    int i, iter, gerar_matriz;
    i = iter =  gerar_matriz = 0;
    if (argc < 1)
		exit(-1);
	opt[0] = opt[1] = 0;
   	for (i = 1; i < argc; i += 2) {
		if (strcmp(argv[i], "-e") == 0 && gerar_matriz == 0) {
            opt[0] = i+1;
		}
		else if (strcmp(argv[i], "-r") == 0) {
			if (atoi(argv[i+1]) <= 1) {
				fprintf(stderr, "O valor de n deve ser maior que 1\n");
				fprintf(stderr, "Modo de uso: invmat [-i arquivo_entrada] [-o arquivo_saida] [-r N] -i k\n");
				exit(-1);
			}
			gerar_matriz = 1;
			*N = atoi(argv[i+1]);
			// A = generateSquareRandomMatrix(*n);
		}
		else if (strcmp(argv[i], "-o") == 0) {
            //Arquivo de saida fornecido
            opt[1] = i + 1;
		}
		else if (strcmp(argv[i], "-i") == 0) {
			if (atoi(argv[i+1]) < 0) {
				fprintf(stderr, "O valor de iteracoes deve ser maior ou igual a 0\n");
				fprintf(stderr, "Modo de uso: invmat [-i arquivo_entrada] [-o arquivo_saida] [-r N] -i k\n");
				exit(-1);
			}
			*max_iter = atoi(argv[i+1]);
			iter = 1;
		}
		else {
			fprintf(stderr, "Parametro invalido!\n");
			fprintf(stderr, "Modo de uso: invmat [-i arquivo_entrada] [-o arquivo_saida] [-r N] -i k\n");
			exit(-1);
		}
	}  //end for
	if (iter == 0) {
		fprintf(stderr, "Numero de iteracoes nao fornecido! Abortando.\n");
		fprintf(stderr, "Modo de uso: invmat [-i arquivo_entrada] [-o arquivo_saida] [-r N] -i k\n");
		exit(-1);
	}
}

/**
 * Efetua comparações em ponto flutuante. Utiliza DBL_EPSILON como limite de erro.
 *
 */
int compara_float(double a, double b, char operacao) {
	double diff_abs = fabs(a - b);
	double maior;
	a = fabs(a);
	b = fabs(b);
	maior = (b > a) ? b : a;

	if (operacao == MENOR_IGUAL) {
		if (diff_abs <= maior * DBL_EPSILON)
			return 1;
		else
			return 0;
	} else if (operacao == MENOR) {
		if (diff_abs <=  DBL_EPSILON)
			return 1;
		else
			return 0;
	}
	return 0;
}

double *generateSquareRandomMatrix(int n )
{
  double *mat = NULL;

  /* return NULL if memory allocation fails */
  if ( ! (mat = (double *) malloc(n*n*sizeof(double))) )
    return (NULL);

  /* generate a randomly initialized matrix in row-major order */
  double *ptr = mat;
  double *end = mat + n*n;

  double invRandMax = 1.0/(double)RAND_MAX;

  while( ptr != end ) {
    *ptr++ = (double)rand() * invRandMax;
  }

  return (mat);
}

double timestamp (void) {
    struct timeval tp;
    gettimeofday(&tp, NULL);
    return((double)(tp.tv_sec*1000.0 + tp.tv_usec/1000.0));
}

void print_matriz(double *A, int n) {
	int i, j;
	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++) {
			printf("%g ", A[i*n + j]);
		}
		printf("\n");
	}
}

/**
 * Imprime resultado no arquivo de saída.
 *
 */
void gerar_saida (FILE *output_f) {
	for (i = 0; i < max_iter && r[i] >= 0; ++i) {
		fprintf(output_f, "# iter %d: ||%.17g||\n", i+1, r[i]);
	}
	fprintf(output_f, "#\n");
    #ifdef TESTE
        if (N > 100)
            return;
    #endif
	for (i = 0; i < N; i++) {
		for (j = 0; j < N; j++) {
			fprintf(output_f, "%g ", AI[i+N*j]);
		}
		fprintf(output_f, "\n");
	}
    printf("t_op1 %g\nt_op2 %g\n", t_op1, t_op2);
}
