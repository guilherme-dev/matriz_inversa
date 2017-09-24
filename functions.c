#include "functions.h"



void processa_argumentos (int argc, char const *argv[]) {
    int i, iter, read_file, gerar_matriz;
    i = iter = read_file = gerar_matriz = 0;

    if (argc < 1) exit(-1);
   	for (i = 1; i < argc; i += 2) {
		if (strcmp(argv[i], "-e") == 0 && gerar_matriz == 0) {
			input_name = malloc(sizeof(char) * strlen(argv[i+1]));
			strcpy(input_name, argv[i+1]);
			input_f = fopen(input_name, "r");
			read_file = 1;
		}
		else if (strcmp(argv[i], "-o") == 0) {
			output_name = malloc(sizeof(char) * strlen(argv[i+1]));
			strcpy(output_name, argv[i+1]);
			output_f = fopen(output_name, "wr");
			printf("Abriu arquivo\n");
		}
		else if (strcmp(argv[i], "-r") == 0 && read_file == 0) {
			if (atoi(argv[i+1]) <= 1) {
				fprintf(stderr, "O valor de n deve ser maior que 1\n");
				fprintf(stderr, "Modo de uso: invmat [-i arquivo_entrada] [-o arquivo_saida] [-r N] -i k\n");
				exit(-1);
			}
			N = atoi(argv[i+1]);
			gerar_matriz = 1;
			A = generateSquareRandomMatrix(N);
			if (! (U = (double *) malloc (N * N * sizeof(double))) )
				exit(-1);
			// print_matriz(A, N);
			for (i = 0; i < N * N; ++i)
			{
				U[i] = A[i];
			}
			// print_matriz(A, N);
		}
		else if (strcmp(argv[i], "-i") == 0) {
			if (atoi(argv[i+1]) <= 0) {
				fprintf(stderr, "O valor de iteracoes deve ser maior que 0\n");
				fprintf(stderr, "Modo de uso: invmat [-i arquivo_entrada] [-o arquivo_saida] [-r N] -i k\n");
				exit(-1);
			}
			iter = 1;
		}
		else {
			fprintf(stderr, "Parametro invalido!\n");
			fprintf(stderr, "Modo de uso: invmat [-i arquivo_entrada] [-o arquivo_saida] [-r N] -i k\n");
			exit(-1);
		}
	}  //end for
	// if (iter == 0) {
	// 	fprintf(stderr, "Numero de iteracoes nao fornecido! Abortando.\n");
	// 	fprintf(stderr, "Modo de uso: invmat [-i arquivo_entrada] [-o arquivo_saida] [-r N] -i k\n");
	// 	exit(-1);
	// }
	if (read_file)
		read_matriz(read_file);
}

void read_matriz (int read_file) {
	int i;
	if (read_file == 1) {
		fscanf(input_f, "%d", &N);

		//Inicializa Matriz A
		if (! (A = (double *) malloc (N * N * sizeof(double))) )
			exit(-1);
		if (! (U = (double *) malloc (N * N * sizeof(double))) )
			exit(-1);
		
		if (!A || !U) {
			printf("Erro na alocacao das matrizes A U\n");
			exit(-1);
		}
		
		for (i = 0; i < N * N; i++) {
			fscanf(input_f, "%lf", &A[i]);
			U[i] = A[i];
		}
		// print_matriz(A, N);
	} else {
		printf("Digite a dimensao da matriz\n");
		fscanf(stdin, "%d", &N);	
		//ler matriz do terminal 
	}
}

int compara_float(double a, double b, char operacao) {
	double diff_abs = fabs(a - b);
	double diff = a - b;
	double maior;
	a = fabs(a);
	b = fabs(b);
	maior = (b > a) ? b : a;

	if (operacao == IGUAL) {
		if (diff_abs <= maior * DBL_EPSILON)
			return 1;
		else 
			return 0;
	} else if (operacao == MENOR) {
		if (diff < maior * DBL_EPSILON)
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