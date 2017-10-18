/**
 * @brief
 *
 * \author Guilherme Santos
 *
 * @param w
 *
 * @return
 */



#include "functions.h"

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
	if (! (U = (double *) malloc (N * N * sizeof(double))) )
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
 * @brief
 *
 * Efetua decomposição LU
 *
 * @param void
 */
void lu_decomposition (void) {
	double maior, temp, m;
	int aux;
	for (i = 0; i < N * N; ++i) {
		U[i] = A[i];
	}
    //Pivotamento Parcial
	for (k = 0; k < N - 1; ++k)
	{
		maior = fabs(U[k*N + k]);
		l = k;
		for (i = k; i < N; ++i){  //Encontra maior pivo
			if ( fabs(U[i*N+j]) > maior )
			{
				maior = fabs(U[i*N+k]);
				l = i;
			}
            if (maior == 0.0) { //TODO ALMOST EQUAL
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
		for (i = k + 1; i < N; ++i)
		{
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
	int opt[2];
	char	*input_name, 			/**< String para nome do arquivo de input*/
			*output_name;			/**< String para nome do arquivo de output */
	FILE	*input_f,				/**< Arquivo entrada */
			*output_f;				/**< Arquivo saida */
    input_name = output_name = NULL;

	processa_argumentos(argc, argv, &N, &max_iter, A, opt);

	// Se foi passado arquivo de entrada como parametro
	if (opt[0]) {
		// Abre arquivo de entrada e faz leitura dos dados para a matriz A
		// Salva o valor de N
		i = opt[0];
		input_name = malloc(sizeof(char) * strlen(argv[i]));
		strcpy(input_name, argv[i]);
		input_f = fopen(input_name, "r");

		fscanf(input_f, "%d", &N);
		if (! (A = (double *) malloc (N * N * sizeof(double))) )
			exit(-1);
		for (i = 0; i < N * N; i++) {
			fscanf(input_f, "%lf", &A[i]);
		}
	} else {
		if (! (A = (double *) malloc (N * N * sizeof(double))) )
			exit(-1);
		A = generateSquareRandomMatrix(N);
	}

	aloca_estruturas();

	for (i = 0; i < N; ++i)
		row[i] = i; // < Inicializa vetor de indices


	temp_begin = timestamp();
	lu_decomposition();
	temp_end = timestamp();
	temp_lu = temp_end - temp_begin;

	// Inicializa matriz I (identidade), mantendo as trocas de linhas feitas durante o pivotamento
	for (i = 0; i < N; ++i) {
		for (j = 0; j < N; ++j) {
			I[i*N+j] = (j == i) ? 1.0 : 0.0;
            R[row[i]*N+j] = I[i*N+j];
		}
	}
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
    LIKWID_MARKER_INIT;
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
                R[row[i]*N+j] = I[i*N+j] - A_AI[i*N+j];
			}
		}

		// NORMA DO RESIDUO
		soma = 0.0;
		temp_begin = timestamp();
		for (i = 0; i < N; ++i) {
			for (j = 0; j < N; ++j) {
				soma += R[row[i]*N+j] * R[row[i]*N+j];
			}
		}

		r[l] = fabs(sqrt(soma));
		temp_end = timestamp();
		temp_res[l] = temp_end - temp_begin;
			temp_begin = timestamp();
            LIKWID_MARKER_START("mult_matrix");
			for (i = 0; i < N; ++i) {
				forward_subs(L, z, R, i);
				backward_subs(U, x, z, i);
				for ( k = 0; k < N; ++k)
				{
					AW[i*N+k] = x[k];
				}
			}
            LIKWID_MARKER_STOP("mult_matrix");
			// Encontra nova solução X(K)
			//X(K) = X(K-1) + W(K)
			for (i = 0; i < N * N; ++i) {
    			AX[i] += AW[i];
			}
			temp_end = timestamp();
	}
    LIKWID_MARKER_CLOSE;
	if (opt[1]) {
		i = opt[1];
		output_name = malloc(sizeof(char) * strlen(argv[i]));
		strcpy(output_name, argv[i]);
		output_f = fopen(output_name, "wr");
        gerar_saida(output_f);
		fclose(output_f);
	} else {
		gerar_saida(stdout);
	}
	if (opt[0])
		fclose (input_f);
    printf("Fim!\n");
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
	return 0;
}
