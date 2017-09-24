	


#include "functions.h"

int main(int argc, char const *argv[])
{
	double maior, temp, m, soma;
	int aux;
	processa_argumentos(argc, argv); 
	
	if (! (row = (int *) malloc (N * sizeof(int))) )
		exit(-1);
	for (i = 0; i < N; ++i)
		row[i] = i;

	if (! (z = (double *) malloc (N * sizeof(double))) )
		exit(-1);
	if (! (b = (double *) malloc (N * sizeof(double))) )
		exit(-1);
	if (! (x = (double *) malloc (N * sizeof(double))) )
		exit(-1);
	if (! (L = (double *) malloc (N * N * sizeof(double))) )
		exit(-1);
	if (! (AI = (double *) malloc (N * N * sizeof(double))) )
		exit(-1);


	// printf("\n");
	//INICIO DA FATORACAO LU
	for (k = 0; k < N - 1; ++k)
	{
		//Pivotamento Parcial
		maior = fabs(U[k*N + k]);
		l = k;
		//Encontra maior pivo
		for (i = k; i < N; ++i){
			if (fabs(U[i*N+k]) > maior)
			{
				maior = fabs(U[i*N+k]);
				l = i;
			}
		}
		if (l != k) {
			printf("Troca de linha: %d -> %d\n", k, l);
			//Troca de linhas

			for (j = 0; j < N; ++j)
			{
				temp = U[k*N+j];
				U[k*N+j] = U[l*N+j];
				U[l*N+j] = temp;

				temp = L[k*N+j];
				L[k*N+j] = L[l*N+j];
				L[l*N+j] = temp; 

				
			}
			aux = row[k];
				row[k] = row[l];
				row[l] = aux;
		}
		//Gerando matriz U a partir da elimacao de gauss
		//E preenchendo matriz L
		printf("Entra eliminacao de gauss\n");
		for (i = k + 1; i < N; ++i)
		{
			printf("A[k*N + k]: %.17g\n", U[k*N + k]);
			m = U[i*N+k] / U[k*N + k];
			L[i*N+k] = m;
			for (j = 0; j < N; ++j)
			{
				U[i*N+j] = U[i*N+j] - m * U[k*N+j];
			}
		}
	}

	
		for (i = 0; i < N; ++i)
		{
			printf("%d ", row[i]);
		}
		L[0] = 1.0;
		for (i = 1; i < N; ++i) {
			for (j = 0; j < i; ++j)
			{
				U[i*N+j] = 0.0;
				if (j == i - 1)
					L[i*N+j+1] = 1.0;
			}
		}

		for (i = 0; i < N; i++)
		{
			printf("i: %d N:%d\n", i, N);
			for ( k = 0; k < N; ++k)
			{
				b[k] = (k == i) ? 1.0 : 0.0;
				z[k] = 0.0;
			}
			printf("\n");
			//forward Lz = b
			soma = 0.0;
			for (k = 0; k < N; ++k) {
			   soma = b[k];

			   for (j = 0; j < k; ++j) {
			      soma = soma - L[k*N+j]*z[j];  
			   }

			   z[k] = soma;
			}

			//Backward Ux = z
			soma = 0.0;
			x[N-1] = z[N-1] / U[(N*N)-1];
			for (k = N-2; k >= 0; --k)
			{
				soma = z[k];
				for (j = k + 1; j < N; ++j)
				{
					soma = soma - U[k*N+j] * x[j];
				}
				x[k] = soma / U[k*N + k];
			}
			for ( k = 0; k < N; ++k)
			{
				AI[row[i]*N+k] = x[k];
			}

			printf("z:\n");
			for (k = 0; k < N; ++k)
			{
				printf("%.17g ", z[k]);
			}
			printf("\nx:\n");
			for (k = 0; k < N; ++k)
			{
				printf("%.17g ", x[k]);
			}
			printf("\n");
		}
	

	printf("matriz A:\n");
	print_matriz (A, N);
	printf("Matriz U:\n");
	print_matriz (U, N);
	printf("Matriz L:\n");
	print_matriz (L, N);
	printf("Matriz AI:\n");
	for ( i = 0; i < N; ++i)
	{
		printf("%d ", i );
		for ( j = 0; j < N; ++j)
		{

			printf("%.17g ", AI[j*N+i]);
		}
		printf("\n");
	}



	free(A);
	free(AI);
	free(L);
	free(U);
	free(b);
	free(x);
	free(z);
	if (output_f)
		fclose(output_f);
	if (input_f)
		fclose (input_f);
	return 0;
}