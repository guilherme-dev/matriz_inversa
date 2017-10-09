#include "functions.h"


/**
 * Processa argumentos de entrada
 * 
 */
void processa_argumentos (int argc, char const *argv[], int *n, int *max_iter, double *A, int *opt) {
    int i, iter, gerar_matriz;
    i = iter =  gerar_matriz = 0;
    char 
    if (argc < 1) 
    	exit(-1);
   	for (i = 1; i < argc; i += 2) {
		if (strcmp(argv[i], "-e") == 0 && gerar_matriz == 0) {
			
			opt[0] = 1; //Arquivo de entrada fornecido
		}
		else if (strcmp(argv[i], "-r") == 0) {
			if (atoi(argv[i+1]) <= 1) {
				fprintf(stderr, "O valor de n deve ser maior que 1\n");
				fprintf(stderr, "Modo de uso: invmat [-i arquivo_entrada] [-o arquivo_saida] [-r N] -i k\n");
				exit(-1);
			}
			gerar_matriz = 1;
			*n = atoi(argv[i+1]);

			//GERA MATRIZ ALEATORIA
			A = generateSquareRandomMatrix(*n);
			//NECESSARIO ALOCAR U AQUI PARA JÁ EFETUAR U = A;
			// if (! (U = (double *) malloc (N * N * sizeof(double))) )
			// 	exit(-1);
			
			// for (k = 0; k < N * N; ++k)
			// {
			// 	U[k] = A[k];
			// }
			
		}
		else if (strcmp(argv[i], "-o") == 0) {
			
			opt[1] = 1; //Arquivo de saida fornecido
		}
		else if (strcmp(argv[i], "-i") == 0) {
			if (atoi(argv[i+1]) < 0) {
				fprintf(stderr, "O valor de iteracoes deve ser maior ou igual a 0\n");
				fprintf(stderr, "Modo de uso: invmat [-i arquivo_entrada] [-o arquivo_saida] [-r N] -i k\n");
				exit(-1);
			}
			max_iter = atoi(argv[i+1]);
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
	// if (opt[0])
	// 	read_matriz(read_file);
}

/**
 * Efetua comparações em ponto flutuante. Utiliza DBL_EPSILON como limite de erro.
 * 
 */
int compara_float(double a, double b, char operacao) {
	double diff_abs = fabs(a - b);
	double diff = a - b;
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
		if (diff <=  DBL_EPSILON)
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
 * Efetua soma de kahan para vetor[].
 * 
 */
double soma_kahan (double *v, int n) {
    double sum = 0.0;
    double c = 0.0;                 // A running compensation for lost low-order bits.
    double y, t;
    int i;
    for (i = 0; i < n; ++i)
    {
    	y = v[i] - c;
    	t = sum + y;
    	c = (t - sum) - y;
    	sum = t;
    }
    return sum;
}

/**
 * Imprime resultado no arquivo de saída.
 * 
 */
void gerar_saida (void) {
	double media_iter, media_res = 0.0;

	fprintf(output_f, "#\n");
	for (i = 0; i < max_iter && r[i] >= 0; ++i) {
		media_res += temp_res[i];
		media_iter += temp_iter[i];
		fprintf(output_f, "# iter %d: ||%.17g||\n", i, r[i]);
	}
	fprintf(output_f, "# Tempo LU: %g\n", temp_lu);
	fprintf(output_f, "# Tempo iter: %.17g\n", media_iter / max_iter);
	fprintf(output_f, "# Tempo residuo: %.17g\n", media_res / max_iter);
	fprintf(output_f, "#\n");
	for (i = 0; i < N; i++) {
		for (j = 0; j < N; j++) {
			fprintf(output_f, "%g ", AX[i+N*j]);
		}
		fprintf(output_f, "\n");
	}
}