#include "functions.h"


#define m_size(d) (((d)*(d+1))/2)
#define size(d) ((d+1)*(d/2))
#define m_index(r,c) ((r)<(c) ? 0 : (m_size((r)-1)+(c)))
#define uindex(r,c) ((r)>(c) ? 0 : ((size(d))-(size(d-r)) + (c-r)))

#define SIZE(n) (((n)*(n+1))/2)
#define OFFSET(i,j) (SIZE((i)-1)+(j))
#define INDEX(i,j) ((i)<(j) ? 0 :  (OFFSET((i),(j))))
#define UINDEX(i,j,n) ((i)>(j) ? 0 : (SIZE(n)-SIZE((n)-(i))+(j)-(i)))


#define LIN 4
#define COL 6


//  TENTANDO USAR MATRIX DE INDECES
void triangular_superior() {


int **mat ;
int i, j ;
int n = 4;

// aloca um vetor de LIN ponteiros para linhas
mat = malloc (LIN * sizeof (int*)) ;
// aloca um vetor com todos os elementos da matriz
mat[0] = malloc (m_size(n) * sizeof (int)) ;


for (i = 0; i < m_size(n); i++) {
    mat[0][i] = i;
    printf("%d ", mat[0][i]);
}
// ajusta os demais ponteiros de linhas (i > 0)
for (i=1; i < n; i++)
  mat[i] = mat[0] + (SIZE(n)-SIZE(n-i)) ;

printf("\n");

// percorre a matriz
for (i=0; i < n; i++) {
  for (j=i; j < n; j++){
      printf("%d ", mat[i][j-i]);
  }
  printf("\n");
}
// libera a memória da matriz
free (mat[0]) ;
free (mat) ;
}


void triangular_inferior() {
    int n = 10;
    // int size = ((n * n) + n) / 2;
    // printf("size: %d\n", size);
    int d = m_size(n);
    int v[d];
    int m[n*n];
    int i, j, k;

    for (i = 0; i < d; ++i)
    {
        v[i] = i;
        printf("%d ", v[i] );
    }
    printf("\n");
    // for (i = 0; i < n * n; i++)
    //     m[i] = i;

    printf("inferior:\n");
    for (i=0; i <=n ; i++) {
        for (j = 0; j < i; ++j) {
            printf("%d ", v[INDEX(i,j)]);
        }
        printf("\n");
    }


    //FUNCIONOU
    printf("superior\n");
    for (i = 0; i < n; ++i) {
        for (j = i; j < n; ++j) {
            printf("%d ", v[UINDEX(i,j,n)]);
        }
        printf("\n");
    }

    printf("superior2:\n");
    for (i=n-1; i >=0 ; i--) {
        for (j = n-1; j >= i; --j) {
            printf("%d ", v[UINDEX(i,j,n)]);
        }
        printf("\n");
    }


    // for (i = 0; i < n; ++i) {
    //     for (j = 0; j < n; ++j) {
    //         printf("%d ", v[uindex2(i,j)]);
    //     }
    //     printf("\n");
    // }


    // for (i = 0; i < n; i++) {
    //     for (j = 0; j < n; j++) {
    //         for (j = 0; j < n; j++) {
    //             printf("%d ", TRM_INDEX(v, d-1-k, d-1-j));
    //         }
    //     }
    //     printf("\n");
    // }
}

//    k = 0;
//    col = n-1;
   // for (i = 0; i < n; ++i) {
//        printf("%d ", v[i]);
//    }
//    printf("\n");
//    for (i = 1; i < n; ++i) {
//        for (j = 0; j < col; ++j) {
//            printf("%d ", v[LIN + j]);
//        }
//        k += i;
//        col--;
//        printf("\n");
//    }





// k = 0;
// for (i = 0; i < N; i++) {
//     for (j = 0; j < i; j++) {
//         L[k] = LU[i*N+j];
//         k++;
//     }
//     for (; j <= i; j++) {
//         L[k] = 1;
//         k++;
//     }
// }
// col = 0;
// for (i = 0; i <= N; i++ ) {
//     for (j = 0; j < col; j++) {
//         printf("%g ", L[m_index(i,j)]);
//     }
//     col++;
//     printf("\n");
// }



void forward_iteration() {
    int i, n = 10000;
    int v[n];
    for (i = 0; i < n; ++i) {
        v[i] = i;
    }
}

void backward_iteration() {
    int i, n = 10000;
    int w[n];
    for (i = n-1; i >= 0; --i) {
        w[i] = i;
    }
}

int main(int argc, char const *argv[])
{
    int i;
    // LIKWID_MARKER_INIT;
    // LIKWID_MARKER_START("t1");
    // double temp_begin, temp_end, temp_fo;
    // temp_begin = timestamp();
    //     for (i = 0; i < 100000; i++) {
    //         forward_iteration();
    //     }
    // temp_end = timestamp();
    // temp_fo = temp_end - temp_begin;
    // LIKWID_MARKER_STOP("t1");
    // printf("temp_fo: %g\n", temp_fo);
    // LIKWID_MARKER_START("t2");
    // temp_begin = timestamp();
    // for (i = 0; i < 100000; i++) {
    //     backward_iteration();
    // }
    // temp_end = timestamp();
    // temp_fo = temp_end - temp_begin;
    // LIKWID_MARKER_STOP("t2");
    // printf("temp_back: %g\n", temp_fo);
    //
    // LIKWID_MARKER_CLOSE;

    // triangular_inferior();
    triangular_superior();



	return 0;
}
