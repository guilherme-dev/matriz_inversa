#include <stdio.h>
#include <stdlib.h>
#define LIN (i*n) - k
#define m_size(d) (((d)*(d+1))/2)
#define m_index(r,c) ((r)<(c) ? 0 : (m_size((r)-1)+(c)))

int main(int argc, char const *argv[])
{
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


	return 0;
}
