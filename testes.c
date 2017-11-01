#include "functions.h"

#define LIN (i*n) - k
#define m_size(d) (((d)*(d+1))/2)
#define m_index(r,c) ((r)<(c) ? 0 : (m_size((r)-1)+(c)))



void triangular_inferior() {
    int n = 10;
    // int size = ((n * n) + n) / 2;
    // printf("size: %d\n", size);
    int d = m_size(n);
    int v[d];
    int col = 0;
    int i, j, k;

    for (i = 0; i < d; ++i)
    {
        v[i] = i;
        printf("%d ", v[i] );
    }
    printf("\n");

    for (i = 0; i <= n; ++i) {
        for (j = 0; j < col; ++j) {
            printf("%d ", v[m_index(i,j)]);
        }
        printf("\n");
        col++;
    }
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

void forward_iteration() {
    int i, n = 1000000;
    int v[n];
    for (i = 0; i < n; ++i) {
        v[i] = i;
    }
}

void backward_iteration() {
    int i, n = 1000000;
    int w[n];
    for (i = n-1; i >= 0; --i) {
        w[i] = i;
    }
}

int main(int argc, char const *argv[])
{
    LIKWID_MARKER_INIT;
    LIKWID_MARKER_START("TESTE");
    double temp_begin, temp_end, temp_fo;
    temp_begin = timestamp();
    forward_iteration();
    temp_end = timestamp();
    temp_fo = temp_end - temp_begin;
    printf("temp_fo: %g\n", temp_fo);
    temp_begin = timestamp();
    backward_iteration();
    temp_end = timestamp();
    temp_fo = temp_end - temp_begin;
    printf("temp_back: %g\n", temp_fo);
    LIKWID_MARKER_STOP("TESTE");
    LIKWID_MARKER_CLOSE;



	return 0;
}
