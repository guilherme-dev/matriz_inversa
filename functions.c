#include "functions.h"

void processing_arguments (int argc, char const *argv[]) {
    int i, iter, read_file;
    i = iter = read_file = 0;


    if (argc < 1) exit(-1);
   	for (i = 1; i < argc; i += 2) {
		if (strcmp(argv[i], "-e") == 0) {
			input_name = malloc(sizeof(char) * strlen(argv[i+1]));
			strcpy(input_name, argv[i+1]);
			input_f = fopen(input_name, "r");
			read_file = 1;
		}
		else if (strcmp(argv[i], "-o") == 0) {
			output_name = malloc(sizeof(char) * strlen(argv[i+1]));
			strcpy(output_name, argv[i+1]);
			output_f = fopen(output_name, "wr");
		}
		else if (strcmp(argv[i], "-r") == 0 && read_file == 0) {
			if (atoi(argv[i+1]) <= 1) {
				fprintf(stderr, "O valor de n deve ser maior que 1\n");
				fprintf(stderr, "Modo de uso: invmat [-i arquivo_entrada] [-o arquivo_saida] [-r N] -i k\n");
				exit(-1);
			}
			N = atoi(argv[i+1]);
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
	if (iter == 0) {
		fprintf(stderr, "Numero de iteracoes nao fornecido! Abortando.\n");
		fprintf(stderr, "Modo de uso: invmat [-i arquivo_entrada] [-o arquivo_saida] [-r N] -i k\n");
		exit(-1);
	}
	read_matrix(read_file);
}

void read_matrix (int read_file) {
	int i;
	double *A;
	if (read_file == 1) {
		fscanf(input_f, "%d", &N);
		allocate_data_structs();

		for (i = 0; i < N * N; i++) {
			fscanf(input_f, "%lf", &A[i]);
		}
		print_matrix(A, (int) N);
	} else {
		printf("Digite a dimensao da matriz\n");
		fscanf(stdin, "%d", &N);
		//ler matriz do terminal 
	}
}

void print_matrix(double *A, int n) {
	int i, j;
	for (i = 0; i < n; i++) {
		for (j = 0; j < n; j++) {
			printf("%g ", A[i*n + j]);
		}
		printf("\n");
	}
}