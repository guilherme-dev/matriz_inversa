#include "functions.h"

void processing_arguments (int argc, char const *argv[]) {
    int i = 1;
    if (strcmp(argv[i],"-i") == 0) {
        i++;
        output_name = malloc(sizeof(char) * strlen(argv[i]));
        strcpy(output_name, argv[i]);
        output_f = fopen(output_name, "wr");
    }
    // if (strcmp(argv[i],"-t") == 0) {
    //     i++;
    //     tolerancia = atof(argv[i]);
    //     i++;
    // } 
    // if (strcmp(argv[i],"-o") == 0) {
    //     i++;
    //     arquivo_saida = malloc(sizeof(char) * strlen(argv[i]));
    //     strcpy(arquivo_saida, argv[i]);
    //     output = fopen(arquivo_saida, "wr");
    // } else {
    //     fprintf(stderr, "ERRO: parametro \"%s\" não reconhecido\n", argv[i]);
    //     exit(-1);
    // }
}
