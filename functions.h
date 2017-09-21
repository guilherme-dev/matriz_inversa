#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <float.h>

char *input_name, *output_name;
FILE *input_f, *output_f;
unsigned int N;
unsigned int max_iter;


void processing_arguments (int argc, char const *argv[]);
void read_matrix(int read_file);
void print_matrix(double *A, int n);