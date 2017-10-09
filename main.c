#include "functions.h"
// int N,  max_iter, *row, i, j, k, l;
// *A matriz A, nao altera
// *AX matriz N * N contendo todos os x, ou seja, matriz inversa
// *AX_T matriz AX transposta, uma vez que AX eh vetor [x0 x1 x2....]
// *AW igual AX, mas pra calcular o valor w (x' = x + w)
// *A_AI A * AX, tem que dar a matriz identidade
// *L 
// *U
// *R matriz N * N pra guardar o residuo R[i][j]
// *b
// *z
// *x; vetor tamanho N pra armazenar o x de cada SL calculado, AX guarda o x da iteracao

/**
 * Aloca dinamicamente todas as estruturas de dados
 */
void aloca_estruturas (void) {
	if (! (row = (int *) malloc (N * sizeof(int))) )
		exit(-1);
	if (! (aux_v = (double *) malloc (N * sizeof(double))) )
		exit(-1);

	if (! (temp_iter = (double *) malloc (max_iter * sizeof(double))) )
		exit(-1);
	if (! (temp_res = (double *) malloc (max_iter * sizeof(double))) )
		exit(-1);

	if (! (r = (double *) malloc (max_iter * sizeof(double))) )
		exit(-1);

	if (! (z = (double *) malloc (N * sizeof(double))) )
		exit(-1);
	if (! (b = (double *) malloc (N * sizeof(double))) )
		exit(-1);
	if (! (x = (double *) malloc (N * sizeof(double))) )
		exit(-1);
	if (! (L = (double *) malloc (N * N * sizeof(double))) )
		exit(-1);
	if (! (AX = (double *) malloc (N * N * sizeof(double))) )
		exit(-1);
	if (! (AW = (double *) malloc (N * N * sizeof(double))) )
		exit(-1);
	if (! (A_AI = (double *) malloc (N * N * sizeof(double))) )
		exit(-1);
	if (! (R = (double *) malloc (N * N * sizeof(double))) )
		exit(-1);
	if (! (I = (double *) malloc (N * N * sizeof(double))) )
		exit(-1);
}

/**
 * Efetua a fatoração LU. 
 * Utiliza compara_float() para comparações durante o pivotamento.
 */
void lu_decomposition (void) {
	double maior, temp, m;
	int aux;
	for (k = 0; k < N - 1; ++k)
	{
		//Pivotamento Parcial
		maior = fabs(U[k*N + k]);
		l = k;
		//Encontra maior pivo
		for (i = k; i < N; ++i){
			if ( compara_float(maior, fabs(U[i*N+k]), MENOR_IGUAL) ) 
			{
				maior = fabs(U[i*N+k]);
				l = i;
			} else if ( compara_float(maior, 0.0, MENOR_IGUAL ) ) { 
				printf("ERRO! Pivo == %.17g, matriz nao possui inversa!\n", maior);
				exit(-1);
			}
		}
		if (l != k) {
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
		// Gerando matriz U a partir da elimacao de gauss
		// E preenchendo matriz L
		// printf("Entra eliminacao de gauss\n");
		for (i = k + 1; i < N; ++i)
		{
			// printf("A[k*N + k]: %.17g\n", U[k*N + k]);
			m = U[i*N+k] / U[k*N + k];
			L[i*N+k] = m;
			for (j = k; j < N; ++j)
			{
				U[i*N+j] = U[i*N+j] - m * U[k*N+j];
			}
		}
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
}
/**
 * Efetua a forward substitution para resolver Lz = R, onde R(0) = I. 
 * 
 */
void forward_subs (double *L, double *z, double *R, int iter) {
	double soma;
	for ( k = 0; k < N; ++k)
	{
		z[k] = 0.0;
	} 
	soma = 0.0;
	for (k = 0; k < N; ++k) {
	   soma = R[row[iter]*N+k];

	   for (j = 0; j < k; ++j) {
	      soma = soma - L[k*N+j]*z[j];
	   }
	   z[k] = soma;
	}
}

/**
 * Efetua backward substitution para resolver Ux = z;
 * 
 */
void backward_subs (double *U, double *x, double *z, int iter) {
	double soma = 0.0;
	//Backward Ux = z
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
}

/**
 * Executa maior parte do método
 * 
 */
int main(int argc, char const *argv[])
{
	srand( 20162 );
	double aux, soma; 
	char	*input_name, 			/**< Strings para nome do arquivo de input*/
			*output_name;			/**< Strings para nome do arquivo de output */
	FILE	*input_f,				/**< Arquivo entrada */
			*output_f;				/**< Arquivo saida */

	int opt[2];						/**< Auxiliar para opções de entrada e saida*/


	processa_argumentos(argc, argv, &n, &max_iter, A, opt); 
	
	//Se foi passado arquivo de entrada como parametro
	if (opt[0]) { 
		//Abre arquivos
		input_name = malloc(sizeof(char) * strlen(argv[i+1]));
		strcpy(input_name, argv[i+1]);
		input_f = fopen(input_name, "r");
		
		fscanf(input_f, "%d", &n);

		if (! (A = (double *) malloc (n * n * sizeof(double))) )
			exit(-1);
		
		for (i = 0; i < N * N; i++) {
			fscanf(input_f, "%lf", &A[i]);
		}

	} else {
		A = generateSquareRandomMatrix(n);
	}



	if (opt[1]) {
		output_name = malloc(sizeof(char) * strlen(argv[i+1]));
		strcpy(output_name, argv[i+1]);
		output_f = fopen(output_name, "wr");
	}

	aloca_estruturas();


	for (i = 0; i < N; ++i)
		row[i] = i; // < Inicializa vetor de indices 


	temp_begin = timestamp();
	lu_decomposition();
	temp_end = timestamp();
	temp_lu = temp_end - temp_begin;
	
	// Inicializa matriz I (identidade), mantendo as trocas de linhas feitas durante o pivotamento
	// for (i = 0; i < N; ++i) {
	// 	for (j = 0; j < N; ++j) {
	// 		I[row[i]*N+j] = (j == i) ? 1.0 : 0.0;
	// 	}
	// } 
	//Encontra primeira Solucao X0
	temp_begin = timestamp();
	for (i = 0; i < N; i++) { //Resolve N sistemas lineares para as Xn colunas de AI
		forward_subs(L, z, I, i);
		backward_subs(U, x, z, i);
		for ( k = 0; k < N; ++k)
		{
			AX[i*N+k] = x[k];
		}
	}
	temp_end = timestamp();
 
	//INICIO REFINAMENTO SUCESSIVO
	for (l = 0; l < max_iter; ++l) {
		temp_iter[l] = temp_end - temp_begin;
		for (i = 0; i < N; i++) {
			for (j = 0; j < N; j++) {
				soma = 0.0;
				for (k = 0; k < N; k++) {
					soma += A[i*N+k] * AX[k+N*j];
				}
				A_AI[i*N+j] = soma;
			}
		}

		//Calculo matriz residuos REFINAMENTO
		for (i = 0; i < N; ++i) {
			for (j = 0; j < N; ++j) {
				aux = I[row[i]*N+j] - A_AI[i*N+j];
				R[row[i]*N+j] = (I[row[i]*N+j] - A_AI[i*N+j] <= DBL_EPSILON) ? 0 : aux;
			}
		}

		// NORMA DO RESIDUO
		soma = 0.0;
		temp_begin = timestamp();
		for (i = 0; i < N; ++i) {
			for (j = 0; j < N; ++j) {
				aux_v[j] = R[row[i]*N+j] * R[row[i]*N+j];
			}
			soma += soma_kahan(aux_v, N);
		}

		r[l] = fabs(sqrt(soma)); 
		temp_end = timestamp();
		temp_res[l] = temp_end - temp_begin;
		if (fabs(r[l]) <= DBL_EPSILON) {
			printf("Residuo[l] <= DBL_EPSILON, finalizando.\n");
			break;
		} else {
			temp_begin = timestamp();
			for (i = 0; i < N; ++i) {
				forward_subs(L, z, R, i);
				backward_subs(U, x, z, i);
				for ( k = 0; k < N; ++k)
				{
					AW[i*N+k] = x[k];
				}
			}
			// Encontra nova solução X(K)
			//X(K) = X(K-1) + W(K)
			for (i = 0; i < N * N; ++i) {
				aux = fabs(AW[i]);
				if (aux > DBL_EPSILON) {
					AX[i] += AW[i];
				}
			}
			temp_end = timestamp();
		}
	}

	gerar_saida();
	free(A);
	free(AX);
	free(A_AI);
	free(AW);
	free(L);
	free(U);
	free(b);
	free(x);
	free(z);
	free(temp_iter);
	free(temp_res);
	if (opt[1]) {
		output_name = malloc(sizeof(char) * strlen(argv[i+1]));
		strcpy(output_name, argv[i+1]);
		output_f = fopen(output_name, "wr");
		fclose(output_f);
	}
	if (input_f)
		fclose (input_f);
	return 0;
}