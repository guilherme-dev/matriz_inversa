#include "functions.h"

void processing_arguments (int argc, char const *argv[]) {
    int i = 1;
    int iter = 0;
    int out = 0;
   	while (i < argc) {
		if (strcmp(argv[i], "-e") == 0) {
			i++;
			input_name = malloc(sizeof(char) * strlen(argv[i]));
			strcpy(input_name, argv[i]);
			input_f = fopen(input_name, "r");
			i++;
			out = 1;
		}
		if (strcmp(argv[i], "-o") == 0) {
			i++;
			output_name = malloc(sizeof(char) * strlen(argv[i]));
			strcpy(output_name, argv[i]);
			output_f = fopen(output_name, "wr");
			i++;
		}
		if (strcmp(argv[i], "-r") == 0) {
			i++;
			if (argv[i] <= 1) {
				fprintf(stderr, "O valor de n deve ser maior que 1\n");
				fprintf(stderr, "Modo de uso: invmat [-i arquivo_entrada] [-o arquivo_saida] [-r N] -i k\n");
				exit(-1);
			}
			n = argv[i];
			i++;
		}
		if (strcmp(argv[i], "-i" == 0)) {
			i++;
			if (argv[i] <= 0) {
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
	}
	if (iter == 0) {
		fprintf(stderr, "Numero de iteracoes nao fornecido! Abortando.\n");
		fprintf(stderr, "Modo de uso: invmat [-i arquivo_entrada] [-o arquivo_saida] [-r N] -i k\n");
		exit(-1);
	}
	if (out == 0) {
		// le matriz de stdin
	} else {
		// le matriz do arquivo
	}
}
